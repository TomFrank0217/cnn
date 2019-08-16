#ifndef  _FEATURE_H_
#define _FEATURE_H_

#include "tensor.h"

class featuresssss :public kernels{
public:
	featuresssss();
	/* to understand Ϊʲô��������Ҫ���ƹ��캯������Ϊû��ָ������� */
	featuresssss(featuresssss &fs_);
    featuresssss(int feature_channels, int features_rows, int features_cols, int val);
	featuresssss(int feature_channels, int features_rows, int features_cols, DATA_TYPE val);
	featuresssss(const cv::Mat &image, DATA_TYPE translation = AVE_VALUE, DATA_TYPE scale = 1.0 / AVE_VALUE);
	~featuresssss();
	featuresssss(int channels, int rows, int cols, DATA_TYPE min, DATA_TYPE max);
	featuresssss(int channels, int rows, int cols, int min, int max);
	/* to understand Ϊʲô��������Ҫ��ֵ��������Ϊû��ָ������� */
	featuresssss& operator=(const featuresssss& fs_);
	//bool reshape(int reshape_mode = FEATURES2MATRIX, int kernels_rows = KERNEL_ROWS, \
		int kernels_cols = KERNEL_COLS, int stride = 1, int padding_mode = VALID_PADDING);
	bool reshape(kernels& tsr, matrix& fts_matrix, int reshape_mode = FEATURES2MATRIX, int kernels_rows = KERNEL_ROWS, \
		int kernels_cols = KERNEL_COLS, int stride = 1, int padding_mode = VALID_PADDING);
public:
	matrix m_features_matrix;
	int m_kernel_rows;/* ����paddingʱ�����features�Ĵ�С todo */
	int m_kernel_cols;/* ����paddingʱ�����features�Ĵ�С todo */
	int m_stride;
	int m_padding_mode;
	kernels m_tensor; /* ��ʱ����ȥ m_tensor��û���õ� */
};

#endif
