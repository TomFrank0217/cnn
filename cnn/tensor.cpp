#include "tensor.h"

tensor::tensor(int tensors_count, int tensors_row, int tensors_col, int val) :
m_tensors_count(tensors_count), m_tensors_row(tensors_row), m_tensors_col(tensors_col)
{
	if (0 >= m_tensors_count){
		DEBUG_PRINT("0 >= m_tensors_count\n");
		return;
	}

	mp_tensors = new matrix[m_tensors_count];
	if (NULL == mp_tensors){
		DEBUG_PRINT("NULL == mp_tensors\n");
		return;
	}

	if (0 == m_tensors_row || 0 == m_tensors_col){
		DEBUG_PRINT("0 == m_tensors_row || 0 == m_tensors_col\n");
		mp_tensors = NULL;
		return;
	}

	if (0 > m_tensors_row || 0 > m_tensors_col){
		DEBUG_PRINT("0 > m_tensors_row || 0 > m_tensors_col\n");
		mp_tensors = NULL;
		return;
	}

	for (int i = 0; i < m_tensors_count; ++i){
		mp_tensors[i] = matrix(m_tensors_row, m_tensors_col, val);
	}
	return;
}

tensor::tensor(int tensors_count, int tensors_row, int tensors_col, DATA_TYPE val) :
m_tensors_count(tensors_count), m_tensors_row(tensors_row), m_tensors_col(tensors_col)
{
	if (0 >= m_tensors_count){
		DEBUG_PRINT("0 >= m_tensors_count\n");
		return;
	}

	mp_tensors = new matrix[m_tensors_count];
	if (NULL == mp_tensors){
		DEBUG_PRINT("NULL == mp_tensors\n");
		return;
	}

	if (0 == m_tensors_row || 0 == m_tensors_col){
		DEBUG_PRINT("0 == m_tensors_row || 0 == m_tensors_col\n");
		mp_tensors = NULL;
		return;
	}

	if (0 > m_tensors_row || 0 > m_tensors_col){
		DEBUG_PRINT("0 > m_tensors_row || 0 > m_tensors_col\n");
		mp_tensors = NULL;
		return;
	}

	for (int i = 0; i < m_tensors_count; ++i){
		mp_tensors[i] = matrix(m_tensors_row, m_tensors_col, val);
	}
	return;
}

tensor::tensor(int tensors_count, int tensors_row, int tensors_col, int min, int max) :\
m_tensors_count(tensors_count), m_tensors_row(tensors_row), m_tensors_col(tensors_col)
{
	if (0 >= m_tensors_count){
		DEBUG_PRINT("0 >= m_tensors_count\n");
		return;
	}

	mp_tensors = new matrix[m_tensors_count];
	if (NULL == mp_tensors){
		DEBUG_PRINT("NULL == mp_tensors\n");
		return;
	}

	if (0 == m_tensors_row || 0 == m_tensors_col){
		DEBUG_PRINT("0 == m_tensors_row || 0 == m_tensors_col\n");
		mp_tensors = NULL;
		return;
	}

	if (0 > m_tensors_row || 0 > m_tensors_col){
		DEBUG_PRINT("0 > m_tensors_row || 0 > m_tensors_col\n");
		mp_tensors = NULL;
		return;
	}

	for (int i = 0; i < m_tensors_count; ++i){
		mp_tensors[i] = matrix(m_tensors_row, m_tensors_col, min, max);
	}
	return;
}

tensor::tensor(int tensors_count, int tensors_row, int tensors_col, DATA_TYPE min, DATA_TYPE max) :\
m_tensors_count(tensors_count), m_tensors_row(tensors_row), m_tensors_col(tensors_col)
{
	if (0 >= m_tensors_count){
		DEBUG_PRINT("0 >= m_tensors_count\n");
		return;
	}

	mp_tensors = new matrix[m_tensors_count];
	if (NULL == mp_tensors){
		DEBUG_PRINT("NULL == mp_tensors\n");
		return;
	}

	if (0 == m_tensors_row || 0 == m_tensors_col){
		DEBUG_PRINT("0 == m_tensors_row || 0 == m_tensors_col\n");
		mp_tensors = NULL;
		return;
	}

	if (0 > m_tensors_row || 0 > m_tensors_col){
		DEBUG_PRINT("0 > m_tensors_row || 0 > m_tensors_col\n");
		mp_tensors = NULL;
		return;
	}

	for (int i = 0; i < m_tensors_count; ++i){
		mp_tensors[i] = matrix(m_tensors_row, m_tensors_col, min, max);
	}
	return;
}

tensor::~tensor(){
	if (NULL == mp_tensors){
		return;
	}

	if (m_tensors_count <= 0 || m_tensors_row <= 0 || m_tensors_col <= 0){
		return;
	}

	delete[] mp_tensors;
	//for (int i = 0; i < m_kernels_count; ++i){
	//    DEBUG_PRINT("i=%d\n", i);
	//    delete (m_p_kernels + i);/* todo */
	//}
	//delete m_p_kernels;
	return;

}

bool tensor::show(int show_image_mode){
	if (0 >= m_tensors_row || 0 >= m_tensors_col){
		DEBUG_PRINT("bool tensor::show() \n \
					0 >= m_tensors_row || 0 >= m_tensors_col\n");
		return false;
	}

	if (0 >= m_tensors_count){
		DEBUG_PRINT("bool tensor::show()\n  \0 >= m_kernels_count");
		return false;
	}

	for (int i = 0; i < m_tensors_count; ++i){
		DEBUG_PRINT("tensor %3d\n", i);
		mp_tensors[i].show(show_image_mode);
	}

	return true;
}

tensor::tensor(const cv::Mat &image, DATA_TYPE translation, DATA_TYPE scale){
	//int img_channels = image.channels();
	this->m_tensors_count = image.channels();
	this->m_tensors_row = image.rows;
	this->m_tensors_col = image.cols;

	this->mp_tensors = new matrix[m_tensors_count];

	if (NULL == mp_tensors){
		DEBUG_PRINT("NULL == mp_tensors\n");
		return;
	}

	for (int i = 0; i < m_tensors_count; ++i){
		mp_tensors[i] = \
			matrix(m_tensors_row, m_tensors_col, DATA_TYPE(0.0));
	}

	int k = 0;
	switch (m_tensors_count)
	{
	case 1:
		//int k = -1;
		for (int i = 0; i < m_tensors_row; ++i){
			for (int j = 0; j < m_tensors_col; ++j){
				mp_tensors[0].m_p_data[k] = \
					DATA_TYPE((int)image.at<uchar>(i, j)) - translation;
				mp_tensors[0].m_p_data[k] *= scale;
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
