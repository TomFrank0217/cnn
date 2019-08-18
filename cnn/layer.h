#ifndef _LAYER_H_
#define  _LAYER_H_

#include "kernels.h"
#include "features.h"
#include "layers_parameters.h"

/* ʵ����ȫ���Ӳ�Ҳ�����Ǿ������ʵ�� */
/* 120->84  ���Կ�����120*1*1���� ��120*1*1*84�������ȥ���,�Ӷ��õ�84*1*1������ */

class layer{
public:
    layer();
	/* todo layer��ĳ�ʼ�� ��������������ĳ�ʼ�� */
	/* todo to delete */
    layer(int kers_channels, int kers_rows, int kers_cols, int kers_count, \
        int fts_channels/*kers_channels*/, int fts_rows, int fts_cols);
	/* todo to delete */
	layer(layer_parameters layer_params_, cv::Mat image);
	layer(int channels, int rows, int cols, layer_parameters* layer_params_);
	layer(layer_parameters ly_params);
    //layer(int kers_channels, int kers_rows, int kers_cols, int kers_count, \
        int fts_channels/*kers_channels*/, int fts_rows, int fts_cols,cv::Mat image)
	
	bool show_shapes();
	matrix conv();
	/* reshape��ǰ�� reshape_�Ǻ��� */
	/* (channel, row ,col) -> (i,j) �ǵ���(f)��(i,j) -> (channel, row ,col)�Ƕ���
	   ���f���ǿ���ӳ��  ����reshape���򴫲�ֱ�Ӹ�ֵ���ݶȷ��򴫲���Ҫ�ۼӸ�ֵ */
	bool reshape(features& src_fts, matrix& dst_fts_mat);
	bool reshape_(matrix& src_fts_mat_diff, features& dst_fts_diff);

	/* �˴���һһӳ���ϵ�����������򴫲�����ֱ�Ӹ�ֵ������Ҫ��features�е��ۼӹ��� */
	bool reshape(kernels& src_kers, matrix& dst_kers_mat);
	bool reshape_(matrix& src_kers_mat_diff, kernels& dst_kers_mat_diff);

	/* �˴���һһӳ���ϵ�����������򴫲�����ֱ�Ӹ�ֵ������Ҫ��features�е��ۼӹ��� */
	bool reshape(matrix& src_conv_mat, features& dst_conv_mat2fts);
	bool reshape_(features& src_conv_mat2fts_diff, matrix& dst_conv_mat_diff);
    /* ��������reshape �Ǿ����ĺ��Ĵ��� */

	bool reshape(features& pooling_mask, features& dst_fts);
    ~layer();
public:
	int m_layer_mode;//
	int m_stride;//
	int m_padding_mode;//
	int m_relu;//
	int m_pooling_mode;
	int m_pooling_size;//
	/* ǰ�򴫲����򴫲���ʱ�������pooling�㣬kers,conv_mat,conv_mat2fts��Ϊ�� */
	features m_fts;
	features m_fts_diff;
	/* diffs=diff(1)+diff(2)+diff(3)+...+diff(batch_size-1)+diff(batch_size) */
	features m_fts_diffs;/* m_fts_diff����Ҫ�ۼƣ�ֻ�����ڴ���,��������ǲ��ǿ���ȥ�� */
	matrix m_fts_mat;
	matrix m_fts_mat_diff;
	matrix m_fts_mat_diffs;/* m_fts_mat_diff ����Ҫ�ۼƣ�ֻ�����ڴ���,��������ǲ��ǿ���ȥ�� */

	kernels m_kers;
	kernels m_kers_diff;
	kernels m_kers_diffs;
	matrix m_kers_mat;
	matrix m_kers_mat_diff;
	matrix m_kers_mat_diffs;

    matrix m_conv_mat;  
    matrix m_relu_mask;  /* 0,1���� ��ʾ���� */ 
    matrix m_conv_relu_mat; 
    matrix m_conv_mat_diff;  
	matrix m_conv_mat_diffs;/* conv_mat_diff ����Ҫ�ۼƣ�ֻ�����ڴ���,��������ǲ��ǿ���ȥ�� */
    matrix m_conv_relu_mat_diff; 
    matrix m_conv_relu_mat_diffs;

    features m_conv_relu_mat2fts;
	features m_conv_relu_mat2fts_diff;
	features m_conv_relu_mat2fts_diffs;/* conv_mat2fts_diff ����Ҫ�ۼƣ�ֻ�����ڴ���,��������ǲ��ǿ���ȥ�� */
    features m_pooling_mask; 
    features m_pooling_features;
};

#endif