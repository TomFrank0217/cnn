#ifndef  _KERNELS_H_
#define _KERNELS_H_

#include "features.h"

class kernels{
public:
	kernels();
	kernels(const kernels &ker_);
	/* todo 似乎把下面两个函数封装成模板类比较合适 */
	kernels(int channels, int rows, int cols, int kernels_count, int val);
	kernels(int channels, int rows, int cols, int kernels_count, DATA_TYPE val);

	/* todo 似乎把下面两个函数封装成模板类比较合适 */
	kernels(int channels, int rows, int cols, int kernels_count, int min, int max);
	kernels(int channels, int rows, int cols, int kernels_count, DATA_TYPE 
		    min, DATA_TYPE max); 

	kernels operator+(DATA_TYPE add_num);//matrix operator+(DATA_TYPE addition_num);
	bool operator+=(DATA_TYPE add_num);//bool operator+=(DATA_TYPE addition_num);
	friend kernels operator+(const DATA_TYPE add_num, const kernels &add_kernels);//friend matrix operator+(const DATA_TYPE val, const matrix &add_matrix);
	kernels operator+(const kernels &add_features);//matrix operator+(const matrix &add_matrix);
	bool operator+=(const kernels& add_features);//bool operator+=(const matrix&add_matrix);

	kernels operator-(DATA_TYPE minus_num);
	bool operator-=(DATA_TYPE minus_num);
	friend kernels operator-(const DATA_TYPE minus, const kernels &minus_kernels);
	kernels operator-(const kernels &minus_kernels);
	bool operator-=(const kernels& minus_kernels);

	friend kernels operator*(const DATA_TYPE scale, const kernels &mutiplier_kernels);
	kernels operator*(const DATA_TYPE scale);
	bool operator*=(const DATA_TYPE scale);
	//matrix hadamard_product(const matrix& matrix_);/* 暂时不需要这个功能 */

	~kernels();
	kernels& operator=(const kernels& ker_);
	bool show(int image_show_mode = SHOW_IMAGE_INITAIL_VALUE);
    bool show_shape();
	bool reset(DATA_TYPE val);
public:
	kernel* mp_kers;
	int m_channels;
	int m_rows;
	int m_cols;
	int m_kers_counts;
    //matrix m_kers_mat;
};

#endif
