#ifndef  _KERNEL_H_
#define _KERNEL_H_

#include "tensor.h"

class kernel :public tensor{
	kernel(int tensors_count, int tensors_row, int tensors_col, int val);
	~kernel();
};

#endif
class tensor{
public:
	tensor(int tensors_count, int tensors_row, int tensors_col, int val);
	tensor(int tensors_count, int tensors_row, int tensors_col, DATA_TYPE val);
	tensor(int tensors_count, int tensors_row, int tensors_col, int min, int max);
	tensor(int tensors_count, int tensors_row, int tensors_col, DATA_TYPE min, DATA_TYPE max);
	tensor::tensor(const cv::Mat &image, DATA_TYPE translation = AVE_VALUE, DATA_TYPE scale = 1.0 / AVE_VALUE);
	~tensor();
	virtual bool reshape(int kernels_width = KERNEL_ROW, int kernels_height = KERNEL_COL, \
		int stride = 1, int padding_mode = VALID_PADDING);
	bool show(int image_show_mode = SHOW_IMAGE_VALUE);
	bool reshape();
public:
	matrix *mp_tensors;
	int m_tensors_count;
	int m_tensors_row;
	int m_tensors_col;
};

#endif
