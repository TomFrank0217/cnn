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

kernels kernels::operator+(DATA_TYPE add_num){
	if (0 >= m_rows || 0 >= m_cols || 0 >= m_channels || 0 >= m_kers_counts){
		DEBUG_PRINT("(0 >= m_rows || 0 >= m_cols||0>=m_channels) kernels::operator+ \n");
		m_channels = m_rows = m_cols = m_kers_counts = 0;
		mp_kers = NULL;
		return *this;
	}
	if (NULL == mp_kers){
		DEBUG_PRINT("(NULL == mp_kers) kernels::operator+ \n");
		m_channels = m_rows = m_cols = m_kers_counts = 0;
		return *this;
	}

	kernels kers_(*this);
	for (int i = 0; i < m_kers_counts; ++i){
		kers_.mp_kers[i] += add_num;
	}

	return kers_;
}

bool kernels::operator+=(DATA_TYPE add_num){
	if (0 >= m_rows || 0 >= m_cols || 0 >= m_channels || 0 >= m_kers_counts){
		DEBUG_PRINT("(0 >= m_rows || 0 >= m_cols||0>=m_channels) kernels::operator+ \n");
		m_channels = m_rows = m_cols = m_kers_counts = 0;
		mp_kers = NULL;
		return false;
	}
	if (NULL == mp_kers){
		DEBUG_PRINT("(NULL == mp_kers) kernels::operator+ \n");
		m_channels = m_rows = m_cols = m_kers_counts = 0;
		return false;
	}

	//kernels kers_(*this);
	for (int i = 0; i < m_kers_counts; ++i){
		mp_kers[i] += add_num;
	}

	return true;
}

kernels kernels::operator-(DATA_TYPE minus_num){
	if (0 >= m_rows || 0 >= m_cols || 0 >= m_channels || 0 >= m_kers_counts){
		DEBUG_PRINT("(0 >= m_rows || 0 >= m_cols||0>=m_channels) kernels::operator+ \n");
		m_channels = m_rows = m_cols = m_kers_counts = 0;
		mp_kers = NULL;
		return *this;
	}
	if (NULL == mp_kers){
		DEBUG_PRINT("(NULL == mp_kers) kernels::operator+ \n");
		m_channels = m_rows = m_cols = m_kers_counts = 0;
		return *this;
	}

	kernels kers_(*this);
	for (int i = 0; i < m_kers_counts; ++i){
		kers_.mp_kers[i] -= minus_num;
	}

	return kers_;
}

bool kernels::operator-=(DATA_TYPE add_num){
	if (0 >= m_rows || 0 >= m_cols || 0 >= m_channels || 0 >= m_kers_counts){
		DEBUG_PRINT("(0 >= m_rows || 0 >= m_cols||0>=m_channels) kernels::operator- \n");
		m_channels = m_rows = m_cols = m_kers_counts = 0;
		mp_kers = NULL;
		return false;
	}
	if (NULL == mp_kers){
		DEBUG_PRINT("(NULL == mp_kers) kernels::operator+ \n");
		m_channels = m_rows = m_cols = m_kers_counts = 0;
		return false;
	}

	//kernels kers_(*this);
	for (int i = 0; i < m_kers_counts; ++i){
		mp_kers[i] -= add_num;
	}

	return true;
}

kernels operator+(const DATA_TYPE add_num, const kernels &add_kernels){
	if (0 >= add_kernels.m_rows || 0 >= add_kernels.m_cols || 0 >= add_kernels.m_channels || 0 >= add_kernels.m_kers_counts){
		DEBUG_PRINT("(0 >= add_kernels.m_rows || 0 >= add_kernels.m_cols || 0 >= add_kernels.m_channels \
					|| 0 >= add_kernels.m_kers_counts) kernels::operator+ \n");
		//add_kernels.m_rows = add_kernels.m_cols = add_kernels.m_channels = 0;
		return add_kernels;
	}
	if (NULL == add_kernels.mp_kers){
		DEBUG_PRINT("(NULL == mp_kers) operator+ \n");
		return add_kernels;
	}

	kernels kers_(add_kernels);
	for (int i = 0; i < add_kernels.m_kers_counts; ++i){
		kers_.mp_kers[i] += add_num;
	}

	return kers_;
}

