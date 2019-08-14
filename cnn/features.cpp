#include "features.h"

features::features(){
	this->m_rows = 0;
	this->m_cols = 0;
	this->m_channels = 0;
	this->mp_matrixes = NULL;
}

features::features(int channels, int rows, int cols, int val) :
m_channels(channels), m_rows(rows), m_cols(cols)
{
	if (0 >= m_channels){
		DEBUG_PRINT("0 >= m_tensors_count\n");
		return;
	}

	mp_matrixes = new matrix[m_channels];
	if (NULL == mp_matrixes){
		DEBUG_PRINT("NULL == mp_matrixes\n");
		return;
	}

	if (0 == m_rows || 0 == m_cols){
		DEBUG_PRINT("0 == m_tensor_row || 0 == m_tensor_col\n");
		mp_matrixes = NULL;
		return;
	}

	if (0 > m_rows || 0 > m_cols){
		DEBUG_PRINT("0 > m_tensor_row || 0 > m_tensor_col\n");
		mp_matrixes = NULL;
		return;
	}

	for (int i = 0; i < m_channels; ++i){
		mp_matrixes[i] = matrix(m_rows, m_cols, val);
	}
	return;
}

features::features(int tensors_count, int tensors_row, int tensors_col, DATA_TYPE val) :
m_channels(tensors_count), m_rows(tensors_row), m_cols(tensors_col)
{
	if (0 >= m_channels){
		DEBUG_PRINT("0 >= m_tensors_count\n");
		return;
	}

	mp_matrixes = new matrix[m_channels];
	if (NULL == mp_matrixes){
		DEBUG_PRINT("NULL == mp_tensors\n");
		return;
	}

	if (0 == m_rows || 0 == m_cols){
		DEBUG_PRINT("0 == m_tensors_row || 0 == m_tensors_col\n");
		mp_matrixes = NULL;
		return;
	}

	if (0 > m_rows || 0 > m_cols){
		DEBUG_PRINT("0 > m_tensors_row || 0 > m_tensors_col\n");
		mp_matrixes = NULL;
		return;
	}

	for (int i = 0; i < m_channels; ++i){
		mp_matrixes[i] = matrix(m_rows, m_cols, val);
	}
	return;
}

features::features(int channels, int rows, int cols, int min, int max) :\
m_channels(channels), m_rows(rows), m_cols(cols)
{
	if (0 >= m_channels){
		DEBUG_PRINT("0 >= m_tensors_count\n");
		return;
	}

	mp_matrixes = new matrix[m_channels];
	if (NULL == mp_matrixes){
		DEBUG_PRINT("NULL == mp_tensors\n");
		return;
	}

	if (0 == m_rows || 0 == m_cols){
		DEBUG_PRINT("0 == m_tensors_row || 0 == m_tensors_col\n");
		mp_matrixes = NULL;
		return;
	}

	if (0 > m_rows || 0 > m_cols){
		DEBUG_PRINT("0 > m_tensors_row || 0 > m_tensors_col\n");
		mp_matrixes = NULL;
		return;
	}

	for (int i = 0; i < m_channels; ++i){
		mp_matrixes[i] = matrix(m_rows, m_cols, min, max);
	}
	return;
}

features::features(int tensors_count, int tensors_row, int tensors_col, DATA_TYPE min, DATA_TYPE max) :\
m_channels(tensors_count), m_rows(tensors_row), m_cols(tensors_col)
{
	if (0 >= m_channels){
		DEBUG_PRINT("0 >= m_tensors_count\n");
		return;
	}

	mp_matrixes = new matrix[m_channels];
	if (NULL == mp_matrixes){
		DEBUG_PRINT("NULL == mp_tensors\n");
		return;
	}

	if (0 == m_rows || 0 == m_cols){
		DEBUG_PRINT("0 == m_tensors_row || 0 == m_tensors_col\n");
		mp_matrixes = NULL;
		return;
	}

	if (0 > m_rows || 0 > m_cols){
		DEBUG_PRINT("0 > m_tensors_row || 0 > m_tensors_col\n");
		mp_matrixes = NULL;
		return;
	}

	for (int i = 0; i < m_channels; ++i){
		mp_matrixes[i] = matrix(m_rows, m_cols, min, max);
	}
	return;
}

