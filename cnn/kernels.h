#ifndef  _KERNEL_H_
#define _KERNEL_H_

#include "tensor.h"

class kernels{
public:
	kernels();
	kernels(const kernels &ker_);
	kernels(int channels, int rows, int cols, int kernels_count, int val);
	kernels(int channels, int rows, int cols, int kernels_count, DATA_TYPE val);
	kernels(int channels, int rows, int cols, int kernels_count, int min, int max);
	kernels(int channels, int rows, int cols, int kernels_count, DATA_TYPE min, DATA_TYPE max);
	~kernels();
	kernels& operator=(const kernels& ker_);
	//bool reshape(int kernel_rows = KERNEL_ROWS, int kernel_cols = KERNEL_COLS, \
		int stride = 1, int padding_mode = VALID_PADDING);
	bool show(int image_show_mode = SHOW_IMAGE_INITAIL_VALUE,int mode=MATRIEX2KERNELS);
	bool reshape(int mode = KERNELS2MATRIEX);
public:
	tensor* mp_tensors0;
	tensor* mp_tensors1;
	int m_channels;
	int m_rows;
	int m_cols;
	int m_kernels_count;
    matrix m_kernels_matrix;
};

#endif
