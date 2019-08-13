#include "layer.h"

layer::layer(){
    //m_kers_channels = m_kers_rows \
    //    = m_kers_cols = m_kers_count = 0;
    //m_fts_channels = m_fts_rows = m_fts_cols = 0;
    kers = kernels();
    fts = features();
}

layer::layer(int kers_channels, int kers_rows, int kers_cols, int kers_count, \
    int fts_channels/*kers_channels*/, int fts_rows, int fts_cols){
    kers = kernels(kers_channels, kers_rows, kers_cols,kers_count,\
        0, 1);/* todo kers初始化需要很小的初始值 */
    fts = features(fts_channels, fts_rows, fts_cols, 0, 1);
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
		conv_matrix_fts = features(conv_features_channels, conv_features_rows, conv_features_cols, 0.0);
		/* 此时这个问题和之前的问题相似，但是简单一些 */
		/* 我们是要求 conv_matrix中第(i,j)元到 conv_matrix_features中对应的(channel,row,col)之间的映射关系*/
		/* 即求一个映射关系f: (i,j) -> (channel,row,col) */
		/* 在这儿 matrix(i,j) -> features(channel,row,col) */
		/* 我们利用后向插值的方法,从 (channel,row,col)出发求的(i,j)的坐标 */
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

	}
	else{
		std::cout << "no mode ,layer::reshape(int mode = MATRIEX2KERNELS) \n";
		return false;
	}
	return true;
}