#ifndef _FEATURES_H_
#define _FEATURES_H_

#include "matrix.h"
#include "const_values.h"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class features{
public:
	features();
	features(int channels, int rows, int cols, int val = 0);
	features(int channels, int rows, int cols, DATA_TYPE val);
	features(int channels, int rows, int cols, int min, int max);
	features(int channels, int rows, int cols, DATA_TYPE min, DATA_TYPE max);
	/*  图像features的数值必须归一化到 (-1.0, 1.0) 之间  */
	features(const cv::Mat &image, DATA_TYPE translation = AVE_VALUE, DATA_TYPE scale = 1.0 / AVE_VALUE);

	features(const features& fs_);
	features& operator=(const features &fs_);
	 ~features();
	 //bool reshape(features& tsr, matrix& fts_matrix, int reshape_mode = FEATURES2MATRIX, int kernels_rows = KERNEL_ROWS, \
	 //	 		int kernels_cols = KERNEL_COLS, int stride = 1, int padding_mode = VALID_PADDING);
	 bool show(int image_show_mode = SHOW_IMAGE_INITAIL_VALUE);

public:
	matrix *mp_matrixes;
	int m_channels;
	int m_rows;
	int m_cols;
};
/* 虽然kernel和features相同 但是kernel不能使用features中的一些方法 */
/* 1. features(const cv::Mat &image, DATA_TYPE translation, DATA_TYPE scale);*/
/* 2. bool reshape(features&,matrix&,int,int,int,int,int);*/
typedef features kernel;

#endif
