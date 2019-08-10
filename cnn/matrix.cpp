#include "matrix.h"
#include <iostream>
#include <iomanip>
#include "const_values.h"

matrix::matrix(int rows, int cols, int val):\
m_rows(rows), m_cols(cols)
{
    if (0 == rows && 0 == cols){
        mp_data = NULL;
        return;
    }
    if (rows <= 0 || cols <= 0){
        DEBUG_PRINT("matrix::matrix(int rows, int cols)\nrows <= 0 || cols <= 0\n");
    }
	m_rows = rows;
	m_cols = cols;
    mp_data = new DATA_TYPE[m_rows * m_cols];
    //DEBUG_PRINT("m_p_matrix = new DATA_TYPE[rows * cols];\n");/* to delete */
    if (NULL == mp_data){
        DEBUG_PRINT("matrix::matrix(int rows, int cols)\nNULL == m_p_data\n");
    }
    //memset(m_p_matrix, val, m_rows*m_cols*sizeof(DATA_TYPE));
    int n = m_rows*m_cols;
    for (int i = 0; i < n; ++i){
        mp_data[i] = val;
    }
}

matrix::matrix(int rows, int cols, int low, int high){
    if (rows <= 0 || cols <= 0){
        DEBUG_PRINT("matrix::matrix(int rows, int cols)\nrows <= 0 || cols <= 0\n");
    }
    m_rows = rows;
    m_cols = cols;
    mp_data = new DATA_TYPE[rows * cols];
    if (NULL == mp_data){
        DEBUG_PRINT("matrix::matrix(int rows, int cols)\nNULL == m_p_data\n");
    }

    if (low > high){
        DEBUG_PRINT("low > high\nNULL  \
                    matrix(int rows, int cols, int low, int high)\n");
    }
    srand(time(0));
    int mod_num = high - low + 1;
    int k = 0;
    for (int i = 0; i < m_rows; ++i){
        for (int j = 0; j < m_cols; ++j){
            mp_data[k++] = rand() % mod_num + low;
        }
    }
}

matrix::matrix(int rows, int cols, DATA_TYPE val):
m_rows(rows),m_cols(cols)
{
    if (rows <= 0 || cols <= 0){
        DEBUG_PRINT("matrix::matrix(int rows, int cols)\nrows <= 0 || cols <= 0\n");
    }

    mp_data = new DATA_TYPE[rows * cols];

    if (NULL == mp_data){
        DEBUG_PRINT("matrix::matrix(int rows, int cols)\nNULL == m_p_data\n");
    }

    int n = m_rows*m_cols;
    for (int i = 0; i < n; ++i){
        mp_data[i] = val;
    }
}

matrix::matrix(int rows, int cols, DATA_TYPE low, DATA_TYPE high):\
m_rows(rows),m_cols(cols)
{

    if (rows <= 0 || cols <= 0){
        DEBUG_PRINT("matrix::matrix(int rows, int cols)\nrows <= 0 || cols <= 0\n");
    }

    mp_data = new DATA_TYPE[rows * cols];
    if (NULL == mp_data){
        DEBUG_PRINT("matrix::matrix(int rows, int cols)\nNULL == m_p_data\n");
    }
    
    srand( (unsigned int) (time(0)) );
    int element_counts = rows*cols;
    DATA_TYPE rand_num = DATA_TYPE(0);
    DATA_TYPE scale = DATA_TYPE(0.0);
    DATA_TYPE slope = 0.0;
    slope = (high - low) / DATA_TYPE(RAND_MAX - 1.0);
    for (int i = 0; i < element_counts; ++i){
        rand_num = DATA_TYPE(rand());
        mp_data[i] = slope*rand_num + low;
    }
}

matrix::matrix(const matrix &A):\
m_rows(A.m_rows),m_cols(A.m_cols)
{
    DEBUG_PRINT("matrix::matrix(const matrix &A) called\n");
    if (A.m_rows <= 0 || A.m_cols <= 0){
        DEBUG_PRINT("matrix::matrix(const matrix &A)\n A.m_rows <= 0 || A.m_cols <= 0\n");
    }

    if (NULL == A.mp_data){
        DEBUG_PRINT("matrix::matrix(const matrix &A)\n NULL == m_p_data\n");
    }
    
    mp_data = new DATA_TYPE[m_rows*m_cols];
    if (NULL == mp_data){
        DEBUG_PRINT("matrix::matrix(const matrix &A)\n NULL == m_p_data\n");
    }

    int element_counts = m_rows*m_cols;
    for (int i = 0; i < element_counts; ++i){
        mp_data[i] = A.mp_data[i];
    }
}

