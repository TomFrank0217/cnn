#include "feature.h"

feature::feature(){
	;
}

feature::feature(int channels, int rows, int cols, int val):\
tensor(channels, rows, cols, val){
	;
}

feature::feature(const cv::Mat &image, DATA_TYPE translation, DATA_TYPE scale)
	     :tensor(image, translation, scale){
	;
}

feature::~feature(){
	;
}

bool feature::reshape(int kernels_width = KERNEL_ROW, int kernels_height = KERNEL_COL, \
	int stride = 1, int padding_mode = VALID_PADDING){
	;
}