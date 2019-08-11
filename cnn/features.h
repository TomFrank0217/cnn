#ifndef  _FEATURE_H_
#define _FEATURE_H_

#include "tensor.h"

class features :public tensor{
public:
	features();
	features(int feature_channels, int features_rows, int features_cols, int val);
	features(const cv::Mat &image, DATA_TYPE translation = AVE_VALUE, DATA_TYPE scale = 1.0 / AVE_VALUE);
	~features();
	features(int channels, int rows, int cols, DATA_TYPE min, DATA_TYPE max);
	features(int channels, int rows, int cols, int min, int max);
	virtual bool reshape(int kernels_rows = KERNEL_ROWS, int kernels_cols = KERNEL_COLS, \
		int stride = 1, int padding_mode = VALID_PADDING);
public:
	matrix m_features_matrix;
	int m_kernel_rows;
	int m_kernel_cols;
	int m_stride;
	int m_padding_mode;
};

#endif