kernels kernels::operator+(const kernels &add_kernels){
	if (0 >= add_kernels.m_rows || 0 >= add_kernels.m_cols || 0 >= add_kernels.m_channels || 0 >= add_kernels.m_kers_counts){
		DEBUG_PRINT("(0 >= add_kernels.m_rows || 0 >= add_kernels.m_cols || 0 >= add_kernels.m_channels \
						|| 0 >= add_kernels.m_kers_counts) kernels::operator+ \n");
		//add_kernels.m_rows = add_kernels.m_cols = add_kernels.m_channels = 0;
		return *this;
	}
	if (NULL == add_kernels.mp_kers){
		DEBUG_PRINT("(NULL == mp_kers) operator+ \n");
		return *this;
	}

	if (0 >= m_rows || 0 >= m_cols || 0 >= m_channels || 0 >= m_kers_counts || NULL == add_kernels.mp_kers){
		DEBUG_PRINT("(0 >= m_rows || 0 >= m_cols || 0 >= m_channels || 0 >= m_kers_counts)\
					 kernels::operator+ \n");
		m_rows = m_cols = m_channels = m_kers_counts = 0;
		mp_kers = NULL;
		return *this;
	}

	kernels kers_(*this);
	for (int i = 0; i < add_kernels.m_kers_counts; ++i){
		kers_.mp_kers[i] += add_kernels.mp_kers[i];
	}

	return kers_;
}

bool kernels::operator+=(const kernels& add_kernels){
	if (0 >= add_kernels.m_rows || 0 >= add_kernels.m_cols || 0 >= add_kernels.m_channels || 0 >= add_kernels.m_kers_counts){
		DEBUG_PRINT("(0 >= add_kernels.m_rows || 0 >= add_kernels.m_cols || 0 >= add_kernels.m_channels \
					 || 0 >= add_kernels.m_kers_counts) kernels::operator+= \n");
		//add_kernels.m_rows = add_kernels.m_cols = add_kernels.m_channels = 0;
		return false;
	}
	if (NULL == add_kernels.mp_kers){
		DEBUG_PRINT("(NULL == mp_kers) operator+ \n");
		return false;
	}

	if (0 >= m_rows || 0 >= m_cols || 0 >= m_channels || 0 >= m_kers_counts || NULL == add_kernels.mp_kers){
		DEBUG_PRINT("(0 >= m_rows || 0 >= m_cols || 0 >= m_channels || 0 >= m_kers_counts)\
					 kernels::operator+= \n");
		m_rows = m_cols = m_channels = m_kers_counts = 0;
		mp_kers = NULL;
		return false;
	}

	if (m_channels == add_kernels.m_channels&&m_rows == add_kernels.m_rows&&\
		m_cols == add_kernels.m_cols&&m_kers_counts == add_kernels.m_kers_counts){
		for (int i = 0; i < add_kernels.m_kers_counts; ++i){
			mp_kers[i] += add_kernels.mp_kers[i];
		}
		return true;
	}
	return false;
}

kernels operator-(const DATA_TYPE minus, const kernels &minus_kernels){
	if (0 >= minus_kernels.m_rows || 0 >= minus_kernels.m_cols || 0 >= minus_kernels.m_channels || 0 >= minus_kernels.m_kers_counts){
		DEBUG_PRINT("(0 >= minus_kernels.m_rows || 0 >= minus_kernels.m_cols || 0 >= minus_kernels.m_channels \
						|| 0 >= minus_kernels.m_kers_counts) features::operator- \n");
		//minus_kernels.m_rows = minus_kernels.m_cols = minus_kernels.m_channels = 0;
		return minus_kernels;
	}
	if (NULL == minus_kernels.mp_kers){
		DEBUG_PRINT("(NULL == mp_kers) operator- \n");
		return minus_kernels;
	}

	kernels kers_(minus_kernels.m_channels, minus_kernels.m_rows, \
		          minus_kernels.m_cols, minus_kernels.m_kers_counts, minus);
	for (int i = 0; i < minus_kernels.m_kers_counts; ++i){
		kers_.mp_kers[i] -= minus_kernels.mp_kers[i];
	}

	return kers_;
}

kernels kernels::operator-(const kernels &minus_kernels){
	if (0 >= minus_kernels.m_rows || 0 >= minus_kernels.m_cols || 0 >= minus_kernels.m_channels || 0 >= minus_kernels.m_kers_counts){
		DEBUG_PRINT("(0 >= minus_kernels.m_rows || 0 >= minus_kernels.m_cols || 0 >= minus_kernels.m_channels \
					|| 0 >= minus_kernels.m_kers_counts) kernels::operator- \n");
		//minus_kernels.m_rows = minus_kernels.m_cols = minus_kernels.m_channels = 0;
		return *this;
	}
	if (NULL == minus_kernels.mp_kers){
		DEBUG_PRINT("(NULL == minus_kernels.mp_kers) operator- \n");
		return *this;
	}

	if (0 >= m_rows || 0 >= m_cols || 0 >= m_channels || 0 >= m_kers_counts || NULL == minus_kernels.mp_kers){
		DEBUG_PRINT("(0 >= m_rows || 0 >= m_cols || 0 >= m_channels || 0 >= m_kers_counts)\
					kernels::operator+ \n");
		m_rows = m_cols = m_channels = m_kers_counts = 0;
		mp_kers = NULL;
		return *this;
	}

	kernels kers_(*this);
	for (int i = 0; i < minus_kernels.m_kers_counts; ++i){
		kers_.mp_kers[i] -= minus_kernels.mp_kers[i];
	}

	return kers_;
}

