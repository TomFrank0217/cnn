#ifndef _LAYER_H_
#define  _LAYER_H_

#include "kernels.h"
#include "features.h"
#include "layers_parameters.h"

/* 实际上全连接层也看作是卷积层来实现 */
/* 120->84  可以看作是120*1*1特征 由120*1*1*84个卷积核去卷积,从而得到84*1*1个特征 */

class layer{
public:
    layer();
	/* todo layer层的初始化 即卷积核与特征的初始化 */
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
	/* reshape是前向 reshape_是后向 */
	/* (channel, row ,col) -> (i,j) 是单射(f)，(i,j) -> (channel, row ,col)是多射
	   因此f不是可逆映射  特征reshape正向传播直接赋值，梯度反向传播需要累加赋值 */
	bool reshape(features& src_fts, matrix& dst_fts_mat);
	bool reshape_(matrix& src_fts_mat_diff, features& dst_fts_diff);

	/* 此处是一一映射关系，所以正向反向传播都是直接赋值，不需要做features中的累加工作 */
	bool reshape(kernels& src_kers, matrix& dst_kers_mat);
	bool reshape_(matrix& src_kers_mat_diff, kernels& dst_kers_mat_diff);

	/* 此处是一一映射关系，所以正向反向传播都是直接赋值，不需要做features中的累加工作 */
	bool reshape(matrix& src_conv_mat, features& dst_conv_mat2fts);
	bool reshape_(features& src_conv_mat2fts_diff, matrix& dst_conv_mat_diff);
    /* 以上六个reshape 是卷积层的核心代码 */

	bool reshape(features& pooling_mask, features& dst_fts);
    ~layer();
public:
	int m_layer_mode;//
	int m_stride;//
	int m_padding_mode;//
	int m_relu;//
	int m_pooling_mode;
	int m_pooling_size;//
	/* 前向传播后向传播的时候，如果是pooling层，kers,conv_mat,conv_mat2fts设为空 */
	features m_fts;
	features m_fts_diff;
	/* diffs=diff(1)+diff(2)+diff(3)+...+diff(batch_size-1)+diff(batch_size) */
	features m_fts_diffs;/* m_fts_diff不需要累计，只是用于传播,这个变量是不是可以去掉 */
	matrix m_fts_mat;
	matrix m_fts_mat_diff;
	matrix m_fts_mat_diffs;/* m_fts_mat_diff 不需要累计，只是用于传播,这个变量是不是可以去掉 */

	kernels m_kers;
	kernels m_kers_diff;
	kernels m_kers_diffs;
	matrix m_kers_mat;
	matrix m_kers_mat_diff;
	matrix m_kers_mat_diffs;

    matrix m_conv_mat;  
    matrix m_relu_mask;  /* 0,1矩阵 表示正负 */ 
    matrix m_conv_relu_mat; 
    matrix m_conv_mat_diff;  
	matrix m_conv_mat_diffs;/* conv_mat_diff 不需要累计，只是用于传播,这个变量是不是可以去掉 */
    matrix m_conv_relu_mat_diff; 
    matrix m_conv_relu_mat_diffs;

    features m_conv_relu_mat2fts;
	features m_conv_relu_mat2fts_diff;
	features m_conv_relu_mat2fts_diffs;/* conv_mat2fts_diff 不需要累计，只是用于传播,这个变量是不是可以去掉 */
    features m_pooling_mask; 
    features m_pooling_features;
};

#endif