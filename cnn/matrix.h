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
	/*  matrix目前只支持 (-1,0,1.0)矩阵的显示  */
    bool show(int show_image_mode = SHOW_IMAGE_VALUE);

	friend matrix operator+(const DATA_TYPE val, const matrix &addition_matrix);
	matrix operator+(DATA_TYPE addition_num);
    matrix operator+(const matrix &addition_matrix);

	friend matrix operator-(const DATA_TYPE val, const matrix &reduction_matrix);
	matrix operator-(DATA_TYPE reduction_num);
    matrix operator-(const matrix &reduction_matrix);
	
	friend matrix operator*(const DATA_TYPE val, const matrix &multiplier_matrix);
	matrix operator*(const matrix &multiplier_matrix);
	matrix operator*(const DATA_TYPE val);

    matrix& operator=(const matrix &A); /* to understand & */
    // matrix operator=(const matrix &A); /* to understand & */
public:
    int m_rows;
    int m_cols;
    DATA_TYPE *mp_data;
};

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
#endif