bool kernels::operator-=(const kernels& minus_kernels){
	if (0 >= minus_kernels.m_rows || 0 >= minus_kernels.m_cols || 0 >= minus_kernels.m_channels || 0 >= minus_kernels.m_kers_counts){
		DEBUG_PRINT("(0 >= minus_kernels.m_rows || 0 >= minus_kernels.m_cols || 0 >= minus_kernels.m_channels \
															 || 0 >= minus_kernels.m_kers_counts) kernels::operator+= \n");
		//minus_kernels.m_rows = minus_kernels.m_cols = minus_kernels.m_channels = 0;
		return false;
	}
	if (NULL == minus_kernels.mp_kers){
		DEBUG_PRINT("(NULL == mp_kers) operator+ \n");
		return false;
	}

	if (0 >= m_rows || 0 >= m_cols || 0 >= m_channels || 0 >= m_kers_counts || NULL == minus_kernels.mp_kers){
		DEBUG_PRINT("(0 >= m_rows || 0 >= m_cols || 0 >= m_channels || 0 >= m_kers_counts)\
															 kernels::operator+= \n");
		m_rows = m_cols = m_channels = m_kers_counts = 0;
		mp_kers = NULL;
		return false;
	}

	if (m_channels == minus_kernels.m_channels&&m_rows == minus_kernels.m_rows&&\
		m_cols == minus_kernels.m_cols&&m_kers_counts == minus_kernels.m_kers_counts){
		for (int i = 0; i < minus_kernels.m_kers_counts; ++i){
			mp_kers[i] -= minus_kernels.mp_kers[i];
		}
		return true;
	}
	return false;
}

kernels operator*(const DATA_TYPE scale, const kernels &mutiplier_kernels){
	if (mutiplier_kernels.m_rows <= 0 || mutiplier_kernels.m_cols <= 0 \
		|| mutiplier_kernels.m_channels <= 0||mutiplier_kernels.m_kers_counts<=0){
		DEBUG_PRINT("mutiplier_kernels.m_rows <= 0 || mutiplier_kernels.m_cols <= 0 \
					||mutiplier_kernels.m_channels<=0 \n mutiplier_kernels::operator*\n");
	}
	if (NULL == mutiplier_kernels.mp_kers){

		DEBUG_PRINT("NULL == mutiplier_kernels.mp_matrixes  mutiplier_kernels::operator*\n");
	}
	/* check -> matrix(const& mat)*/
	kernels result_kernels(mutiplier_kernels);
	for (int i = 0; i < result_kernels.m_kers_counts; ++i){
		result_kernels.mp_kers[i] *= scale;
	}

	return result_kernels;
}

kernels kernels::operator*(const DATA_TYPE scale){
	if (0 >= m_rows || 0 >=m_cols || 0 >= m_channels || 0 >= m_kers_counts){
		DEBUG_PRINT("(0 >= x.m_rows || 0 >= x.m_cols || 0 >= x.m_channels \
					|| 0 >= x.m_kers_counts) kernels::operator* \n");
		m_rows = m_cols = m_channels = m_kers_counts = 0;
		mp_kers = NULL;
		return *this;
	}
	if (NULL == mp_kers){
		DEBUG_PRINT("(NULL == x.mp_kers) operator- \n");
		m_rows = m_cols = m_channels = m_kers_counts = 0;
		return *this;
	}

	kernels kers_(*this);
	for (int i = 0; i < m_kers_counts; ++i){
		kers_.mp_kers[i] *= scale;
	}

	return kers_;
}

bool kernels::operator*=(const DATA_TYPE scale){
	if (0 >= m_rows || 0 >= m_cols || 0 >= m_channels || 0 >= m_kers_counts){
		DEBUG_PRINT("(0 >= m_rows || 0 >= m_cols||0>=m_channels) kernels::operator- \n");
		m_channels = m_rows = m_cols = m_kers_counts = 0;
		mp_kers = NULL;
		return false;
	}

	if (NULL == mp_kers){
		DEBUG_PRINT("(NULL == mp_kers) kernels::operator+ \n");
		m_channels = m_rows = m_cols = m_kers_counts = 0;
		return false;
	}

	//kernels kers_(*this);
	for (int i = 0; i < m_kers_counts; ++i){
		mp_kers[i] *= scale;
	}

	return true;
}

bool kernels::reset(DATA_TYPE val){
	if (0 >= m_channels || 0 >= m_rows || 0 >= m_cols || 0 >= m_kers_counts || NULL == mp_kers){
		m_channels = m_rows = m_cols = m_kers_counts = 0;
		mp_kers = NULL;
		return false;
	}

	for (int i = 0; i < m_kers_counts; ++i){
		mp_kers[i].reset(val);
	}
	return true;
}