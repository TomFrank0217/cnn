#include "kernels.h"

kernels::kernels(){
	mp_tensors0 = NULL;
	mp_tensors1 = NULL;
	m_channels = 0;
	m_rows = 0;
	m_cols = 0;
	m_kernels_count = 0;
	m_kernels_matrix = matrix();
}

kernels::kernels(int channels, int rows, int cols, int kernels_count, int val):\
m_channels(channels),m_rows(rows),m_cols(cols),m_kernels_count(kernels_count){
	if (0 >= channels || 0 >= rows || 0 >= cols || 0 >= kernels_count){
		DEBUG_PRINT("(0 >= channels || 0 >= rows || 0 >= cols || 0 >= kernels_count) \n \
					kernels(int channels, int rows, int cols, int kernels_count, int val)");
	}

	int kernels_matrix_rows = m_rows*m_cols*m_channels;
	int kernels_matrix_cols = m_kernels_count;
	m_kernels_matrix = matrix(kernels_matrix_rows, kernels_matrix_cols);

	mp_tensors0 = NULL;
	mp_tensors1 = NULL;
	mp_tensors0 = new tensor[kernels_count];
	mp_tensors1 = new tensor[kernels_count];
	if (NULL == mp_tensors0 || NULL == mp_tensors1){
		DEBUG_PRINT("(NULL == mp_tensors0||NULL==mp_tensors1) \n \
		      kernels(int channels, int rows, int cols, int kernels_count, int val)");
	}

	for (int i = 0; i < kernels_count; ++i){
		mp_tensors0[i] = tensor(channels, rows, cols, val);
		mp_tensors1[i] = tensor(channels, rows, cols, val);
	}
}

kernels::kernels(int channels, int rows, int cols, int kernels_count, DATA_TYPE val):\
m_channels(channels), m_rows(rows), m_cols(cols), m_kernels_count(kernels_count){
	if (0 >= channels || 0 >= rows || 0 >= cols || 0 >= kernels_count){
		DEBUG_PRINT("(0 >= channels || 0 >= rows || 0 >= cols || 0 >= kernels_count) \n \
					 kernels(int channels, int rows, int cols, int kernels_count, DATA_TYPE val)");
	}

	int kernels_matrix_rows = m_rows*m_cols*m_channels;
	int kernels_matrix_cols = m_kernels_count;
	m_kernels_matrix = matrix(kernels_matrix_rows, kernels_matrix_cols);

	mp_tensors0 = NULL;
	mp_tensors1 = NULL;
	mp_tensors0 = new tensor[kernels_count];
	mp_tensors1 = new tensor[kernels_count];
	if (NULL == mp_tensors0 || NULL == mp_tensors1){
		DEBUG_PRINT("(NULL == mp_tensors0 || NULL == mp_tensors1) \n \
					 kernels(int channels, int rows, int cols, int kernels_count, DATA_TYPE val)");
	}

	for (int i = 0; i < kernels_count; ++i){
		mp_tensors0[i] = tensor(channels, rows, cols, val);
		mp_tensors1[i] = tensor(channels, rows, cols, val);
	}
}

kernels::kernels(int channels, int rows, int cols, int kernels_count, int min, int max):\
m_channels(channels), m_rows(rows), m_cols(cols), m_kernels_count(kernels_count){
	if (0 >= channels || 0 >= rows || 0 >= cols || 0 >= kernels_count){
		DEBUG_PRINT("(0 >= channels || 0 >= rows || 0 >= cols || 0 >= kernels_count) \n \
					kernels(int channels, int rows, int cols, int kernels_count, int min, int max)");
	}

	int kernels_matrix_rows = m_rows*m_cols*m_channels;
	int kernels_matrix_cols = m_kernels_count;
	m_kernels_matrix = matrix(kernels_matrix_rows, kernels_matrix_cols);

	mp_tensors0 = NULL;
	mp_tensors1 = NULL;
	mp_tensors0 = new tensor[kernels_count];
	mp_tensors1 = new tensor[kernels_count];
	if (NULL == mp_tensors0 || NULL == mp_tensors1){
		DEBUG_PRINT("(NULL == mp_tensors0 || NULL == mp_tensors1) \n \
					  kernels(int channels, int rows, int cols, int kernels_count, int min, int max)");
	}

	for (int i = 0; i < kernels_count; ++i){
		mp_tensors0[i] = tensor(channels, rows, cols, min, max);
		mp_tensors1[i] = tensor(channels, rows, cols, min, max);
	}
}

