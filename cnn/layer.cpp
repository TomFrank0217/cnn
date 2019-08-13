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
		- RANDOM_INITIAL_VAL, RANDOM_INITIAL_VAL);/* todo kers��ʼ����Ҫ��С�ĳ�ʼֵ */
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
		/* ��ʱ��������֮ǰ���������ƣ����Ǽ�һЩ */
		/* ������Ҫ�� conv_matrix�е�(i,j)Ԫ�� conv_matrix_features�ж�Ӧ��(channel,row,col)֮���ӳ���ϵ*/
		/* ����һ��ӳ���ϵf: (i,j) -> (channel,row,col) */
		/* ����� matrix(i,j) -> features(channel,row,col) */
		/* �������ú����ֵ�ķ���,�� (channel,row,col)�������(i,j)������ */
		/* ��Ϊf��һ������ӳ�䣬�����ֵ��ǰ���ֵ������һ������f�������ʱ��������� */
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
		/* ������Ҫ��conv_matrix_features��(channel,row,col)Ԫ��conv_matrix�е�(i,j)Ԫ֮���ӳ���ϵ*/
		/* ����һ��ӳ���ϵg: (channel,row,col) -> (i,j) */
		/* ����� features(channel,row,col) -> matrix(i,j) */
		/* �������ú����ֵ�ķ���,�� (i,j)�������(channel,row,col)������ */
		/* ��Ϊg��һ������ӳ�䣬�����ֵ��ǰ���ֵ������һ������g�������ʱ��������� */
		/* f(g(x)) == x ==g(f(x)) f��g��Ϊ��ӳ�� */
		
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