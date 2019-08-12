#include "layer.h"

layer::layer(){
    //m_kers_channels = m_kers_rows \
    //    = m_kers_cols = m_kers_count = 0;
    //m_fts_channels = m_fts_rows = m_fts_cols = 0;
    kers = kernels();
    fts = features();
}

layer::layer(int kers_channels, int kers_rows, int kers_cols, int kers_count, \
    int fts_channels/*kers_channels*/, int fts_rows, int fts_cols){
    kers = kernels(kers_channels, kers_rows, kers_cols,kers_count,\
        - 3, 3);/* todo kers初始化需要很小的初始值 */
    fts = features(fts_channels, fts_rows, fts_cols, -2, 2);
}

layer::~layer(){
    ;
}

matrix layer::conv(){
    return fts.m_features_matrix*kers.m_kernels_matrix;
}