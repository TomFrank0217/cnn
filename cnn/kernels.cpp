#include "kernels.h"

kernels::kernels(){
	mp_tensors = NULL;
	m_channels = 0;
	m_rows = 0;
	m_cols = 0;
	m_kernels_count = 0;
}

kernels::kernels(int channels, int rows, int cols, int kernels_count, int val):\
m_channels(channels),m_rows(rows),m_cols(cols),m_kernels_count(kernels_count){
	if (0 >= channels || 0 >= rows || 0 >= cols || 0 >= kernels_count){
		DEBUG_PRINT("(0 >= channels || 0 >= rows || 0 >= cols || 0 >= kernels_count) \n \
					kernels(int channels, int rows, int cols, int kernels_count, int val)");
	}
	mp_tensors = new tensor[kernels_count];
	if (NULL == mp_tensors){
		DEBUG_PRINT("(NULL == mp_tensors) \n \
					 kernels(int channels, int rows, int cols, int kernels_count, int val)");
	}

	for (int i = 0; i < kernels_count; ++i){
		mp_tensors[i] = tensor(channels, rows, cols, val);
	}
}

kernels::kernels(int channels, int rows, int cols, int kernels_count, DATA_TYPE val):\
m_channels(channels), m_rows(rows), m_cols(cols), m_kernels_count(kernels_count){
	if (0 >= channels || 0 >= rows || 0 >= cols || 0 >= kernels_count){
		DEBUG_PRINT("(0 >= channels || 0 >= rows || 0 >= cols || 0 >= kernels_count) \n \
					 kernels(int channels, int rows, int cols, int kernels_count, DATA_TYPE val)");
	}
	mp_tensors = new tensor[kernels_count];
	if (NULL == mp_tensors){
		DEBUG_PRINT("(NULL == mp_tensors) \n \
					kernels(int channels, int rows, int cols, int kernels_count, DATA_TYPE val)");
	}

	for (int i = 0; i < kernels_count; ++i){
		mp_tensors[i] = tensor(channels, rows, cols, val);
	}
}

kernels::kernels(int channels, int rows, int cols, int kernels_count, int min, int max):\
m_channels(channels), m_rows(rows), m_cols(cols), m_kernels_count(kernels_count){
	if (0 >= channels || 0 >= rows || 0 >= cols || 0 >= kernels_count){
		DEBUG_PRINT("(0 >= channels || 0 >= rows || 0 >= cols || 0 >= kernels_count) \n \
					kernels(int channels, int rows, int cols, int kernels_count, int min, int max)");
	}
	mp_tensors = new tensor[kernels_count];
	if (NULL == mp_tensors){
		DEBUG_PRINT("(NULL == mp_tensors) \n \
					  kernels(int channels, int rows, int cols, int kernels_count, int min, int max)");
	}

	for (int i = 0; i < kernels_count; ++i){
		mp_tensors[i] = tensor(channels, rows, cols, min, max);
	}
}

kernels::kernels(int channels, int rows, int cols, int kernels_count, DATA_TYPE min, DATA_TYPE max):\
m_channels(channels), m_rows(rows), m_cols(cols), m_kernels_count(kernels_count){
	if (0 >= channels || 0 >= rows || 0 >= cols || 0 >= kernels_count){
		DEBUG_PRINT("(0 >= channels || 0 >= rows || 0 >= cols || 0 >= kernels_count) \n \
					kernels(int channels, int rows, int cols, int kernels_count, DATA_TYPE min, DATA_TYPE max)");
	}
	mp_tensors = new tensor[kernels_count];
	if (NULL == mp_tensors){
		DEBUG_PRINT("(NULL == mp_tensors) \n \
					 kernels(int channels, int rows, int cols, int kernels_count, DATA_TYPE min, DATA_TYPE max)");
	}

	for (int i = 0; i < kernels_count; ++i){
		mp_tensors[i] = tensor(channels, rows, cols, min, max);
	}
}


kernels::~kernels(){
	delete[] mp_tensors;
}


bool kernels::reshape(int kernels_width, int kernels_height, int stride, int padding_mode){
	//todo
	return true;
}

bool kernels::show(int image_show_mode){
	for (int i = 0; i < m_kernels_count; ++i){
		std::cout << "kernels" << i << std::endl;
		mp_tensors[i].show(image_show_mode);
		std::cout << std::endl;
	}
	return true;
}