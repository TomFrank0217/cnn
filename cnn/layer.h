//#ifndef _LAYER_H_
//#define  _LAYER_H
//
//#include "kernels.h"
//#include "features.h"
//
//class layer{
//public:
//    layer();
//	/* todo layer层的初始化 即卷积核与特征的初始化 */
//    layer(int kers_channels, int kers_rows, int kers_cols, int kers_count, \
//        int fts_channels/*kers_channels*/, int fts_rows, int fts_cols);
//    matrix conv();
//	bool reshape(int mode = MATRIEX2KERNELS);
//    ~layer();
//public:
//	/* 前向传播后向传播的时候，如果是pooling层，kers设为空 */
//    kernels kers;
//    featuresssss fts;
//    matrix conv_matrix;
//    featuresssss conv_matrix_fts;
//
//};
//
//#endif