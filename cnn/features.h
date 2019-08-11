#ifndef  _FEATURE_H_
#define _FEATURE_H_

#include "tensor.h"

class features :public tensor{
public:
	features();
	features(int channels, int rows, int cols, int val);
	features(const cv::Mat &image, DATA_TYPE translation = AVE_VALUE, DATA_TYPE scale = 1.0 / AVE_VALUE);
	~features();

	virtual bool reshape(int kernels_width = KERNEL_ROW, int kernels_height = KERNEL_COL, \
		int stride = 1, int padding_mode = VALID_PADDING);
};

#endif
