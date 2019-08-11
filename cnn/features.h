#ifndef  _FEATURE_H_
#define _FEATURE_H_

#include "tensor.h"

class features :public tensor{
public:
	features();
	features(int feature_channels, int features_rows, int features_cols, int val);
	features(const cv::Mat &image, DATA_TYPE translation = AVE_VALUE, DATA_TYPE scale = 1.0 / AVE_VALUE);
	~features();

	virtual bool reshape(int kernels_rows = KERNEL_ROWS, int kernels_cols = KERNEL_COLS, \
		int stride = 1, int padding_mode = VALID_PADDING);
public:
	matrix m_features_matrix;
	int m_kernels_rows;
	int m_kernels_cols;
	int m_stride;
	int m_padding_mode;
};

#endif