matrix matrix::operator+(const matrix & addition_matrix){
    if (m_rows <= 0 || m_cols <= 0){
        DEBUG_PRINT("m_rows <= 0 || m_cols <= 0  matrix::operator+\n");
    }

    if (addition_matrix.m_rows <= 0 || addition_matrix.m_cols <= 0){
        DEBUG_PRINT("addition_matrix.m_rows <= 0 || addition_matrix.m_cols <= 0  \
                    matrix::operator+\n");
    }

    if (NULL == mp_data){
        DEBUG_PRINT("NULL == m_p_data  matrix::operator+\n");
    }

    if (NULL == addition_matrix.mp_data){
        DEBUG_PRINT("NULL == addition_matrix.m_p_data  matrix::operator+\n");
    }

    if (m_rows != addition_matrix.m_rows || m_cols != addition_matrix.m_cols){
        DEBUG_PRINT("m_rows != addition_matrix.m_rows || m_cols != addition_matrix.m_cols \
                    matrix::operator+\n");
    }

    matrix sum_matrix(*this);

    int k = 0;
    for (int i = 0; i < m_rows; ++i){
        for (int j = 0; j < m_cols; ++j){
            sum_matrix.mp_data[k] += addition_matrix.mp_data[k];
            ++k;
        }
    }

    return sum_matrix;
}

matrix matrix::operator+(DATA_TYPE addition_num){
	if (m_rows <= 0 || m_cols <= 0){
		DEBUG_PRINT("m_rows <= 0 || m_cols <= 0  matrix::operator+\n");
	}

	if (NULL == mp_data){
		DEBUG_PRINT("NULL == mp_data  matrix::operator+\n");
	}

	matrix sum_matrix(*this);

	int k = 0;
	for (int i = 0; i < m_rows; ++i){
		for (int j = 0; j < m_cols; ++j){
			sum_matrix.mp_data[k] += addition_num;
			++k;
		}
	}

	return sum_matrix;
}


matrix matrix::operator-(const matrix &reduction_matrix){

	if (m_rows <= 0 || m_cols <= 0){
		DEBUG_PRINT("m_rows <= 0 || m_cols <= 0  matrix::operator+\n");
	}

	if (reduction_matrix.m_rows <= 0 || reduction_matrix.m_cols <= 0){
		DEBUG_PRINT("reduction_matrix.m_rows <= 0 || reduction_matrix.m_cols <= 0  \
																matrix::operator+\n");
	}

	if (NULL == mp_data){
		DEBUG_PRINT("null == m_p_data  matrix::operator+\n");
	}

	if (NULL == reduction_matrix.mp_data){
		DEBUG_PRINT("null == reduction_matrix.m_p_data  matrix::operator+\n");
	}

	if (m_rows != reduction_matrix.m_rows || m_cols != reduction_matrix.m_cols){
		DEBUG_PRINT("m_rows != reduction_matrix.m_rows || m_cols != reduction_matrix.m_cols \
									matrix::operator+\n");
	}

	matrix minuend_matrix(*this);

	int k = 0;
	for (int i = 0; i < m_rows; ++i){
		for (int j = 0; j < m_cols; ++j){
			minuend_matrix.mp_data[k] -= reduction_matrix.mp_data[k];
			++k;
		}
	}

	return minuend_matrix;
}

matrix matrix::operator-(DATA_TYPE reduction_num){
	if (m_rows <= 0 || m_cols <= 0){
		DEBUG_PRINT("m_rows <= 0 || m_cols <= 0  matrix::operator+\n");
	}

	if (NULL == mp_data){
		DEBUG_PRINT("NULL == mp_data  matrix::operator+\n");
	}

	matrix reduction_matrix(*this);

	int k = 0;
	for (int i = 0; i < m_rows; ++i){
		for (int j = 0; j < m_cols; ++j){
			reduction_matrix.mp_data[k] -= reduction_num;
			++k;
		}
	}

	return reduction_matrix;
}

