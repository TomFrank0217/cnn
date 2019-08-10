#ifndef  _FEATURE_H_
#define _FEATURE_H_

#include "tensor.h"

class feature :public tensor{
public:
	feature();
	feature(int features_count, int features_row, int features_col, int val);
	feature(const cv::Mat &image, DATA_TYPE translation = AVE_VALUE, DATA_TYPE scale = 1.0 / AVE_VALUE);
	~feature();
};

#endif
