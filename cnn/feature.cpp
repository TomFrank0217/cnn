#include "feature.h"

feature::feature(){
	;
}

feature::feature(int features_count, int features_row, int features_col, int val):\
tensor(features_count, features_row, features_col, val){
	;
}


feature::~feature(){
	;
}

feature::feature(const cv::Mat &image, DATA_TYPE translation, DATA_TYPE scale)
	:tensor(image, translation, scale){
	;
}