matrix matrix::operator*(const DATA_TYPE val){
	if (m_rows <= 0 || m_cols <= 0){
		DEBUG_PRINT("m_rows <= 0 || m_cols <= 0  matrix::operator*\n");
	}

	if (NULL == mp_data){
		DEBUG_PRINT("NULL == mp_data  matrix::operator*\n");
	}

	matrix multiplier_matrix(*this);
	int elements_count = this->m_rows*this->m_cols;
	DATA_TYPE *p_data = multiplier_matrix.mp_data;
	for (int i = 0; i < elements_count; ++i){
		p_data[i] *= val;
	}

	return multiplier_matrix;
}

matrix matrix::operator*(const matrix &multiplier_matrix){
    if (m_rows <= 0 || m_cols <= 0){
        DEBUG_PRINT("m_rows <= 0 || m_cols <= 0  matrix::operator+\n");
    }

    if (multiplier_matrix.m_rows <= 0 || multiplier_matrix.m_cols <= 0){
        DEBUG_PRINT("multiplier_matrix.m_rows <= 0 || multiplier_matrix.m_cols <= 0  \
                                         matrix::operator+\n");
    }

    if (NULL == mp_data){
        DEBUG_PRINT("NULL == m_p_data  matrix::operator+\n");
    }

    if (NULL == multiplier_matrix.mp_data){
        DEBUG_PRINT("NULL == multiplier_matrix.m_p_data  matrix::operator+\n");
    }

    if (this->m_cols != multiplier_matrix.m_rows){
        DEBUG_PRINT("this->m_cols != multiplier_matrix.m_rows  \n \
					matrix::operator*(const matrix &multiplier_matrix)\n");
    }

    matrix product_matrix(this->m_rows, multiplier_matrix.m_cols, 0.0);

    int s = 0, t = 0, r = 0;
    for (int i = 0; i < product_matrix.m_rows; ++i){
        for (int k = 0; k < product_matrix.m_cols; ++k){
            product_matrix.mp_data[s] = 0.0;
            int j = 0;
            t = i*this->m_cols;
            for (j = 0; j < this->m_cols; ++j){
                r = j*multiplier_matrix.m_cols;
                product_matrix.mp_data[s] += \
                    this->mp_data[t++] * multiplier_matrix.mp_data[r + k];
            }
            ++s;
        }
    }

    return product_matrix;
}

matrix::~matrix(){
    if (m_rows <= 0 || m_cols <= 0){
        DEBUG_PRINT("m_rows <= 0 || m_cols <= 0  matrix::~matrix()\n");
    }

    if (NULL == mp_data){
        DEBUG_PRINT("NULL == m_p_data  matrix::~matrix()\n");
    }

    DEBUG_PRINT("matrix destructor called.\n");
    delete[] mp_data;
}

matrix& matrix::operator=(const matrix &A){

    //DEBUG_PRINT("matrix matrix::operator = (const matrix &A)\n");
    if (this == &A){
        return *this;
    }

    delete[] mp_data;
    mp_data = NULL;
    this->m_rows = A.m_rows;
    this->m_cols = A.m_cols;

    mp_data = new DATA_TYPE[m_rows*m_cols];
    int n = m_rows*m_cols;
    for (int i = 0; i < n; ++i){
        mp_data[i] = A.mp_data[i];
    }

    return *this;
}

