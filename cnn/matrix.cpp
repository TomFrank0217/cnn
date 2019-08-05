#include "matrix.h"
#include <iostream>
#include <iomanip>
#include "const_values.h"

matrix::matrix(int rows, int cols, int val):\
m_rows(rows),m_cols(cols)
{
    if (0 == rows && 0 == cols){
        m_p_data = NULL;
        return;
    }
    if (rows <= 0 || cols <= 0){
        DEBUG_PRINT("matrix::matrix(int rows, int cols)\nrows <= 0 || cols <= 0\n");
    }

    m_p_data = new DATA_TYPE[m_rows * m_cols];
    //DEBUG_PRINT("m_p_matrix = new DATA_TYPE[rows * cols];\n");/* to delete */
    if (NULL == m_p_data){
        DEBUG_PRINT("matrix::matrix(int rows, int cols)\nNULL == m_p_data\n");
    }
    //memset(m_p_matrix, val, m_rows*m_cols*sizeof(DATA_TYPE));
    int n = m_rows*m_cols;
    for (int i = 0; i < n; ++i){
        m_p_data[i] = val;
    }
}

matrix::matrix(int rows, int cols, int low, int high){
    if (rows <= 0 || cols <= 0){
        DEBUG_PRINT("matrix::matrix(int rows, int cols)\nrows <= 0 || cols <= 0\n");
    }
    m_rows = rows;
    m_cols = cols;
    m_p_data = new DATA_TYPE[rows * cols];
    if (NULL == m_p_data){
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
            m_p_data[k++] = rand() % mod_num + low;
        }
    }
}

matrix::matrix(int rows, int cols, DATA_TYPE val):
m_rows(rows),m_cols(cols)
{
    if (rows <= 0 || cols <= 0){
        DEBUG_PRINT("matrix::matrix(int rows, int cols)\nrows <= 0 || cols <= 0\n");
    }

    m_p_data = new DATA_TYPE[rows * cols];

    if (NULL == m_p_data){
        DEBUG_PRINT("matrix::matrix(int rows, int cols)\nNULL == m_p_data\n");
    }

    int n = m_rows*m_cols;
    for (int i = 0; i < n; ++i){
        m_p_data[i] = val;
    }
}

matrix::matrix(int rows, int cols, DATA_TYPE low, DATA_TYPE high):\
m_rows(rows),m_cols(cols)
{

    if (rows <= 0 || cols <= 0){
        DEBUG_PRINT("matrix::matrix(int rows, int cols)\nrows <= 0 || cols <= 0\n");
    }

    m_p_data = new DATA_TYPE[rows * cols];
    if (NULL == m_p_data){
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
        m_p_data[i] = slope*rand_num + low;
    }
}

