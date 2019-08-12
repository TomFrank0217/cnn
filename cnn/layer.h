#ifndef _LAYER_H_
#define  _LAYER_H

#include "kernels.h"
#include "features.h"

class layer{
public:
    layer();
    layer(int kers_channels, int kers_rows, int kers_cols, int kers_count, \
        int fts_channels/*kers_channels*/, int fts_rows, int fts_cols);
    ~layer();
public:
    kernels kers;
    features fts;
    matrix conv_matrix;
    features conv_matrix_fts;
    //int m_kers_channels;
    //int m_kers_rows;
    //int m_kers_cols;
    //int m_kers_count;
    //int m_fts_channels;/* == m_kers_channels */
    //int m_fts_rows;
    //int m_fts_cols;
};

#endif