#ifndef _MATRIX_H_
#define _MATRIX_H_
#include "const_values.h"
#include "debug_print.h"
#include <memory.h>      /*  for memset  */
#include <time.h>        /*  for time(0) */
#include <stdlib.h>      /*  for RAND_MAX rand() */

class matrix{
public:
    matrix(int rows = 0, int cols = 0, int val = 0);
    matrix(int rows, int cols, int low, int high);
    matrix(int rows, int cols, DATA_TYPE val);
    matrix(int rows, int cols, DATA_TYPE low, DATA_TYPE high);
    matrix(const matrix &A);
    ~matrix();
    bool show(int show_image_mode = SHOW_IMAGE_VALUE);
    matrix operator+(const matrix &addition_matrix);
    matrix operator-(const matrix &reduction_matrix);
    matrix operator*(const matrix &multiplier_matrix);
    matrix& operator=(const matrix &A); /* to understand & */
    // matrix operator=(const matrix &A); /* to understand & */
public:
    int m_rows;
    int m_cols;
    DATA_TYPE *m_p_data;
};
#endif