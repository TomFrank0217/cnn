#include "tensor.h"

tensor::tensor(){
	this->m_rows = 0;
	this->m_cols = 0;
	this->m_channels = 0;
	this->mp_matrixes = NULL;
}

tensor::tensor(int channels, int rows, int cols, int val) :
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

tensor::tensor(int tensors_count, int tensors_row, int tensors_col, DATA_TYPE val) :
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

tensor::tensor(int channels, int rows, int cols, int min, int max) :\
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

tensor::tensor(int tensors_count, int tensors_row, int tensors_col, DATA_TYPE min, DATA_TYPE max) :\
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

tensor::~tensor(){
	if (NULL == mp_matrixes){
		return;
	}

	if (m_channels <= 0 || m_rows <= 0 || m_cols <= 0){
		return;
	}

	delete[] mp_matrixes;
	//for (int i = 0; i < m_kernels_count; ++i){
	//    DEBUG_PRINT("i=%d\n", i);
	//    delete (m_p_kernels + i);/* todo */
	//}
	//delete m_p_kernels;
	return;

}

bool tensor::show(int show_image_mode){
	if (0 >= m_rows || 0 >= m_cols){
		DEBUG_PRINT("bool tensor::show() \n \
					0 >= m_tensors_row || 0 >= m_tensors_col\n");
		return false;
	}

	if (0 >= m_channels){
		DEBUG_PRINT("bool tensor::show()\n  \0 >= m_kernels_count");
		return false;
	}

	for (int i = 0; i < m_channels; ++i){
		DEBUG_PRINT("tensor %3d\n", i);
		mp_matrixes[i].show(show_image_mode);
	}

	return true;
}

tensor::tensor(const cv::Mat &image, DATA_TYPE translation, DATA_TYPE scale){
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