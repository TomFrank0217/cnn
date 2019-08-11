#ifndef  _KERNEL_H_
#define _KERNEL_H_

#include "tensor.h"


class kernels :public tensor{
public:
	kernels();
	kernels(int channels, int rows, int cols, int val);
	kernels(const cv::Mat &image, DATA_TYPE translation = AVE_VALUE, DATA_TYPE scale = 1.0 / AVE_VALUE);
	~kernels();

	virtual bool reshape(int kernel_rows = KERNEL_ROWS, int kernel_cols = KERNEL_COLS, \
		int stride = 1, int padding_mode = VALID_PADDING);
};

#endif
