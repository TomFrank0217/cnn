#include "kernel.h"

kernel::kernel(){
	;
}

kernel::kernel(int tensors_count, int tensors_row, int tensors_col, int val):\
        tensor(tensors_count, tensors_row, tensors_col, val){
	
}


kernel::~kernel(){
	;
}

kernel::kernel(const cv::Mat &image, DATA_TYPE translation, DATA_TYPE scale)
:tensor(image,translation,scale){
	;
}