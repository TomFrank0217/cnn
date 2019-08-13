#ifndef  _KERNELS_H_
#define _KERNELS_H_

#include "features.h"

class kernels{
public:
	kernels();
	kernels(const kernels &ker_);
	kernels(int channels, int rows, int cols, int kernels_count, int val);
	kernels(int channels, int rows, int cols, int kernels_count, DATA_TYPE val);
	kernels(int channels, int rows, int cols, int kernels_count, int min, int max);
	kernels(int channels, int rows, int cols, int kernels_count, DATA_TYPE 
		    min = -RANDOM_INITIAL_VAL, DATA_TYPE max = RANDOM_INITIAL_VAL); 
	~kernels();
	kernels& operator=(const kernels& ker_);
	//bool reshape(int kernel_rows = KERNEL_ROWS, int kernel_cols = KERNEL_COLS, \
		int stride = 1, int padding_mode = VALID_PADDING);
	bool show(int image_show_mode = SHOW_IMAGE_INITAIL_VALUE,int mode=MATRIEX2KERNELS);
	bool reshape(int mode = KERNELS2MATRIEX);
public:
	kernel* mp_kers;
	kernel* mp_tensors1;
	int m_channels;
	int m_rows;
	int m_cols;
	int m_kers_counts;
    matrix m_kers_mat;
};

#endif
