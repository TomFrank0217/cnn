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

	m_kernels_rows = kernels_rows;
	m_kernels_cols = kernels_cols;
	m_stride = stride;
	m_padding_mode = padding_mode;

	switch (padding_mode){
	case VALID_PADDING: /* (N+2P-K)/S+1 */
		m_features_matrix = matrix( ( (m_rows - m_kernels_rows) / stride+1 ) \
                        		  * ( (m_cols - m_kernels_cols) / stride+1 ), \
			                        m_kernels_rows*m_kernels_cols*m_channels);
		for (int i = 0; i < m_features_matrix.m_rows; ++i){
			for (int j = 0; j < m_features_matrix.m_cols; ++j){

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

