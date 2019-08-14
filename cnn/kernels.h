#ifndef  _KERNELS_H_
#define _KERNELS_H_

#include "features.h"

class kernels{
public:
	kernels();
	kernels(const kernels &ker_);
	/* todo �ƺ�����������������װ��ģ����ȽϺ��� */
	kernels(int channels, int rows, int cols, int kernels_count, int val);
	kernels(int channels, int rows, int cols, int kernels_count, DATA_TYPE val);

	/* todo �ƺ�����������������װ��ģ����ȽϺ��� */
	kernels(int channels, int rows, int cols, int kernels_count, int min, int max);
	kernels(int channels, int rows, int cols, int kernels_count, DATA_TYPE 
		    min, DATA_TYPE max); 
	~kernels();
	kernels& operator=(const kernels& ker_);
	bool show(int image_show_mode = SHOW_IMAGE_INITAIL_VALUE);
	//bool reshape(int mode = KERNELS2MATRIEX);
public:
	kernel* mp_kers;
	int m_channels;
	int m_rows;
	int m_cols;
	int m_kers_counts;
    //matrix m_kers_mat;
};

#endif