features::~features(){
	if (NULL == mp_matrixes){
		return;
	}

	if (m_channels <= 0 || m_rows <= 0 || m_cols <= 0){
		return;
	}

	delete[] mp_matrixes;
	//for (int i = 0; i < m_kers_counts; ++i){
	//    DEBUG_PRINT("i=%d\n", i);
	//    delete (m_p_kernels + i);/* todo */
	//}
	//delete m_p_kernels;
	return;

}

bool features::show(int show_image_mode){
	if (0 >= m_rows || 0 >= m_cols){
		DEBUG_PRINT("bool features::show() \n \
					0 >= m_features_row || 0 >= m_features_col\n");
		return false;
	}

	if (0 >= m_channels){
		DEBUG_PRINT("bool features::show()\n  0>= m_channels\n");
		return false;
	}
	//DEBUG_PRINT("\n\n\ntensor row=%d  col=%d  \n", m_rows, m_cols);
	std::cout << "features" << std::endl;
	for (int i = 0; i < m_channels; ++i){
		DEBUG_PRINT("matrix(feature) %3d\n", i);
		mp_matrixes[i].show(show_image_mode);
	}
	std::cout << std::endl << std::endl;
	return true;
}

features::features(const cv::Mat &image, DATA_TYPE translation, DATA_TYPE scale){
	//int img_channels = image.channels();
	this->m_channels = image.channels();
	this->m_rows = image.rows;
	this->m_cols = image.cols;

	this->mp_matrixes = new matrix[m_channels];

	if (NULL == mp_matrixes){
		DEBUG_PRINT("NULL == mp_tensors\n");
		return;
	}

	for (int i = 0; i < m_channels; ++i){
		mp_matrixes[i] = \
			matrix(m_rows, m_cols, DATA_TYPE(0.0));
	}

	int k = 0;
	switch (m_channels)
	{
	case 1:
		//int k = -1;
		for (int i = 0; i < m_rows; ++i){
			for (int j = 0; j < m_cols; ++j){
				mp_matrixes[0].mp_data[k] = \
					DATA_TYPE((int)image.at<uchar>(i, j)) - translation;
				mp_matrixes[0].mp_data[k] *= scale;
				++k;
				//
			}
		}
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	default:
		break;
	}
	return;
}

//bool tensor::reshape(int kernels_width, int kernels_height, int stride, int padding_mode){
//	return true;
//}

features::features(const features& ts_){
 //   m_channels = ts_.m_channels;
	//m_rows = ts_.m_rows;
	//m_cols = ts_.m_cols;
	if (NULL == mp_matrixes){
		DEBUG_PRINT("(NULL == mp_matrixes)   features(const features& ts_)\n");
	}
	else{
		if (m_channels == ts_.m_channels&&m_rows*m_cols == ts_.m_rows*ts_.m_cols){
			;/* 内存一致，不重新申请空间 */
		}
		else{
			if (NULL == mp_matrixes){
				;
			}
			else{
				delete[] mp_matrixes;
			}
			mp_matrixes = new matrix[m_channels];
		}
	}
	if (NULL == mp_matrixes){
		DEBUG_PRINT("(NULL == mp_matrixes) features(const features&) \n");
		return;
	}
	for (int i = 0; i < m_channels; ++i){
		mp_matrixes[i] = ts_.mp_matrixes[i];
	}
}

features& features::operator=(const features &fs_){
	if (this == &fs_){
		return *this;
	}
	
	if (NULL == fs_.mp_matrixes){
		std::cout << "(NULL == ts_.mp_matrixes)  tensor::operator=\n";
		if (NULL == mp_matrixes){
			m_channels = m_rows = m_cols = 0;
			return *this;
		}
		else{
			delete[] mp_matrixes;
			mp_matrixes = NULL;
			m_channels = m_rows = m_cols = 0;
			return *this;
		}
	}

	if (NULL != mp_matrixes){
		if (m_channels == fs_.m_channels&&m_rows*m_cols == fs_.m_rows*fs_.m_cols){
			;
		}
		else{
			delete[] mp_matrixes;
			mp_matrixes = NULL;
		}
	}

	m_channels = fs_.m_channels;
	m_rows = fs_.m_rows;
	m_cols = fs_.m_cols;

	mp_matrixes = new matrix[m_channels];
	for (int i = 0; i < m_channels; i++){
		mp_matrixes[i] = fs_.mp_matrixes[i];
	}

	return *this;
}
