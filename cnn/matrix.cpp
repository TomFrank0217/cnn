#include "matrix.h"
#include <iostream>
#include <iomanip>
#include "const_values.h"

int matrix::rand_num = 0;

matrix::matrix(int rows, int cols, int val)
{
    if (0 == rows && 0 == cols){
		m_rows = m_cols = 0;
        mp_data = NULL;
        return;
    }
    if (rows <= 0 || cols <= 0){
		m_rows = m_cols = 0;
		mp_data = NULL;
        DEBUG_PRINT("matrix::matrix(int rows, int cols)\nrows <= 0 || cols <= 0\n");
		return;
    }

	m_rows = rows;
	m_cols = cols;
    mp_data = new DATA_TYPE[m_rows * m_cols];
    //DEBUG_PRINT("m_p_matrix = new DATA_TYPE[rows * cols];\n");/* to delete */
    if (NULL == mp_data){
        DEBUG_PRINT("matrix::matrix(int rows, int cols)\nNULL == mp_data\n");
		return;
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
        DEBUG_PRINT("matrix::matrix(int rows, int cols)\nNULL == mp_data\n");
    }

    if (low > high){
        DEBUG_PRINT("low > high\nNULL  \
                    matrix(int rows, int cols, int low, int high)\n");
    }
    srand(matrix::rand_num++);
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
        DEBUG_PRINT("matrix::matrix(int rows, int cols)\nNULL == mp_data\n");
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
        DEBUG_PRINT("matrix::matrix(int rows, int cols)\nNULL == mp_data\n");
    }
    
    srand(matrix::rand_num++);
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

matrix matrix::operator+(const matrix & add_matrix){
    if (m_rows <= 0 || m_cols <= 0){
        DEBUG_PRINT("m_rows <= 0 || m_cols <= 0  matrix::operator+\n");
    }

    if (add_matrix.m_rows <= 0 || add_matrix.m_cols <= 0){
        DEBUG_PRINT("add_matrix.m_rows <= 0 || add_matrix.m_cols <= 0  \
                    matrix::operator+\n");
    }

    if (NULL == mp_data){
        DEBUG_PRINT("NULL == mp_data  matrix::operator+\n");
    }

    if (NULL == add_matrix.mp_data){
        DEBUG_PRINT("NULL == add_matrix.mp_data  matrix::operator+\n");
    }

    if (m_rows != add_matrix.m_rows || m_cols != add_matrix.m_cols){
        DEBUG_PRINT("m_rows != add_matrix.m_rows || m_cols != add_matrix.m_cols \
                    matrix::operator+\n");
    }

    matrix sum_matrix(*this);

    int k = 0;
    for (int i = 0; i < m_rows; ++i){
        for (int j = 0; j < m_cols; ++j){
            sum_matrix.mp_data[k] += add_matrix.mp_data[k];
            ++k;
        }
    }

    return sum_matrix;
}

