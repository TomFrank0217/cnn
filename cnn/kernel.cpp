#include "kernel.h"

kernel::kernel(){
	;
}

kernel::kernel(int channels, int rows, int cols, int val):\
        tensor(channels, rows, cols, val){
	
}

kernel::~kernel(){
	;
}

kernel::kernel(const cv::Mat &image, DATA_TYPE translation, DATA_TYPE scale)
:tensor(image,translation,scale){
	;
}