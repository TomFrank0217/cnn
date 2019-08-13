#include "kernels.h"

kernels::kernels(){
	mp_kers = NULL;
	mp_tensors1 = NULL;
	m_channels = 0;
	m_rows = 0;
	m_cols = 0;
	m_kers_counts = 0;
	m_kers_mat = matrix();
}

kernels::kernels(int channels, int rows, int cols, int kernels_counts, int val):\
m_channels(channels),m_rows(rows),m_cols(cols),m_kers_counts(kernels_counts){
	if (0 >= channels || 0 >= rows || 0 >= cols || 0 >= kernels_counts){
		DEBUG_PRINT("(0 >= channels || 0 >= rows || 0 >= cols || 0 >= kernels_count) \n \
					kernels(int channels, int rows, int cols, int kernels_count, int val)");
	}

	int kers_mat_rows = m_rows*m_cols*m_channels;
	int kers_mat_cols = m_kers_counts;
	m_kers_mat = matrix(kers_mat_rows, kers_mat_cols);

	mp_kers = NULL;
	mp_tensors1 = NULL;
	mp_kers = new kernel[kernels_counts];
	mp_tensors1 = new kernel[kernels_counts];
	if (NULL == mp_kers || NULL == mp_tensors1){
		DEBUG_PRINT("(NULL == mp_kers||NULL==mp_tensors1) \n \
		      kernels(int channels, int rows, int cols, int kernels_count, int val)");
	}

	for (int i = 0; i < m_kers_counts; ++i){
		mp_kers[i] = kernel(channels, rows, cols, val);
		mp_tensors1[i] = kernel(channels, rows, cols, val);
	}
}

kernels::kernels(int channels, int rows, int cols, int kernels_counts, DATA_TYPE val):\
m_channels(channels), m_rows(rows), m_cols(cols), m_kers_counts(kernels_counts){
	if (0 >= channels || 0 >= rows || 0 >= cols || 0 >= kernels_counts){
		DEBUG_PRINT("(0 >= channels || 0 >= rows || 0 >= cols || 0 >= kernels_count) \n \
					 kernels(int channels, int rows, int cols, int kernels_count, DATA_TYPE val)");
	}

	int kernels_matrix_rows = m_rows*m_cols*m_channels;
	int kernels_matrix_cols = m_kers_counts;
	m_kers_mat = matrix(kernels_matrix_rows, kernels_matrix_cols);

	mp_kers = new kernel[kernels_counts];
	mp_tensors1 = new kernel[kernels_counts];
	if (NULL == mp_kers || NULL == mp_tensors1){
		DEBUG_PRINT("(NULL == mp_kers || NULL == mp_tensors1) \n \
					 kernels(int channels, int rows, int cols, int kernels_count, DATA_TYPE val)");
	}

	for (int i = 0; i < kernels_counts; ++i){
		mp_kers[i] = kernel(channels, rows, cols, val);
		mp_tensors1[i] = kernel(channels, rows, cols, val);
	}
}

kernels::kernels(int channels, int rows, int cols, int kernels_counts, int min, int max):\
m_channels(channels), m_rows(rows), m_cols(cols), m_kers_counts(kernels_counts){
	if (0 >= channels || 0 >= rows || 0 >= cols || 0 >= kernels_counts){
		DEBUG_PRINT("(0 >= channels || 0 >= rows || 0 >= cols || 0 >= kernels_count) \n \
					kernels(int channels, int rows, int cols, int kernels_count, int min, int max)");
	}

	int kernels_matrix_rows = m_rows*m_cols*m_channels;
	int kernels_matrix_cols = m_kers_counts;
	m_kers_mat = matrix(kernels_matrix_rows, kernels_matrix_cols);

	mp_kers = new kernel[kernels_counts];
	mp_tensors1 = new kernel[kernels_counts];
	if (NULL == mp_kers || NULL == mp_tensors1){
		DEBUG_PRINT("(NULL == mp_kers || NULL == mp_tensors1) \n \
					  kernels(int channels, int rows, int cols, int kernels_count, int min, int max)");
	}

	for (int i = 0; i < kernels_counts; ++i){
		mp_kers[i] = kernel(channels, rows, cols, min, max);
		mp_tensors1[i] = kernel(channels, rows, cols, min, max);
	}
}

