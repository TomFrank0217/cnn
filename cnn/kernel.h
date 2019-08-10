#ifndef  _KERNEL_H_
#define _KERNEL_H_

#include "tensor.h"

class kernel :public tensor{
	kernel(int tensors_count, int tensors_row, int tensors_col, int val);
	~kernel();
};

#endif