kernels::kernels(int channels, int rows, int cols, int kernels_count, DATA_TYPE min, DATA_TYPE max):\
m_channels(channels), m_rows(rows), m_cols(cols), m_kernels_count(kernels_count){
	if (0 >= channels || 0 >= rows || 0 >= cols || 0 >= kernels_count){
		DEBUG_PRINT("(0 >= channels || 0 >= rows || 0 >= cols || 0 >= kernels_count) \n \
					kernels(int channels, int rows, int cols, int kernels_count, DATA_TYPE min, DATA_TYPE max)");
	}

	int kernels_matrix_rows = m_rows*m_cols*m_channels;
	int kernels_matrix_cols = m_kernels_count;
	m_kernels_matrix = matrix(kernels_matrix_rows, kernels_matrix_cols);

	mp_tensors0 = NULL;
	mp_tensors1 = NULL;
	mp_tensors0 = new tensor[kernels_count];
	mp_tensors1 = new tensor[kernels_count];
	if (NULL == mp_tensors0 || NULL != mp_tensors1){
		DEBUG_PRINT("(NULL == mp_tensors) \n \
					 kernels(int channels, int rows, int cols, int kernels_count, DATA_TYPE min, DATA_TYPE max)");
	}

	for (int i = 0; i < kernels_count; ++i){
		mp_tensors0[i] = tensor(channels, rows, cols, min, max);
		mp_tensors1[i] = tensor(channels, rows, cols, min, max);
	}
}


kernels::~kernels(){
	if (NULL != mp_tensors0){
		delete[] mp_tensors0;
		mp_tensors0 = NULL;
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

bool kernels::show(int image_show_mode){
	for (int i = 0; i < m_kernels_count; ++i){
		std::cout << "kernels" << i << std::endl;
		mp_tensors0[i].show(image_show_mode);
		std::cout << std::endl;
	}
	return true;
}

kernels::kernels(const kernels &ker_){
	m_channels = ker_.m_channels;
	m_rows = ker_.m_rows;
	m_cols = ker_.m_cols;
	m_kernels_count = ker_.m_kernels_count;
	if (NULL != mp_tensors0||NULL!=mp_tensors1){
		delete[] mp_tensors0;
		mp_tensors0 = NULL;
		delete[] mp_tensors1;
		mp_tensors1 = NULL;
	}
	m_kernels_matrix = ker_.m_kernels_matrix;
	mp_tensors0 = new tensor[m_kernels_count];
	mp_tensors1 = new tensor[m_kernels_count];
	if (NULL == mp_tensors0 || NULL == mp_tensors1){
		DEBUG_PRINT("(NULL == mp_tensors0 || NULL == mp_tensors1)\n");
		return;
	}
	for (int i = 0; i < m_kernels_count; ++i){
		mp_tensors0[i] = ker_.mp_tensors0[i];
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
	m_kernels_count = ker_.m_kernels_count;
	m_kernels_matrix = ker_.m_kernels_matrix;

	if (NULL != mp_tensors0 || NULL != mp_tensors1){
		delete[] mp_tensors0;
		mp_tensors0 = NULL;
		delete[] mp_tensors1;
		mp_tensors1 = NULL;
	}

	mp_tensors0 = new tensor[m_kernels_count];
	mp_tensors1 = new tensor[m_kernels_count];

	for (int i = 0; i < m_kernels_count; ++i){
		mp_tensors0[i] = ker_.mp_tensors0[i];
		mp_tensors1[i] = ker_.mp_tensors1[i];
	}
}

bool kernels::reshape(int mode){
	switch(mode)
	{
	case MATRIEX2KERNELS:
		int kernels_matrix_rows = m_rows*m_cols*m_channels;
		int kernels_matrix_cols = m_kernels_count;
		m_kernels_matrix = matrix(kernels_matrix_rows, kernels_matrix_cols);
		/* kernels是个四维张量，要确定m_kernels_matrix（i，j）
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
		mp_tensors1 = new tensor[m_kernels_count];
		if (NULL != mp_tensors0){
			for (int i = 0; i < m_kernels_count; ++i){
				*(mp_tensors1 + i) = *(mp_tensors0 + i);
			}
		}
		else{
			std::cout << "if (NULL != mp_tensors0)\n \
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
					= m_kernels_matrix.mp_data[i*kernels_matrix_cols + j];
			}
		}
		/* 以上是核心代码 */
		break;
		/* (R,C,r,c)->(i,j)
		(ROW,COL,row,col->(kernels_matrix.row, kernels_matrix.col)) */
	case KERNELS2MATRIEX:
		int ROWS = m_channels;
		int COLS = m_kernels_count;
		int rows = m_rows;
		int cols = m_cols;
		int i = 0;
		int j = 0;
		/* todo 此处代码可以优化 for example 交换 R C 的循环顺序 */
		for (int R = 0; R < ROWS; ++R){
			for (int C = 0; C < COLS; ++C){
				for (int r = 0; r < rows; ++r){
					for (int c = 0; c < cols; ++c){
						i = R*rows*cols + r*cols + c;
						j = C;
						m_kernels_matrix.mp_data[i*m_kernels_matrix.m_cols + j] = \
							mp_tensors0[C].mp_matrixes[R].mp_data[r*cols + c];
					}
				}
			}
		}
		/* 此处是核心代码 */
		break;
	default:
		std::cout << "bool kernels::reshape(int mode)\n default\n";
		break;
	}

	return true;
}