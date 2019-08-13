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

//bool kernels::reshape(int mode){
//
//	int ROWS = m_channels;
//	int COLS = m_kers_counts;
//	int rows = m_rows;
//	int cols = m_cols;
//	int i = 0;
//	int j = 0;
//
//	switch(mode)
//	{
//		/* (R,C,r,c)->(i,j)
//		(ROW,COL,row,col->(kernels_matrix.row, kernels_matrix.col)) */
//	case KERNELS2MATRIEX:
//		/* todo 此处代码可以优化 for example 交换 R C 的循环顺序 */
//		for (int R = 0; R < ROWS; ++R){
//			for (int C = 0; C < COLS; ++C){
//				for (int r = 0; r < rows; ++r){
//					for (int c = 0; c < cols; ++c){
//						i = R*rows*cols + r*cols + c;
//						j = C;
//						m_kers_mat.mp_data[i*m_kers_mat.m_cols + j] = \
//							mp_kers[C].mp_matrixes[R].mp_data[r*cols + c];
//					}
//				}
//			}
//		}
//		/* 此处是核心代码 */
//		break;
//	case MATRIEX2KERNELS:
//		int kernels_matrix_rows = m_rows*m_cols*m_channels;
//		int kernels_matrix_cols = m_kers_counts;
//		//m_kers_mat = matrix(kernels_matrix_rows, kernels_matrix_cols);
//		/* kernels是个四维张量，要确定m_kers_mat（i，j）
//		在kernels种的具体位置需要一个四维向量（ROW,COL,row,col）
//		即确定一个(向量)定位函数loc. st loc(i,j)=（ROW,COL,row,col）*/
//		int ROW = 0;
//		int COL = 0;
//		int row = 0;
//		int col = 0;
//		int index = 0;
//		if (NULL != mp_tensors1){
//			delete[] mp_tensors1;
//			mp_tensors1 = NULL;
//		}
//		mp_tensors1 = new kernel[m_kers_counts];
//		if (NULL != mp_kers){
//			for (int i = 0; i < m_kers_counts; ++i){
//				*(mp_tensors1 + i) = *(mp_kers + i);
//			}
//		}
//		else{
//			std::cout << "if (NULL != mp_kers)\n \
//						 bool kernels::reshape(int mode)\n";
//			return false;
//		}
//
//		for (int i = 0; i < kernels_matrix_rows; ++i){
//			for (int j = 0; j < kernels_matrix_cols; ++j){
//				;/* todo 此处代码可以优化 */
//				ROW = i / (m_rows*m_cols);
//				COL = j;
//				index = i - ROW*m_rows*m_cols;
//				row = index / m_cols;
//				col = index - row*m_cols;
//				mp_tensors1[COL].mp_matrixes[ROW].mp_data[row*m_cols + col] \
//					= m_kers_mat.mp_data[i*kernels_matrix_cols + j];
//			}
//		}
//		/* 以上是核心代码 */
//		break;
//
//	//default:
//	//	std::cout << "bool kernels::reshape(int mode)\n default\n";
//	//	break;
//	}
//
//	return true;
//}