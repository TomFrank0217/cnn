#include "features.h"

features::features(){
	;
}

features::features(int channels, int rows, int cols, int val):\
tensor(channels, rows, cols, val){
	;
}

features::features(const cv::Mat &image, DATA_TYPE translation, DATA_TYPE scale)
	     :tensor(image, translation, scale){
	;
}

features::~features(){
	;
}

bool features::reshape(int kernels_width, int kernels_height, \
	int stride, int padding_mode){
	return true;
}