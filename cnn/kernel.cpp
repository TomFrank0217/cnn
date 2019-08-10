#include "kernel.h"

kernel::kernel(int tensors_count, int tensors_row, int tensors_col, int val):\
        tensor(tensors_count, tensors_row, tensors_col, val){
	
}

kernel::~kernel(){
	;
}