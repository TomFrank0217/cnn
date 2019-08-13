#ifndef  _FEATURE_H_
#define _FEATURE_H_

#include "tensor.h"

class features :public tensor{
public:
	features();
	/* to understand 为什么特征不需要复制构造函数，因为没有指针变量吗？ */
	features(features &fs_);
    features(int feature_channels, int features_rows, int features_cols, int val);
	features(int feature_channels, int features_rows, int features_cols, DATA_TYPE val);
	features(const cv::Mat &image, DATA_TYPE translation = AVE_VALUE, DATA_TYPE scale = 1.0 / AVE_VALUE);
	~features();
	features(int channels, int rows, int cols, DATA_TYPE min, DATA_TYPE max);
	features(int channels, int rows, int cols, int min, int max);
	/* to understand 为什么特征不需要赋值函数，因为没有指针变量吗？ */
	features& operator=(const features& fs_);
	bool reshape(int mode = FEATURES2MATRIX, int kernels_rows = KERNEL_ROWS, \
		int kernels_cols = KERNEL_COLS, int stride = 1, int padding_mode = VALID_PADDING);
public:
	matrix m_features_matrix;
	int m_kernel_rows;/* 用于padding时候控制features的大小 */
	int m_kernel_cols;/* 用于padding时候控制features的大小 */
	int m_stride;
	int m_padding_mode;
	tensor m_tensor; 
};

#endif
