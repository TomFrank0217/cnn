#ifndef _LAYER_H_
#define  _LAYER_H

#include "kernels.h"
#include "features.h"
/* ʵ����ȫ���Ӳ�Ҳ�����Ǿ������ʵ�� */
/* 120->84  ���Կ�����120*1*1���� ��120*1*1*84�������ȥ���,�Ӷ��õ�84*1*1������ */

class layer{
public:
    layer();
	/* todo layer��ĳ�ʼ�� ��������������ĳ�ʼ�� */
    layer(int kers_channels, int kers_rows, int kers_cols, int kers_count, \
        int fts_channels/*kers_channels*/, int fts_rows, int fts_cols);
    matrix conv();
	/* reshape��ǰ�� reshape_�Ǻ��� */
	bool reshape(features& src_fts, matrix& dst_fts_mat);
	bool reshape_(matrix& src_fts_mat_diff, features& dst_fts_diff);

	bool reshape(kernels& src_kers, matrix& dst_kers_mat);
	bool reshape_(matrix& src_kers_mat_diff, kernels& dst_kers_diff);

	bool reshape(matrix& src_conv_mat, features& dst_conv_mat2fts);
	bool reshape_(features& src_conv_mat2fts_diff, matrix& dst_conv_mat_diff);

    ~layer();
public:
	/* ǰ�򴫲����򴫲���ʱ�������pooling�㣬kers,conv_mat,conv_mat2fts��Ϊ�� */

	features m_fts;
	//features m_fts_diff;
	matrix m_fts_mat;
	//matrix m_fts_mat_diff;

	kernels m_kers;
	//kernels m_kers_diff;
	matrix m_kers_mat;
	//matrix m_kers_mat_diff;
	
	matrix m_conv_mat;
	//matrix conv_mat_diff;
    features m_conv_mat2fts;
	//features conv_mat2fts_diff;
};

#endif