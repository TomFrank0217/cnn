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