#ifndef  _KERNEL_H_
#define _KERNEL_H_

#include "tensor.h"

class kernels{
public:
	kernels();
	kernels(int channels, int rows, int cols, int kernels_count, int val);
	kernels(int channels, int rows, int cols, int kernels_count, DATA_TYPE val);
	kernels(int channels, int rows, int cols, int kernels_count, int min, int max);
	
	~kernels();
	
	virtual bool reshape(int kernel_rows = KERNEL_ROWS, int kernel_cols = KERNEL_COLS, \
		int stride = 1, int padding_mode = VALID_PADDING);
public:
	tensor* mp_tensors;
	int m_channels;
	int m_rows;
	int m_cols;
	int m_kernels_count;
};

#endif
