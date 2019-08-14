#include "kernels.h"

kernels::kernels(){
	mp_kers = NULL;
	m_channels = 0;
	m_rows = 0;
	m_cols = 0;
	m_kers_counts = 0;
	//m_kers_mat = matrix();
}

kernels::kernels(int channels, int rows, int cols, int kernels_counts, int val):\
m_channels(channels),m_rows(rows),m_cols(cols),m_kers_counts(kernels_counts){
	if (0 >= channels || 0 >= rows || 0 >= cols || 0 >= kernels_counts){
		DEBUG_PRINT("(0 >= channels || 0 >= rows || 0 >= cols || 0 >= kernels_count) \n \
					kernels(int channels, int rows, int cols, int kernels_count, int val)");
	}

	int kers_mat_rows = m_rows*m_cols*m_channels;
	int kers_mat_cols = m_kers_counts;
	//m_kers_mat = matrix(kers_mat_rows, kers_mat_cols);

	mp_kers = NULL;
	mp_kers = new kernel[kernels_counts];
	if (NULL == mp_kers){
		DEBUG_PRINT("(NULL == mp_kers \
		      kernels(int channels, int rows, int cols, int kernels_count, int val)");
	}

	for (int i = 0; i < m_kers_counts; ++i){
		mp_kers[i] = kernel(channels, rows, cols, val);
	}
}

kernels::kernels(int channels, int rows, int cols, int kernels_counts, DATA_TYPE val):\
m_channels(channels), m_rows(rows), m_cols(cols), m_kers_counts(kernels_counts){
	if (0 >= channels || 0 >= rows || 0 >= cols || 0 >= kernels_counts){
		DEBUG_PRINT("(0 >= channels || 0 >= rows || 0 >= cols || 0 >= kernels_count) \n \
					 kernels(int channels, int rows, int cols, int kernels_count, DATA_TYPE val)");
	}

	int kernels_matrix_rows = m_rows*m_cols*m_channels;
	int kernels_matrix_cols = m_kers_counts;
	//m_kers_mat = matrix(kernels_matrix_rows, kernels_matrix_cols);

	mp_kers = new kernel[kernels_counts];
	if (NULL == mp_kers){
		DEBUG_PRINT("(NULL == mp_kers \n \
					 kernels(int channels, int rows, int cols, int kernels_count, DATA_TYPE val)");
	}

	for (int i = 0; i < kernels_counts; ++i){
		mp_kers[i] = kernel(channels, rows, cols, val);
	}
}

kernels::kernels(int channels, int rows, int cols, int kernels_counts, int min, int max):\
m_channels(channels), m_rows(rows), m_cols(cols), m_kers_counts(kernels_counts){
	if (0 >= channels || 0 >= rows || 0 >= cols || 0 >= kernels_counts){
		DEBUG_PRINT("(0 >= channels || 0 >= rows || 0 >= cols || 0 >= kernels_count) \n \
					kernels(int channels, int rows, int cols, int kernels_count, int min, int max)");
	}

	int kernels_matrix_rows = m_rows*m_cols*m_channels;
	int kernels_matrix_cols = m_kers_counts;
	//m_kers_mat = matrix(kernels_matrix_rows, kernels_matrix_cols);

	mp_kers = new kernel[kernels_counts];
	if (NULL == mp_kers){
		DEBUG_PRINT("(NULL == mp_kers \n \
					  kernels(int channels, int rows, int cols, int kernels_count, int min, int max)");
	}

	for (int i = 0; i < kernels_counts; ++i){
		mp_kers[i] = kernel(channels, rows, cols, min, max);
	}
}

kernels::kernels(int channels, int rows, int cols, int kernels_count, DATA_TYPE min, DATA_TYPE max):\
m_channels(channels), m_rows(rows), m_cols(cols), m_kers_counts(kernels_count){
	if (0 >= channels || 0 >= rows || 0 >= cols || 0 >= kernels_count){
		DEBUG_PRINT("(0 >= channels || 0 >= rows || 0 >= cols || 0 >= kernels_count) \n \
					kernels(int channels, int rows, int cols, int kernels_count, DATA_TYPE min, DATA_TYPE max)");
	}

	int kernels_matrix_rows = m_rows*m_cols*m_channels;
	int kernels_matrix_cols = m_kers_counts;
	//m_kers_mat = matrix(kernels_matrix_rows, kernels_matrix_cols);

	mp_kers = NULL;
	mp_kers = new kernel[kernels_count];
	if (NULL == mp_kers){
		DEBUG_PRINT("(NULL == mp_tensors) \n \
					 kernels(int channels, int rows, int cols, int kernels_count, DATA_TYPE min, DATA_TYPE max)");
	}

	for (int i = 0; i < kernels_count; ++i){
		mp_kers[i] = kernel(channels, rows, cols, min, max);
	}
}

kernels::~kernels(){
	if (NULL != mp_kers){
		delete[] mp_kers;
		mp_kers = NULL;
	}
}


//bool kernels::reshape(){
	//todo
	//return true;
//}

/* bool show(int image_show_mode = SHOW_IMAGE_INITAIL_VALUE, int mode = MATRIEX2KERNELS) */
bool kernels::show(int image_show_mode){
	std::cout << "kernels\n" << std::endl;
	for (int i = 0; i < m_kers_counts; ++i){
		std::cout << "kernel " << i << std::endl;
		mp_kers[i].show(image_show_mode);
	}
	std::cout << std::endl;
	return true;
}

kernels::kernels(const kernels &ker_){
	m_channels = ker_.m_channels;
	m_rows = ker_.m_rows;
	m_cols = ker_.m_cols;
	m_kers_counts = ker_.m_kers_counts;
	/* todo 此处是否应该释放指针指向的内存 如果释放会不会出现matrix和features复制构造函数相同的问题 */
	//if (NULL != mp_kers){
	//	delete[] mp_kers;
	//	mp_kers = NULL;
	//}
	//m_kers_mat = ker_.m_kers_mat;
	mp_kers = new kernel[m_kers_counts];
	if (NULL == mp_kers){
		DEBUG_PRINT("(NULL == mp_kers \n");
		return;
	}
	for (int i = 0; i < m_kers_counts; ++i){
		mp_kers[i] = ker_.mp_kers[i];
	}

}
kernels& kernels::operator=(const kernels& ker_){
	if (&ker_ == this){
		return *this;
	}

	m_channels = ker_.m_channels;
	m_rows = ker_.m_rows;
	m_cols = ker_.m_cols;
	m_kers_counts = ker_.m_kers_counts;
	//m_kers_mat = ker_.m_kers_mat;

	if (NULL != mp_kers){
		delete[] mp_kers;
		mp_kers = NULL;
	}

	mp_kers = new kernel[m_kers_counts];
	if (NULL == mp_kers){
		std::cout << "(NULL == mp_kers \n  kernels::operator= \n";
		return *this;
	}

	for (int i = 0; i < m_kers_counts; ++i){
		mp_kers[i] = ker_.mp_kers[i];
	}
}