bool matrix::show(int show_image_mode){
	if (m_rows <= 0 || m_cols <= 0 || NULL == mp_data){
		DEBUG_PRINT("(m_rows <= 0 || m_cols <= 0 || NULL == m_p_data)    \
										                                        matrix::show()");
		return false;
	}

	int num = 0;
	int k = -1;

	//std::string  zero_str = "  ", nonzero_str = "**";
	std::string str;
	switch (show_image_mode)
	{
	case SHOW_IMAGE_SHAPE:
		for (int i = SHOW_IAMGE_CROP_LENGTH; i < m_rows - SHOW_IAMGE_CROP_LENGTH; ++i){
			for (int j = SHOW_IAMGE_CROP_LENGTH; j < m_cols - SHOW_IAMGE_CROP_LENGTH; ++j){
				if (ABS(AVE_VALUE*(mp_data[i*m_cols + j] + 1.0)) < DELTA)
					std::cout << "  ";
				else
					std::cout << "**";
			}
			std::cout << std::endl;
		}
		break;

	case SHOW_IMAGE_SCALE_VALUE:
		for (int i = SHOW_IAMGE_CROP_LENGTH; i < m_rows - SHOW_IAMGE_CROP_LENGTH; ++i){
			for (int j = SHOW_IAMGE_CROP_LENGTH; j < m_cols - SHOW_IAMGE_CROP_LENGTH; ++j){
				if (ABS(AVE_VALUE*(mp_data[i*m_cols + j] + 1.0)) < DELTA){
					for (int k = 0; k < SHOW_WIDTH; ++k){
						std::cout << " ";
					}
				}
				else{
					std::cout << std::setw(SHOW_WIDTH) << std::setprecision(SHOW_WIDTH / 2 - 1) << mp_data[i*m_cols + j];
				}
			}
			std::cout << std::endl;
		}
		break;

	case SHOW_IMAGE_INITAIL_VALUE:
		for (int i = SHOW_IAMGE_CROP_LENGTH; i < m_rows - SHOW_IAMGE_CROP_LENGTH; ++i){
			for (int j = SHOW_IAMGE_CROP_LENGTH; j < m_cols - SHOW_IAMGE_CROP_LENGTH; ++j){
				//	if ( ABS(mp_data[i*m_cols + j]) < DELTA){
				//		for (int k = 0; k < SHOW_WIDTH; ++k){
				//			std::cout << " ";
				//		}
				//	}
				//	else{
				//		std::cout << std::setw(SHOW_WIDTH) << std::setprecision(SHOW_WIDTH / 2 - 1) << mp_data[i*m_cols + j];
				//	}
				//}
				std::cout << std::setw(4) << std::setprecision(2) << mp_data[i*m_cols + j];
			}
			std::cout << std::endl;
		}
		break;
	default:
		return false;
	}
	std::cout << std::endl;
	return true;
}

matrix operator+(const DATA_TYPE val, const matrix &addition_matrix){
	if (addition_matrix.m_rows <= 0 || addition_matrix.m_cols <= 0){
		DEBUG_PRINT("addition_matrix.m_rows <= 0 || addition_matrix.m_cols <= 0\n \
																				matrix::operator+\n");
	}

	if (NULL == addition_matrix.mp_data){
		DEBUG_PRINT("NULL == addition_matrix.mp_data  matrix::operator+\n");
	}
	matrix sum_matrix(addition_matrix);
	int elements_count = addition_matrix.m_rows*addition_matrix.m_cols;
	DATA_TYPE *p_sum_data = sum_matrix.mp_data;
	for (int i = 0; i < elements_count; ++i){
		p_sum_data[i] += val;
	}

	return sum_matrix;

}


matrix operator-(const DATA_TYPE val, const matrix &reduction_matrix){
	if (reduction_matrix.m_rows <= 0 || reduction_matrix.m_cols <= 0){
		DEBUG_PRINT("reduction_matrix.m_rows <= 0 || reduction_matrix.m_cols <= 0\n \
																				matrix::operator-\n");
	}

	if (NULL == reduction_matrix.mp_data){
		DEBUG_PRINT("NULL == addition_matrix.mp_data  matrix::operator+\n");
	}
	matrix result_matrix(reduction_matrix.m_rows, reduction_matrix.m_cols, val);
	int elements_count = reduction_matrix.m_rows*reduction_matrix.m_cols;
	DATA_TYPE *p_result_data = result_matrix.mp_data;
	for (int i = 0; i < elements_count; ++i){
		p_result_data[i] -= val;
	}

	return result_matrix;
}

matrix operator*(const DATA_TYPE val, const matrix &multiplier_matrix){
	if (multiplier_matrix.m_rows <= 0 || multiplier_matrix.m_cols <= 0){
		DEBUG_PRINT("multiplier_matrix.m_rows <= 0 || multiplier_matrix.m_cols <= 0\n \
															matrix::operator*\n");
	}

	if (NULL == multiplier_matrix.mp_data){
		DEBUG_PRINT("NULL == multiplier_matrix.mp_data  matrix::operator*\n");
	}
	matrix result_matrix(multiplier_matrix);
	int elements_count = multiplier_matrix.m_rows*multiplier_matrix.m_cols;
	DATA_TYPE *p_result_data = result_matrix.mp_data;
	for (int i = 0; i < elements_count; ++i){
		p_result_data[i] *= val;
	}

	return result_matrix;
}