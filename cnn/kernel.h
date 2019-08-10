#ifndef  _KERNEL_H_
#define _KERNEL_H_

#include "tensor.h"


class kernel :public tensor{
public:
	kernel();
	kernel(int tensors_count, int tensors_row, int tensors_col, int val);
	kernel(const cv::Mat &image, DATA_TYPE translation = AVE_VALUE, DATA_TYPE scale = 1.0 / AVE_VALUE);
	~kernel();
};

#endif
