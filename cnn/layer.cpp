#include "layer.h"

layer::layer(){
    //m_kers_channels = m_kers_rows \
    //    = m_kers_cols = m_kers_count = 0;
    //m_fts_channels = m_fts_rows = m_fts_cols = 0;
    kers = kernels();
    fts = featuresssss();
}

layer::layer(int kers_channels, int kers_rows, int kers_cols, int kers_count, \
    int fts_channels/*kers_channels*/, int fts_rows, int fts_cols){
    kers = kernels(kers_channels, kers_rows, kers_cols,kers_count,\
		- RANDOM_INITIAL_VAL, RANDOM_INITIAL_VAL);/* todo kers初始化需要很小的初始值 */
    fts = featuresssss(fts_channels, fts_rows, fts_cols, 0, 1);
}

layer::~layer(){
    ;
}

matrix layer::conv(){
    return fts.m_features_matrix*kers.m_kernels_matrix;
}


bool layer::reshape(int mode){
	if (MATRIX2FEATURES == mode){
		conv_matrix = conv();
		int conv_features_channels = conv_matrix.m_cols;
			/* todo padding!=0 */
		int conv_features_rows = \
			(fts.m_rows - kers.m_rows) / fts.m_stride + 1;
		/* todo padding!=0 */
		int conv_features_cols = \
			(fts.m_cols - kers.m_cols) / fts.m_stride + 1;
		if (conv_features_rows*conv_features_cols != conv_matrix.m_rows){
			std::cout << "(conv_features_rows*conv_features_cols != mx.m_rows\
						 layer::reshape()\n)";
		}
		conv_matrix_fts = featuresssss(conv_features_channels, conv_features_rows, conv_features_cols, 0.0);
		/* 此时这个问题和之前的问题相似，但是简单一些 */
		/* 我们是要求 conv_matrix中第(i,j)元到 conv_matrix_features中对应的(channel,row,col)之间的映射关系*/
		/* 即求一个映射关系f: (i,j) -> (channel,row,col) */
		/* 在这儿 matrix(i,j) -> features(channel,row,col) */
		/* 我们利用后向插值的方法,从 (channel,row,col)出发求得(i,j)的坐标 */
		/* 因为f是一个可逆映射，后向插值和前向插值计算量一样，但f不可逆的时候会有区别 */
		int i = 0;
		int j = 0;
		for (int channel = 0; channel < conv_matrix_fts.m_channels; ++channel){
			for (int row = 0; row < conv_matrix_fts.m_rows; ++row){
				for (int col = 0; col < conv_matrix_fts.m_cols; ++col){
					j = channel;
					//row = i / (conv_matrix_fts.m_cols);
					//col = i - row*conv_matrix_fts.m_cols;
					i = row*conv_matrix_fts.m_cols + col;

					//conv_matrix_fts.mp_matrixes[channel].mp_data[row*conv_matrix_fts.m_cols + col] \
						= conv_matrix.mp_data[i*conv_matrix.m_cols + j];
					conv_matrix_fts.mp_matrixes[j].mp_data[i] = \
						conv_matrix.mp_data[i*conv_matrix.m_cols + j];
				}
			}
		}

		return true;
	}
	else if (FEATURES2MATRIX == mode){
		/* 我们是要求conv_matrix_features第(channel,row,col)元到conv_matrix中第(i,j)元之间的映射关系*/
		/* 即求一个映射关系g: (channel,row,col) -> (i,j) */
		/* 在这儿 features(channel,row,col) -> matrix(i,j) */
		/* 我们利用后向插值的方法,从 (i,j)出发求得(channel,row,col)的坐标 */
		/* 因为g是一个可逆映射，后向插值和前向插值计算量一样，但g不可逆的时候会有区别 */
		/* f(g(x)) == x ==g(f(x)) f与g互为逆映射 */
		
		/* fts.m_features_matrix*kers.m_kernels_matrix; */
		conv_matrix = matrix(fts.m_features_matrix.m_rows, kers.m_kernels_matrix.m_cols, 0.0);
		int channel = 0;
		int row = 0;
		int col = 0;
		
		for (int i = 0; i < conv_matrix.m_rows; ++i){
			for (int j = 0; j < conv_matrix.m_cols; ++j){
				channel = j;
			    row = i / (conv_matrix_fts.m_cols);
				col = i - row*conv_matrix_fts.m_cols;
				conv_matrix.mp_data[i*conv_matrix.m_cols + j] = \
				conv_matrix_fts.mp_matrixes[channel].mp_data[row*conv_matrix_fts.m_cols + col];
			}
		}
		return true;
	}
	else{
		std::cout << "no mode ,layer::reshape(int mode = MATRIEX2KERNELS) \n";
		return false;
	}
	return true;
}