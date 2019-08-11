#include "features.h"

features::features(){
	matrix m_features_matrix;
}

features::features(int feature_channels, int features_rows, int features_cols, int val):\
tensor(feature_channels, features_rows, features_cols, val){
	matrix m_features_matrix;
}

features::features(const cv::Mat &image, DATA_TYPE translation, DATA_TYPE scale)
	     :tensor(image, translation, scale){
	matrix m_features_matrix;
}

features::features(int feature_channels, int features_rows, int features_cols, DATA_TYPE min, DATA_TYPE max) : \
tensor(feature_channels, features_rows, features_cols, min,max)
{
	return;
}

features::features(int feature_channels, int features_rows, int features_cols, int min, int max) : \
tensor(feature_channels, features_rows, features_cols, min, max)
{
	return;
}


features::~features(){
	;
}

//virtual bool reshape(int kernels_width = KERNEL_ROW, int kernels_height = KERNEL_COL, \
//	int stride = 1, int padding_mode = VALID_PADDING);
bool features::reshape(int kernels_rows, int kernels_cols, int stride, int padding_mode){
	if (0 >= kernels_rows || 0 >= kernels_cols){
		DEBUG_PRINT("(0 >= kernel_rows || 0 >= kernel_cols) \n features::reshape \n");
		return false;
	}
	if (0 >= stride){
		DEBUG_PRINT("(0 >= stride) \n features::reshape \n");
		return false;
	}

	m_kernel_rows = kernels_rows;
	m_kernel_cols = kernels_cols;
	m_stride = stride;
	m_padding_mode = padding_mode;
	/* 以下三个变量来确定卷积左上方元素的在kernel中的位置 */
	int channel_in_kernels = 0;/* channel 代表第几个卷积核(特征) */
	int row_in_kernel = 0;     /* row代表元素相对于卷积核左上方元素的行数 */
	int col_in_kernel = 0;     /* col代表元素相对于卷积核左上方元素的列数 */
	/* 以上三个变量来确定单个卷积核左上方元素的在kernel中的位置 */

	/* 以下两个变量来确定卷积核左上角元素相对于单个特征的位置 */
	int row_in_feature = 0;
	int col_in_feature = 0;
	/* 仿照牛顿力学中的相对位置，即坐标转换，\
	   能够确定features_matrix元素在原始features中的绝对位置 */
	int index_in_kernel = 0;
	/* index_in_kernels辅助变量，描述元素相对于单个卷积核的相对位置（一维）*/
	switch (padding_mode){
	case VALID_PADDING: /* (N+2P-K)/S +1 */
		m_features_matrix = matrix( ((m_rows - m_kernel_rows)/stride +1)* \
                        		    ((m_cols - m_kernel_cols)/stride +1), \
			                        m_kernel_rows*m_kernel_cols*m_channels);
		/* 下面是核心代码 features2matrix */
		/* todo 此处计算可以优化 */
		for (int i = 0; i < m_features_matrix.m_rows; ++i){
			for (int j = 0; j < m_features_matrix.m_cols; ++j){
				channel_in_kernels = j / (m_kernel_rows*m_kernel_cols);
				index_in_kernel = j - channel_in_kernels*m_kernel_rows*m_kernel_cols;
				row_in_kernel = index_in_kernel / m_kernel_cols;
				col_in_kernel = index_in_kernel - row_in_kernel*m_kernel_cols;
				
				row_in_feature = i / ((m_cols - m_kernel_cols) / stride + 1);
				col_in_feature = i - row_in_feature*((m_cols - m_kernel_cols) / stride + 1);
				m_features_matrix.mp_data[i*m_features_matrix.m_cols + j] = \
					mp_matrixes[channel_in_kernels].mp_data\
					[(row_in_feature + row_in_kernel)*m_rows + (col_in_feature + col_in_kernel)];
			}
		}
		break;
	case SAME_PADDING:
		//todo
		break;
	default:
		break;
	}
	return true;
}