kernels::kernels(int channels, int rows, int cols, int kernels_count, DATA_TYPE min, DATA_TYPE max):\
m_channels(channels), m_rows(rows), m_cols(cols), m_kers_counts(kernels_count){
	if (0 >= channels || 0 >= rows || 0 >= cols || 0 >= kernels_count){
		DEBUG_PRINT("(0 >= channels || 0 >= rows || 0 >= cols || 0 >= kernels_count) \n \
					kernels(int channels, int rows, int cols, int kernels_count, DATA_TYPE min, DATA_TYPE max)");
	}

	int kernels_matrix_rows = m_rows*m_cols*m_channels;
	int kernels_matrix_cols = m_kers_counts;
	m_kers_mat = matrix(kernels_matrix_rows, kernels_matrix_cols);

	mp_kers = NULL;
	mp_tensors1 = NULL;
	mp_kers = new kernel[kernels_count];
	mp_tensors1 = new kernel[kernels_count];
	if (NULL == mp_kers || NULL != mp_tensors1){
		DEBUG_PRINT("(NULL == mp_tensors) \n \
					 kernels(int channels, int rows, int cols, int kernels_count, DATA_TYPE min, DATA_TYPE max)");
	}

	for (int i = 0; i < kernels_count; ++i){
		mp_kers[i] = kernel(channels, rows, cols, min, max);
		mp_tensors1[i] = kernel(channels, rows, cols, min, max);
	}
}

kernels::~kernels(){
	if (NULL != mp_kers){
		delete[] mp_kers;
		mp_kers = NULL;
	}

	if (NULL != mp_tensors1){
		delete[] mp_tensors1;
		mp_tensors1 = NULL;
	}
}


//bool kernels::reshape(){
	//todo
	//return true;
//}

/* bool show(int image_show_mode = SHOW_IMAGE_INITAIL_VALUE, int mode = MATRIEX2KERNELS) */
bool kernels::show(int image_show_mode, int mode){
	if (KERNELS2MATRIEX == mode){
		std::cout << "kernels\n" << std::endl;
		for (int i = 0; i < m_kers_counts; ++i){
			std::cout << "kernel " << i << std::endl;
			mp_kers[i].show(image_show_mode);
			std::cout << std::endl;
		}
		reshape(KERNELS2MATRIEX);
		m_kers_mat.show(SHOW_IMAGE_INITAIL_VALUE);
	}
	else if (MATRIEX2KERNELS == mode){
		std::cout << "matrix \n" << std::endl;
		m_kers_mat.show(SHOW_IMAGE_INITAIL_VALUE);
		reshape(MATRIEX2KERNELS);
		for (int i = 0; i < m_kers_counts; ++i){
			std::cout << "kernel " << i << std::endl;
			mp_tensors1[i].show(image_show_mode);
			std::cout << std::endl;
		}
	}
	else{

	}


	return true;
}