matrix::matrix(const matrix &A):\
m_rows(A.m_rows),m_cols(A.m_cols)
{
    DEBUG_PRINT("matrix::matrix(const matrix &A) called\n");
    if (A.m_rows <= 0 || A.m_cols <= 0){
        DEBUG_PRINT("matrix::matrix(const matrix &A)\n A.m_rows <= 0 || A.m_cols <= 0\n");
    }

    if (NULL == A.m_p_data){
        DEBUG_PRINT("matrix::matrix(const matrix &A)\n NULL == m_p_data\n");
    }
    
    m_p_data = new DATA_TYPE[m_rows*m_cols];
    if (NULL == m_p_data){
        DEBUG_PRINT("matrix::matrix(const matrix &A)\n NULL == m_p_data\n");
    }

    int element_counts = m_rows*m_cols;
    for (int i = 0; i < element_counts; ++i){
        m_p_data[i] = A.m_p_data[i];
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

    if (NULL == m_p_data){
        DEBUG_PRINT("NULL == m_p_data  matrix::operator+\n");
    }

    if (NULL == addition_matrix.m_p_data){
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
            sum_matrix.m_p_data[k] += addition_matrix.m_p_data[k];
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

    if (NULL == m_p_data){
        DEBUG_PRINT("NULL == m_p_data  matrix::operator+\n");
    }

    if (NULL == reduction_matrix.m_p_data){
        DEBUG_PRINT("NULL == reduction_matrix.m_p_data  matrix::operator+\n");
    }

    if (m_rows != reduction_matrix.m_rows || m_cols != reduction_matrix.m_cols){
        DEBUG_PRINT("m_rows != reduction_matrix.m_rows || m_cols != reduction_matrix.m_cols \
                                                            matrix::operator+\n");
    }

    matrix minuend_matrix(*this);

    int k = 0;
    for (int i = 0; i < m_rows; ++i){
        for (int j = 0; j < m_cols; ++j){
            minuend_matrix.m_p_data[k] -= reduction_matrix.m_p_data[k];
            ++k;
        }
    }

    return minuend_matrix;
}

bool matrix::show(int show_image_mode){
    if (m_rows <= 0 || m_cols <= 0 || NULL == m_p_data){
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
                if (ABS(AVE_VALUE*( m_p_data[i*m_cols + j] + 1.0) ) < 0.01)
                    std::cout << "  ";
                else
                    std::cout << "**";
            }
            std::cout << std::endl;
        }
        break;

    case SHOW_IMAGE_VALUE:
        

        for (int i = SHOW_IAMGE_CROP_LENGTH; i < m_rows - SHOW_IAMGE_CROP_LENGTH; ++i){
            for (int j = SHOW_IAMGE_CROP_LENGTH; j < m_cols - SHOW_IAMGE_CROP_LENGTH; ++j){
                if (ABS(AVE_VALUE + m_p_data[i*m_cols+j]) < 0.01){
                    for (int k = 0; k < SHOW_WIDTH; ++k){
                        std::cout << " ";
                    }
                }
                else{
                    std::cout << std::setw(SHOW_WIDTH) << std::setprecision(SHOW_WIDTH / 2 - 1) << m_p_data[i*m_cols + j];
                }
            }
            std::cout << std::endl;
        }
        break;

    default:
        return false;
    }

}

matrix matrix::operator*(const matrix &multiplier_matrix){
    if (m_rows <= 0 || m_cols <= 0){
        DEBUG_PRINT("m_rows <= 0 || m_cols <= 0  matrix::operator+\n");
    }

    if (multiplier_matrix.m_rows <= 0 || multiplier_matrix.m_cols <= 0){
        DEBUG_PRINT("multiplier_matrix.m_rows <= 0 || multiplier_matrix.m_cols <= 0  \
                                         matrix::operator+\n");
    }

    if (NULL == m_p_data){
        DEBUG_PRINT("NULL == m_p_data  matrix::operator+\n");
    }

    if (NULL == multiplier_matrix.m_p_data){
        DEBUG_PRINT("NULL == multiplier_matrix.m_p_data  matrix::operator+\n");
    }

    if (this->m_cols != multiplier_matrix.m_rows){
        DEBUG_PRINT("this->m_cols != multiplier_matrix.m_rows  \
                                        matrix::operator*(const matrix &multiplier_matrix)\n");
    }

    matrix product_matrix(this->m_rows, multiplier_matrix.m_cols, 0.0);

    int s = 0, t = 0, r = 0;
    for (int i = 0; i < product_matrix.m_rows; ++i){
        for (int k = 0; k < product_matrix.m_cols; ++k){
            product_matrix.m_p_data[s] = 0.0;
            int j = 0;
            t = i*this->m_cols;
            for (j = 0; j < this->m_cols; ++j){
                r = j*multiplier_matrix.m_cols;
                product_matrix.m_p_data[s] += \
                    this->m_p_data[t++] * multiplier_matrix.m_p_data[r + k];
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

    if (NULL == m_p_data){
        DEBUG_PRINT("NULL == m_p_data  matrix::~matrix()\n");
    }

    DEBUG_PRINT("matrix destrcutor called.\n");
    delete[] m_p_data;
}

matrix& matrix::operator=(const matrix &A){

    //DEBUG_PRINT("matrix matrix::operator = (const matrix &A)\n");
    if (this == &A){
        return *this;
    }

    delete[] m_p_data;
    m_p_data = NULL;
    this->m_rows = A.m_rows;
    this->m_cols = A.m_cols;

    m_p_data = new DATA_TYPE[m_rows*m_cols];
    int n = m_rows*m_cols;
    for (int i = 0; i < n; ++i){
        m_p_data[i] = A.m_p_data[i];
    }

    return *this;
}