bool matrix::operator+=(const matrix&add_matrix){
	if (0 >= m_rows || 0 >= m_cols){
		DEBUG_PRINT("(0 >= m_rows || 0 >= m_cols)  matrix::operator+= \n");
		return false;
	}

	if (0 >= add_matrix.m_rows || 0 >= add_matrix.m_cols){
		DEBUG_PRINT("(0 >= add_matrix.m_rows || 0 >= add_matrix.m_cols)  matrix::operator+= \n");
		return false;
	}

	if (NULL == mp_data||NULL==add_matrix.mp_data){
		DEBUG_PRINT("(NULL == mp_data||NULL==add_matrix.mp_data) matrix::operator+\n");
		return false;
	}
	if (m_rows != add_matrix.m_rows || m_cols != add_matrix.m_cols){
		DEBUG_PRINT("m_rows != add_matrix.m_rows || m_cols != add_matrix.m_cols \
					 matrix::operator+= \n");
		return false;
	}

	int n = m_rows*m_cols;
	DATA_TYPE*pdata = add_matrix.mp_data;
	for (int i = 0; i < n; ++i){
		mp_data[i] += pdata[i];
	}

	return true;
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

bool matrix::operator+=(DATA_TYPE add_num){
	if (m_rows <= 0 || m_cols <= 0){
		DEBUG_PRINT("m_rows <= 0 || m_cols <= 0  matrix::operator+=\n");
		return false;
	}

	if (NULL == mp_data){
		DEBUG_PRINT("NULL == mp_data  matrix::operator+=\n");
		return false;
	}

	int n = m_rows*m_cols;
	for (int i = 0; i < n; ++i){
		mp_data[i] += add_num;
	}

	return true;
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
		DEBUG_PRINT("null == mp_data  matrix::operator+\n");
	}

	if (NULL == reduction_matrix.mp_data){
		DEBUG_PRINT("null == reduction_matrix.mp_data  matrix::operator+\n");
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

bool matrix::operator-=(const matrix& minus_matrix){
	if (0 >= m_rows || 0 >= m_cols){
		DEBUG_PRINT("(0 >= m_rows || 0 >= m_cols)  matrix::operator+= \n");
		return false;
	}

	if (0 >= minus_matrix.m_rows || 0 >= minus_matrix.m_cols){
		DEBUG_PRINT("(0 >= minus_matrix.m_rows || 0 >= minus_matrix.m_cols)  matrix::operator+= \n");
		return false;
	}

	if (NULL == mp_data || NULL == minus_matrix.mp_data){
		DEBUG_PRINT("(NULL == mp_data||NULL==add_matrix.mp_data) matrix::operator+\n");
		return false;
	}
	if (m_rows != minus_matrix.m_rows || m_cols != minus_matrix.m_cols){
		DEBUG_PRINT("m_rows != minus_matrix.m_rows || m_cols != minus_matrix.m_cols \
					matrix::operator+= \n");
		return false;
	}

	int n = m_rows*m_cols;
	DATA_TYPE*pdata = minus_matrix.mp_data;
	for (int i = 0; i < n; ++i){
		mp_data[i] -= pdata[i];
	}

	return true;
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

bool matrix::operator-=(DATA_TYPE add_num){
	if (m_rows <= 0 || m_cols <= 0){
		DEBUG_PRINT("m_rows <= 0 || m_cols <= 0  matrix::operator-=\n");
		return false;
	}

	if (NULL == mp_data){
		DEBUG_PRINT("NULL == mp_data  matrix::operator-=\n");
		return false;
	}

	int n = m_rows*m_cols;
	for (int i = 0; i < n; ++i){
		mp_data[i] -= add_num;
	}

	return true;
}

matrix matrix::operator*(const DATA_TYPE val){
	if (m_rows <= 0 || m_cols <= 0){
		DEBUG_PRINT("m_rows <= 0 || m_cols <= 0  matrix::operator*\n");
	}

	if (NULL == mp_data){
		DEBUG_PRINT("NULL == mp_data  matrix::operator*\n");
	}
	matrix multiplier_matrix(*this);

	int elements_count = m_rows*m_cols;
	DATA_TYPE *p_data = multiplier_matrix.mp_data;
	for (int i = 0; i < elements_count; ++i){
		p_data[i] *= val;
	}

	return multiplier_matrix;
}

bool matrix::operator*=(const DATA_TYPE val){
	if (m_rows <= 0 || m_cols <= 0){
		DEBUG_PRINT("m_rows <= 0 || m_cols <= 0  matrix::operator-=\n");
		return false;
	}

	if (NULL == mp_data){
		DEBUG_PRINT("NULL == mp_data  matrix::operator-=\n");
		return false;
	}

	int n = m_rows*m_cols;
	for (int i = 0; i < n; ++i){
		mp_data[i] *= val;
	}

	return true;
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
        DEBUG_PRINT("NULL == mp_data  matrix::operator+\n");
    }

    if (NULL == multiplier_matrix.mp_data){
        DEBUG_PRINT("NULL == multiplier_matrix.mp_data  matrix::operator+\n");
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
        //DEBUG_PRINT("m_rows <= 0 || m_cols <= 0  matrix::~matrix()\n");
		return;
    }

    if (NULL == mp_data){
        //DEBUG_PRINT("NULL == mp_data  matrix::~matrix()\n");
		return;
    }

    //DEBUG_PRINT("matrix destructor called.\n");
    delete[] mp_data;
	//DEBUG_PRINT("mp_data=%x  ", mp_data);
	//DEBUG_PRINT("mp_data=%x\n", *mp_data);
	mp_data = NULL;
}

matrix& matrix::operator=(const matrix &A){

    if (this == &A){
        return *this;
    }

	if (0 >= A.m_rows || 0 >= A.m_cols || NULL == A.mp_data){
		DEBUG_PRINT("(0 >= A.m_rows || 0 >= A.m_cols)  \
					NULL == A.mp_data matrix::operator= \n");
		m_rows = m_cols = 0;
		if (NULL != mp_data){
			delete[] mp_data;
			mp_data = NULL;
		}
		return *this;
	}
	/* 以下A所有值已经合法 */
	if (NULL == mp_data){
		m_rows = A.m_rows;
		m_cols = A.m_cols;
		mp_data = new DATA_TYPE[m_rows*m_cols];
	}
	else{//mp_data!=NULL
		if (m_rows*m_cols != A.m_rows*A.m_cols){
			delete[] mp_data;
			mp_data = NULL;
			m_rows = A.m_rows;
			m_cols = A.m_cols;
			mp_data = new DATA_TYPE[m_rows*m_cols];
		}
		else{
			m_rows = A.m_rows;
			m_cols = A.m_cols;
			/* mp_data不需要重新申请空间，减少计算量 */
		}
	}

    int n = m_rows*m_cols;
	DATA_TYPE *pdata = A.mp_data;
    for (int i = 0; i < n; ++i){
		mp_data[i] = pdata[i];
    }

    return *this;
}
matrix::matrix(const matrix &A)
{
	static int i = 0;
	i++;
	if (NULL != mp_data){
		std::cout << i << "  ";
		std::cout << mp_data << std::endl;
	}
	if (this == &A){
		return;
	}
	//DEBUG_PRINT("matrix::matrix(const matrix &A) called\n");
	if (A.m_rows <= 0 || A.m_cols <= 0){
		mp_data = NULL;
		m_rows = m_cols = 0;
		DEBUG_PRINT("matrix::matrix(const matrix &A)\n \
					A.m_rows <= 0 || A.m_cols <= 0\n");
		return;
	}
	if (NULL == A.mp_data){
		//DEBUG_PRINT("matrix::matrix(const matrix &A)\n NULL == mp_data\n");
		mp_data =NULL;
		m_rows = m_cols = 0;
		return;
	}

	if (true||NULL != mp_data){
		/* 不是所有的非空指针都能释放的,野指针指向的是未知内存 */
		/* 在这里因为是复制构造函数，所以初始值不需要释放 */
		/* todo to understand 以上的说法是对的吗 2*A 报错为什么 */
		//DEBUG_PRINT("mp_data=%x\n", mp_data);
		//DEBUG_PRINT("mp_data=%x", *mp_data);
		int x = 0;
		//delete[] mp_data;//todo to understand
		//mp_data = NULL;
	}
	m_rows = A.m_rows;
	m_cols = A.m_cols;
	mp_data = new DATA_TYPE[m_rows*m_cols];
	if (NULL == mp_data){
		//DEBUG_PRINT("matrix::matrix(const matrix &A)\n NULL == mp_data\n");
		m_rows = m_cols = 0;
		return;
	}

	int element_counts = m_rows*m_cols;
	DATA_TYPE* pdata = A.mp_data;
	for (int i = 0; i < element_counts; ++i){
		mp_data[i] = pdata[i];
	}
}

bool matrix::show(int show_image_mode){
	if (m_rows <= 0 || m_cols <= 0 || NULL == mp_data){
		DEBUG_PRINT("(m_rows <= 0 || m_cols <= 0 || NULL == mp_data)    \
					matrix::show()\n");
		return false;
	}

	int num = 0;
	int k = -1;
	//std::string  zero_str = "  ", nonzero_str = "**";
	std::string str;
	switch (show_image_mode)
	{
	case SHOW_IMAGE_SHAPE:
		for (int i = SHOW_IMAGE_CROP_LENGTH; i < m_rows - SHOW_IMAGE_CROP_LENGTH; ++i){
			for (int j = SHOW_IMAGE_CROP_LENGTH; j < m_cols - SHOW_IMAGE_CROP_LENGTH; ++j){
				if (ABS(AVE_VALUE*(mp_data[i*m_cols + j] + 1.0)) < DELTA)
					std::cout << "  ";
				else
					std::cout << "**";
			}
			std::cout << std::endl;
		}
		break;

	case SHOW_IMAGE_SCALE_VALUE:
		for (int i = SHOW_IMAGE_CROP_LENGTH; i < m_rows - SHOW_IMAGE_CROP_LENGTH; ++i){
			for (int j = SHOW_IMAGE_CROP_LENGTH; j < m_cols - SHOW_IMAGE_CROP_LENGTH; ++j){
				if (ABS(AVE_VALUE*(mp_data[i*m_cols + j] + 1.0)) < DELTA){
					for (int k = 0; k < SHOW_WIDTH; ++k){
						std::cout << " ";
					}
				}
				else{
					std::cout << std::setw(SHOW_WIDTH) << std::setprecision(SHOW_WIDTH - 3) << mp_data[i*m_cols + j];
				}
			}
			std::cout << std::endl;
		}
		break;

	case SHOW_IMAGE_INITAIL_VALUE:
		for (int i = SHOW_IMAGE_CROP_LENGTH; i < m_rows - SHOW_IMAGE_CROP_LENGTH; ++i){
			for (int j = SHOW_IMAGE_CROP_LENGTH; j < m_cols - SHOW_IMAGE_CROP_LENGTH; ++j){
				//	if ( ABS(mp_data[i*m_cols + j]) < DELTA){
				//		for (int k = 0; k < SHOW_WIDTH; ++k){
				//			std::cout << " ";
				//		}
				//	}
				//	else{
				//		std::cout << std::setw(SHOW_WIDTH) << std::setprecision(SHOW_WIDTH / 2 - 1) << mp_data[i*m_cols + j];
				//	}
				//}
 
				std::cout << std::setw(SHOW_WIDTH) << std::setprecision(SHOW_WIDTH / 2 - 1) << mp_data[i*m_cols + j];
				//std::cout << mp_data[i*m_cols + j];
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
    DATA_TYPE *p_reduction_data = reduction_matrix.mp_data;
	for (int i = 0; i < elements_count; ++i){
        p_result_data[i] -= p_reduction_data[i];
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
	/* check -> matrix(const& mat)*/
	matrix result_matrix(multiplier_matrix);
	int elements_count = result_matrix.m_rows*result_matrix.m_cols;
	DATA_TYPE *p_result_data = result_matrix.mp_data;
	for (int i = 0; i < elements_count; ++i){
		p_result_data[i] *= val;
	}

	return result_matrix;
}

matrix matrix::hadamard_product(const matrix& matrix_){
	matrix hada_product = matrix_;
	/* todo check 行列 */
	for (int i = 0; i < m_rows; ++i){
		for (int j = 0; j < m_cols; ++j){
			hada_product.mp_data[i*m_rows + j] = \
				mp_data[i*m_cols + j];
		}
	}
	return hada_product;
}