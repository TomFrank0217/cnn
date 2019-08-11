#ifndef _KERNELS_H_
#define _KERNELS_H_

#include "matrix.h"
#include "const_values.h"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class tensor{
public:
	tensor();
	tensor(int channels, int rows, int cols, int val);
	tensor(int channels, int rows, int cols, DATA_TYPE val);
	tensor(int channels, int rows, int cols, int min, int max);
	tensor(int channels, int rows, int cols, DATA_TYPE min, DATA_TYPE max);
	/*  tensor的数值必须归一化到(-1,1)之间  */
	tensor::tensor(const cv::Mat &image, DATA_TYPE translation = AVE_VALUE, DATA_TYPE scale = 1.0 / AVE_VALUE);

	virtual ~tensor();
	virtual bool reshape(int kernels_width = KERNEL_ROW, int kernels_height = KERNEL_COL, \
		int stride = 1, int padding_mode = VALID_PADDING);
	/*  tensor的数值必须归一化到(-1,1)之间，才能正确显示 其余的数值todo  */
	bool show(int image_show_mode = SHOW_IMAGE_SCALE_VALUE);
public:
	matrix *mp_matrixes;
	int m_channels;
	int m_rows;
	int m_cols;
};

#endif
