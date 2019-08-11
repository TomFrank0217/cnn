#include "kernels.h"

kernels::kernels(){
	;
}

kernels::kernels(int channels, int rows, int cols, int val):\
        tensor(channels, rows, cols, val){
	
}

kernels::~kernels(){
	;
}

kernels::kernels(const cv::Mat &image, DATA_TYPE translation, DATA_TYPE scale)
:tensor(image,translation,scale){
	;
}

bool kernels::reshape(int kernels_width, int kernels_height, int stride, int padding_mode){
	return true;
}