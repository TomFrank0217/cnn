#include "layer.h"

layer::layer(){
    //m_kers_channels = m_kers_rows \
    //    = m_kers_cols = m_kers_count = 0;
    //m_fts_channels = m_fts_rows = m_fts_cols = 0;
    m_kers = kernels();
    m_fts = features();
}

layer::layer(int kers_channels, int kers_rows, int kers_cols, int kers_count, \
    int fts_channels/*kers_channels*/, int fts_rows, int fts_cols){
    m_kers = kernels(kers_channels, kers_rows, kers_cols,kers_count,\
		- 1, 1);/* todo kers初始化需要很小的初始值 */
	m_fts = features(fts_channels, fts_rows, fts_cols, 0, 1);/* todo 初始化为double 型 */
}

layer::~layer(){
    ;
}


matrix layer::conv(){
	/* todo check two mats */
	return m_fts_mat*m_kers_mat;
}

bool layer::reshape(kernels& src_kers, matrix& dst_kers_mat){
	/* (R,C,r,c)->(i,j)
	(ROW,COL,row,col->(kernels_matrix.row, kernels_matrix.col)) */
	/* todo 此处代码可以优化 for example 交换 R C 的循环顺序 */
	int dst_kers_mat_rows = src_kers.m_channels *src_kers.m_rows*src_kers.m_cols;
	int dst_kers_mat_cols = src_kers.m_kers_counts;
	dst_kers_mat = matrix(dst_kers_mat_rows, dst_kers_mat_cols);
	int i = 0;
	int j = 0;

	for (int R = 0; R < src_kers.m_channels; ++R){
		for (int C = 0; C < src_kers.m_kers_counts; ++C){
			for (int r = 0; r < src_kers.m_rows; ++r){
				for (int c = 0; c < src_kers.m_cols; ++c){
					i = R*src_kers.m_rows*src_kers.m_cols + r*src_kers.m_cols + c;
					j = C;
					dst_kers_mat.mp_data[i*dst_kers_mat.m_cols + j] = \
						src_kers.mp_kers[C].mp_matrixes[R].mp_data[r*src_kers.m_cols + c];
				}
			}
		}
	}
	return true;
}

bool layer::reshape_(matrix& src_kers_mat_diff, kernels& dst_kers_diff){
	//int kernels_matrix_rows = m_rows*m_cols*m_channels;
	//int kernels_matrix_cols = m_kers_counts;
	//m_kers_mat = matrix(kernels_matrix_rows, kernels_matrix_cols);
	/* kernels是个四维张量，要确定m_kers_mat（i，j）
	在kernels种的具体位置需要一个四维向量（ROW,COL,row,col）
	即确定一个(向量)定位函数loc. st loc(i,j)=（ROW,COL,row,col）*/
	int ROW = 0;
	int COL = 0;
	int row = 0;
	int col = 0;
	int index = 0;

	dst_kers_diff =kernels\
		(m_kers.m_channels, m_kers.m_rows, m_kers.m_cols, m_kers.m_kers_counts, 0.0);

	for (int i = 0; i < src_kers_mat_diff.m_rows; ++i){
		for (int j = 0; j < src_kers_mat_diff.m_cols; ++j){
			;/* todo 此处代码可以优化 */
			ROW = i / (m_kers.m_rows*m_kers.m_cols);
			COL = j;
			index = i - ROW*(m_kers.m_rows*m_kers.m_cols);
			row = index / m_kers.m_cols;
			col = index - row*m_kers.m_cols;
			dst_kers_diff.mp_kers[COL].mp_matrixes[ROW].mp_data[row*m_kers.m_cols + col] \
				= src_kers_mat_diff.mp_data[i*src_kers_mat_diff.m_cols + j];
		}
	}
	/* 以上是核心代码 */
	return true;
}