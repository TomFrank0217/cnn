#ifndef _LAYER_H_
#define  _LAYER_H

#include "kernels.h"
#include "features.h"

class layer{
public:
    layer();
	/* todo layer��ĳ�ʼ�� ��������������ĳ�ʼ�� */
    layer(int kers_channels, int kers_rows, int kers_cols, int kers_count, \
        int fts_channels/*kers_channels*/, int fts_rows, int fts_cols);
    matrix conv();
	bool reshape(int mode = MATRIEX2KERNELS);
    ~layer();
public:
    kernels kers;
    features fts;
    matrix conv_matrix;
    features conv_matrix_fts;

};

#endif