kernels::kernels(const kernels &ker_){
	m_channels = ker_.m_channels;
	m_rows = ker_.m_rows;
	m_cols = ker_.m_cols;
	m_kers_counts = ker_.m_kers_counts;
	if (NULL != mp_kers||NULL!=mp_tensors1){
		delete[] mp_kers;
		mp_kers = NULL;
		delete[] mp_tensors1;
		mp_tensors1 = NULL;
	}
	m_kers_mat = ker_.m_kers_mat;
	mp_kers = new kernel[m_kers_counts];
	mp_tensors1 = new kernel[m_kers_counts];
	if (NULL == mp_kers || NULL == mp_tensors1){
		DEBUG_PRINT("(NULL == mp_kers || NULL == mp_tensors1)\n");
		return;
	}
	for (int i = 0; i < m_kers_counts; ++i){
		mp_kers[i] = ker_.mp_kers[i];
		mp_tensors1[i] = ker_.mp_tensors1[i];
	}

}
kernels& kernels::operator=(const kernels& ker_){
	if (&ker_ == this){
		return *this;
	}

	m_channels = ker_.m_channels;
	m_rows = ker_.m_rows;
	m_cols = ker_.m_cols;
	m_kers_counts = ker_.m_kers_counts;
	m_kers_mat = ker_.m_kers_mat;

	if (NULL != mp_kers && NULL != mp_tensors1){
		delete[] mp_kers;
		mp_kers = NULL;
		delete[] mp_tensors1;
		mp_tensors1 = NULL;
	}

	mp_kers = new kernel[m_kers_counts];
	mp_tensors1 = new kernel[m_kers_counts];
	if (NULL == mp_kers || NULL == mp_tensors1){
		std::cout << "(NULL == mp_kers || NULL == mp_tensors1)\
					 				\n  kernels::operator= \n";
		return *this;
	}

	for (int i = 0; i < m_kers_counts; ++i){
		mp_kers[i] = ker_.mp_kers[i];
		mp_tensors1[i] = ker_.mp_tensors1[i];
	}
}

bool kernels::reshape(int mode){

	int ROWS = m_channels;
	int COLS = m_kers_counts;
	int rows = m_rows;
	int cols = m_cols;
	int i = 0;
	int j = 0;

	switch(mode)
	{
		/* (R,C,r,c)->(i,j)
		(ROW,COL,row,col->(kernels_matrix.row, kernels_matrix.col)) */
	case KERNELS2MATRIEX:
		/* todo 此处代码可以优化 for example 交换 R C 的循环顺序 */
		for (int R = 0; R < ROWS; ++R){
			for (int C = 0; C < COLS; ++C){
				for (int r = 0; r < rows; ++r){
					for (int c = 0; c < cols; ++c){
						i = R*rows*cols + r*cols + c;
						j = C;
						m_kers_mat.mp_data[i*m_kers_mat.m_cols + j] = \
							mp_kers[C].mp_matrixes[R].mp_data[r*cols + c];
					}
				}
			}
		}
		/* 此处是核心代码 */
		break;
	case MATRIEX2KERNELS:
		int kernels_matrix_rows = m_rows*m_cols*m_channels;
		int kernels_matrix_cols = m_kers_counts;
		//m_kers_mat = matrix(kernels_matrix_rows, kernels_matrix_cols);
		/* kernels是个四维张量，要确定m_kers_mat（i，j）
		在kernels种的具体位置需要一个四维向量（ROW,COL,row,col）
		即确定一个(向量)定位函数loc. st loc(i,j)=（ROW,COL,row,col）*/
		int ROW = 0;
		int COL = 0;
		int row = 0;
		int col = 0;
		int index = 0;
		if (NULL != mp_tensors1){
			delete[] mp_tensors1;
			mp_tensors1 = NULL;
		}
		mp_tensors1 = new kernel[m_kers_counts];
		if (NULL != mp_kers){
			for (int i = 0; i < m_kers_counts; ++i){
				*(mp_tensors1 + i) = *(mp_kers + i);
			}
		}
		else{
			std::cout << "if (NULL != mp_kers)\n \
						 bool kernels::reshape(int mode)\n";
			return false;
		}

		for (int i = 0; i < kernels_matrix_rows; ++i){
			for (int j = 0; j < kernels_matrix_cols; ++j){
				;/* todo 此处代码可以优化 */
				ROW = i / (m_rows*m_cols);
				COL = j;
				index = i - ROW*m_rows*m_cols;
				row = index / m_cols;
				col = index - row*m_cols;
				mp_tensors1[COL].mp_matrixes[ROW].mp_data[row*m_cols + col] \
					= m_kers_mat.mp_data[i*kernels_matrix_cols + j];
			}
		}
		/* 以上是核心代码 */
		break;

	//default:
	//	std::cout << "bool kernels::reshape(int mode)\n default\n";
	//	break;
	}

	return true;
}