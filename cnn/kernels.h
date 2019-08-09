#ifndef _KERNELS_H_
#define _KERNELS_H_

#include "matrix.h"
#include "const_values.h"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class kernels{
public:
	kernels(int kernels_count, int kernels_row, int kernels_col, int val);
	kernels(int kernels_count, int kernels_row, int kernels_col, DATA_TYPE val);
	kernels(int kernels_count, int kernels_row, int kernels_col, int min, int max);
	kernels(int kernels_count, int kernels_row, int kernels_col, DATA_TYPE min, DATA_TYPE max);
	kernels::kernels(const cv::Mat &image, DATA_TYPE translation = AVE_VALUE, DATA_TYPE scale = 1.0 / AVE_VALUE);
	~kernels();
	bool kernels::features_2_matrix(int kernels_width = KERNEL_ROW, int kernels_height = KERNEL_COL, \
		int stride = 1, int padding_mode = VALID_PADDING);
	bool show(int image_show_mode = SHOW_IMAGE_VALUE);
	bool features_2_matrix();
private:
	matrix *m_p_kernels_features;
	matrix *features_matrix;

	int m_kernels_features_count;
	int m_kernels_features_row;
	int m_kernels_features_col;

	int m_feature_matrix_row;
	int m_feature_matrix_col;

	int m_padding;
};

typedef kernels features;

#endif
