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
    matrix(int rows, int cols, int min, int max);
	matrix(int rows, int cols, DATA_TYPE val);
    matrix(int rows, int cols, DATA_TYPE min, DATA_TYPE max);
	matrix(const matrix &A);/* todo */
	matrix& operator=(const matrix &A); /* to understand & */
	// matrix operator=(const matrix &A); /* to understand & */
    ~matrix();
	bool show(int show_image_mode = SHOW_IMAGE_INITAIL_VALUE);

	friend matrix operator+(const DATA_TYPE val, const matrix &add_matrix);
	matrix operator+(DATA_TYPE addition_num);
	bool operator+=(DATA_TYPE addition_num);
    matrix operator+(const matrix &add_matrix);
	bool operator+=(const matrix&add_matrix);

	friend matrix operator-(const DATA_TYPE val, const matrix &reduction_matrix);
	matrix operator-(DATA_TYPE reduction_num);
	bool operator-=(DATA_TYPE reduction_num);
    matrix operator-(const matrix &reduction_matrix);
	bool operator-=(const matrix&add_matrix);

	friend matrix operator*(const DATA_TYPE val, const matrix &multiplier_matrix);
	matrix operator*(const matrix &multiplier_matrix);
	//matrix operator*(const matrix &multiplier_matrix);/* 这个函数最好不要定义，因为改变了原始矩阵的大小 */
	matrix operator*(const DATA_TYPE val);
	bool operator*=(const DATA_TYPE val);
	matrix hadamard_product(const matrix& matrix_);

public:
    int m_rows;
    int m_cols;
    DATA_TYPE *mp_data;
	static int rand_num;
};

#endif