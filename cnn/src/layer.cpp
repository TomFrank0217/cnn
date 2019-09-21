#include "../include/layer.h"

layer::layer(){
	m_padding_mode = VALID_PADDING;
	m_stride = STRIDE;

	m_fts = features();
	m_fts_diff = features();
	m_fts_diffs = features();
	m_fts_mat = matrix();
	m_fts_mat_diff = matrix();
	m_fts_mat_diffs = matrix();

	m_kers = kernels();
	m_kers_diff = kernels();
	m_kers_diffs = kernels();
	m_kers_mat = matrix();
	m_kers_mat_diff = matrix();
	m_kers_mat_diffs = matrix();

	m_conv_mat = matrix();
	m_conv_mat_diff = matrix();
	m_conv_mat_diffs = matrix();
	m_relu_mask = matrix();
	m_pooling_mask = features();
	m_pooling_features = features();
	m_conv_relu_mat_diffs = matrix();
	m_conv_relu_mat_diffs = matrix();
	m_conv_relu_mat2fts = features();
	m_conv_relu_mat2fts_diff = features();
	m_conv_relu_mat2fts_diffs = features();
}

layer::layer(int channels, int rows, int cols, layer_parameters* layer_params_){

	m_layer_mode = layer_params_->layer_mode;
	m_stride = layer_params_->stride;
	m_padding_mode = layer_params_->padding_mode;
	m_relu = layer_params_->relu;
	m_pooling_mode = layer_params_->pooling_mode;
	m_pooling_size = layer_params_->pooling_size;

	m_fts = features(channels, rows, cols, 0.0);
	m_fts_diff = features(channels, rows, cols, 0.0);
	/* diffs=diff(1)+diff(2)+diff(3)+...+diff(batch_size-1)+diff(batch_size) */
	m_fts_diffs = features(channels, rows, cols, 0.0);

	if (CONVOLUTION_LAYER == layer_params_->layer_mode || \
		FULLCONNECTION_LAYER == layer_params_->layer_mode){
		/* kernels initial  */
		/* varibales for forward propagation */
		int ker_channels = layer_params_->kernel_channels;
		int ker_rows = layer_params_->kernel_rows;
		int ker_cols = layer_params_->kernel_cols;
		int kers_counts = layer_params_->kernels_counts;
		/* varibales for back propagation */
		m_kers = kernels(ker_channels, ker_rows, ker_cols, kers_counts, KERS_MIN_VAL, KERS_MAX_VAL);
		m_kers_diff = kernels(ker_channels, ker_rows, ker_cols, kers_counts, 0);/* ��������ƺ�����Ҫ�� */
		m_kers_diffs = kernels(ker_channels, ker_rows, ker_cols, kers_counts, 0.0);
		/* variables for forward propagation */
		int kers_mat_rows = ker_channels*ker_rows*ker_cols;
		int kers_mat_cols = kers_counts;
		m_kers_mat = matrix(kers_mat_rows, kers_mat_cols, 0.0);
		m_kers_mat_T = matrix(kers_mat_cols, kers_mat_rows, 0.0);
		/* variables for back propagation*/
		m_kers_mat_diff = matrix(kers_mat_rows, kers_mat_cols, 0.0);
		m_kers_mat_diffs = matrix(kers_mat_rows, kers_mat_cols, 0.0);
		/* end initial kernels */
		int padding_size = 0; /* valid Ĭ�ϵ�padding ��ʽ */
		if (SAME_PADDING == layer_params_->padding_mode){
			padding_size = (layer_params_->kernel_rows - 1) / 2;
		}
		int fts_rows_ = (m_fts.m_rows - m_kers.m_rows + 2 * padding_size) / m_stride + 1;
		fts_rows_ *= ((m_fts.m_rows - m_kers.m_rows + 2 * padding_size) / m_stride + 1);
		int fts_cols_ = m_kers.m_rows*m_kers.m_cols*m_kers.m_channels;
		m_fts_mat = matrix(fts_rows_, fts_cols_, 0.0);
		m_fts_mat_T = matrix(fts_cols_, fts_rows_, 0.0);
		m_fts_mat_diff = matrix(fts_rows_, fts_cols_, 0.0);
		//matrix m_fts_mat_diffs;/* m_fts_mat_diff ����Ҫ�ۼƣ�ֻ�����ڴ���,��������ǲ��ǿ���ȥ�� */

		m_conv_mat = matrix(m_fts_mat.m_rows, m_kers_mat.m_cols, 0.0);
		/* ������ʱ�������relu����û�д򿪣���ʱ�ǲ���Ҫrelu_mask�ģ�����Ϊ�˷�ֹ�ظ����룬�ڳ�ʼ����ʱ���������� */
		m_relu_mask = matrix(m_fts_mat.m_rows, m_kers_mat.m_cols, 0.0); /* 0,1���� ��ʾ���� */
		m_conv_relu_mat = matrix(m_fts_mat.m_rows, m_kers_mat.m_cols, 0.0);
		/* conv_mat_diff ����Ҫ�ۼƣ�ֻ�����ڴ���,��������ǲ��ǿ���ȥ�� */
		m_conv_mat_diff = matrix(m_fts_mat.m_rows, m_kers_mat.m_cols, 0.0);
		m_conv_mat_diffs = matrix(m_fts_mat.m_rows, m_kers_mat.m_cols, 0.0);
		m_conv_relu_mat_diff = matrix(m_fts_mat.m_rows, m_kers_mat.m_cols, 0.0);
		m_conv_relu_mat_diffs = matrix(m_fts_mat.m_rows, m_kers_mat.m_cols, 0.0);
	}
	else if (POOLING_LAYER == layer_params_->layer_mode){
		m_pooling_mask = features(channels, rows, cols, 0.0);
	}
	else if (FULLCONNECTION_LAYER == layer_params_->layer_mode){
		;
	}
	//int m = 0;
	//int n = 0;
	///* todo Ҫ����������  ͷ�󣡣��� */
	//if (NULL == pre_layer_params_){
	//	/* ���ǵ�һ������ */
	//	m_fts = features(image);
	//}
	//else{
	//	if (CONVOLUTION_LAYER == pre_layer_params_->layer_mode){
	//		if (CONVOLUTION_LAYER == layer_params_->layer_mode){
	//			;
	//		}
	//		else if (POOLING_LAYER == layer_params_->layer_mode){
	//			;
	//		}
	//		else if (FULLCONNECTION_LAYER == layer_params_->layer_mode){
	//			;
	//		}
	//	}
	//	else if (POOLING_LAYER == pre_layer_params_->layer_mode){
	//		if (CONVOLUTION_LAYER == layer_params_->layer_mode){
	//			;
	//		}
	//		else if (POOLING_LAYER == layer_params_->layer_mode){
	//			;
	//		}
	//		else if (FULLCONNECTION_LAYER == layer_params_->layer_mode){
	//			;
	//		}
	//	}
	//	else if (FULLCONNECTION_LAYER == pre_layer_params_->layer_mode){
	//		if (CONVOLUTION_LAYER == layer_params_->layer_mode){
	//			;
	//		}
	//		else if (POOLING_LAYER == layer_params_->layer_mode){
	//			;
	//		}
	//		else if (FULLCONNECTION_LAYER == layer_params_->layer_mode){
	//			;
	//		}
	//	}
	//}
}

/* ʵ���������һ���߼��ϵ�ȱ�ݣ���һ��һ���Ǿ������*/
//layer::layer(layer_parameters layer_params_, cv::Mat image){
//	/* kernels initial  */
//	/* varibales for forward propagation */
//	int ker_channels = layer_params_.kernel_channels;
//	int ker_rows = layer_params_.kernel_rows;
//	int ker_cols = layer_params_.kernel_cols;
//	int kers_counts = layer_params_.kernels_counts;
//	/* varibales for back propagation */
//	m_kers = kernels(ker_channels, ker_rows, ker_cols, kers_counts, KERS_MIN_VAL, KERS_MAX_VAL);
//	//m_kers_diff = kernels(ker_channels, ker_rows, ker_cols, kers_counts, 0);/* ��������ƺ�����Ҫ�� */
//	m_kers_diffs = kernels(ker_channels, ker_rows, ker_cols, kers_counts, 0.0);
//	/* variables for forward propagation */
//	int kers_mat_rows = ker_channels*ker_rows*ker_cols;
//	int kers_mat_cols = kers_counts;
//	m_kers_mat = matrix(kers_mat_rows, kers_mat_cols, 0.0);
//	/* variables for back propagation*/
//	m_kers_mat_diff = matrix(kers_mat_rows, kers_mat_cols, 0.0);
//	m_kers_mat_diffs = matrix(kers_mat_rows, kers_mat_cols, 0.0);
//	/* end initial kernels */
//
//	m_stride = layer_params_.stride;
//
//	/* features initial from image */
//	/* todo check image */
//	m_fts = features(image);
//	m_fts_diff = features(image.channels(), image.rows, image.cols, 0.0);
//	/* diffs=diff(1)+diff(2)+diff(3)+...+diff(batch_size-1)+diff(batch_size) */
//	m_fts_diffs = features(image.channels(), image.rows, image.cols, 0.0);
//	int padding_size = 0; /* valid Ĭ�ϵ�padding ��ʽ */
//	if (SAME_PADDING == layer_params_.padding_mode){
//		padding_size = (layer_params_.kernel_rows - 1) / 2;
//	}
//	int fts_rows_ = (m_fts.m_rows-m_kers.m_rows+2*padding_size)/m_stride + 1;
//	fts_rows_ *= ((m_fts.m_rows - m_kers.m_rows + 2 * padding_size) / m_stride + 1);
//	int fts_cols_ = m_kers.m_rows*m_kers.m_cols*m_kers.m_channels;
//	//m_fts_mat = matrix(fts_rows_, fts_cols_, 0.0);
//	//m_fts_mat_diff = matrix(fts_rows_, fts_cols_, 0.0);
//	//matrix m_fts_mat_diffs;/* m_fts_mat_diff ����Ҫ�ۼƣ�ֻ�����ڴ���,��������ǲ��ǿ���ȥ�� */
//
//	/* conv relu */
//	int rows = m_fts_mat.m_rows;
//	int cols = m_kers_mat.m_cols;
//	m_conv_mat = matrix(rows, cols, INITIAL_NUMBER);
//	m_conv_mat_diff = matrix(rows, cols, INITIAL_NUMBER);/* todo  to delete */
//	//m_conv_mat_diffs = matrix(rows, cols, INITIAL_NUMBER);/* todo to delete */
//	m_relu_mask = matrix(rows, cols, 0);
//	m_conv_relu_mat = matrix(rows, cols, 0);
//	m_conv_relu_mat_diff = matrix(rows, cols, 0);
//	//m_pooling_mask = matrix(rows, cols, 0);
//	//m_pooling_features = matrix(rows, cols, 0);
//	m_conv_relu_mat_diffs = matrix(rows, cols, 0);
//	/* todo not valid_padding */
//
//	int m = (m_fts.m_rows - m_kers.m_rows + 2 * padding_size) / stride + 1;
//	int n = (m_fts.m_cols - m_kers.m_cols + 2 * padding_size) / stride + 1;
//	m_conv_relu_mat2fts = features(m_kers.m_channels, m, n, INITIAL_NUMBER);
//	m_conv_relu_mat2fts_diff = features(m_kers.m_channels, m, n, INITIAL_NUMBER);
//	m_conv_relu_mat2fts_diffs = features(m_kers.m_channels, m, n, INITIAL_NUMBER);
//}

//layer::layer(int kers_channels, int kers_rows, int kers_cols, int kers_count, \
//    int fts_channels/*kers_channels*/, int fts_rows, int fts_cols){
//	if (kers_channels != fts_channels){
//		DEBUG_PRINT("(kers_channels != fts_channels)\n");
//		return;
//	}
//	m_padding_mode = VALID_PADDING;
//	stride = STRIDE;
//	/* todo ��ʼ��Ϊdouble �� */
//	m_fts = features(fts_channels, fts_rows, fts_cols, -INITIAL_NUMBER, INITIAL_NUMBER);
//	m_fts_diff = features(fts_channels, fts_rows, fts_cols, -INITIAL_NUMBER, INITIAL_NUMBER);
//	m_fts_diffs = features(fts_channels, fts_rows, fts_cols, -INITIAL_NUMBER, INITIAL_NUMBER);
//
//	int r = (fts_rows - kers_rows) / stride + 1;
//	r *= ((fts_cols- kers_cols) / stride + 1);
//	int c = kers_rows*kers_cols*kers_channels;
//	m_fts_mat = matrix(r, c, 0.0);
//	m_fts_mat_diff = matrix(r, c, INITIAL_NUMBER);
//    m_fts_mat_diffs = matrix(r, c, INITIAL_NUMBER);/* to delete */
//
//	/* todo kers��ʼ����Ҫ��С�ĳ�ʼֵ */
//	m_kers = kernels(kers_channels, kers_rows, kers_cols, kers_count, -INITIAL_NUMBER, INITIAL_NUMBER);
//	m_kers_diff = kernels(kers_channels, kers_rows, kers_cols, kers_count, -INITIAL_NUMBER, INITIAL_NUMBER);
//	m_kers_diffs = kernels(kers_channels, kers_rows, kers_cols, kers_count, -INITIAL_NUMBER, INITIAL_NUMBER);
//	int kers_mat_rows = m_kers.m_channels *m_kers.m_rows*m_kers.m_cols;
//	int kers_mat_cols = m_kers.m_kers_counts;
//	m_kers_mat = matrix(kers_mat_rows, kers_mat_cols, INITIAL_NUMBER);
//	m_kers_mat_diff = matrix(kers_mat_rows, kers_mat_cols, INITIAL_NUMBER);
//    m_kers_mat_diffs = matrix(kers_mat_rows, kers_mat_cols, INITIAL_NUMBER);/* to delete */
//
//	int rows = m_fts_mat.m_rows;
//	int cols = m_kers_mat.m_cols;
//	m_conv_mat = matrix(rows, cols, INITIAL_NUMBER);
//    m_conv_mat_diff = matrix(rows, cols, INITIAL_NUMBER);/* todo  to delete */
//    m_conv_mat_diffs = matrix(rows, cols, INITIAL_NUMBER);/* todo to delete */
//    m_relu_mask = matrix(rows, cols, 0);
//    m_conv_relu_mat = matrix(rows, cols, 0);
//    m_conv_relu_mat_diffs = matrix(rows, cols, 0);
//    //m_pooling_mask = matrix(rows, cols, 0);
//    //m_pooling_features = matrix(rows, cols, 0);
//    m_conv_relu_mat_diffs = matrix(rows, cols, 0);
//	/* todo not VALID_PADDING */
//	int m = (m_fts.m_rows - m_kers.m_rows) / stride + 1;
//	int n = (m_fts.m_cols - m_kers.m_cols) / stride + 1;
//	m_conv_relu_mat2fts = features(m_kers.m_channels, m, n, INITIAL_NUMBER);
//	m_conv_relu_mat2fts_diff = features(m_kers.m_channels, m, n, INITIAL_NUMBER);
//	m_conv_relu_mat2fts_diffs = features(m_kers.m_channels, m, n, INITIAL_NUMBER);
//}

layer::layer(layer_parameters ly_params){

}

layer::~layer(){
	;
}


matrix layer::conv(){
	/* todo check two mats */
	reshape(m_fts, m_fts_mat);
	reshape(m_kers, m_kers_mat);
	m_conv_mat = m_fts_mat*m_kers_mat;
	return  m_conv_mat;
}

bool layer::reshape(kernels& src_kers, matrix& dst_kers_mat){
	/* (R,C,r,c)->(i,j)
	(ROW,COL,row,col->(kernels_matrix.row, kernels_matrix.col)) */
	/* todo �˴���������Ż� for example ���� R C ��ѭ��˳�� */
	if (NULL == src_kers.mp_kers){
		DEBUG_PRINT("(NULL == src_kers.mp_kers)\
								layer::reshape(kernels& src_kers, matrix& dst_kers_mat) \n");
		return false;
	}
	int dst_kers_mat_rows = src_kers.m_channels *src_kers.m_rows*src_kers.m_cols;
	int dst_kers_mat_cols = src_kers.m_kers_counts;
	if (NULL == dst_kers_mat.mp_data){
		dst_kers_mat = matrix(dst_kers_mat_rows, dst_kers_mat_cols, 0.0);
	}
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
	/* kernels�Ǹ���ά������Ҫȷ��m_kers_mat��i��j��
	��kernels�ֵľ���λ����Ҫһ����ά������ROW,COL,row,col��
	��ȷ��һ��(����)��λ����loc. st loc(i,j)=��ROW,COL,row,col��*/
	int ROW = 0;
	int COL = 0;
	int row = 0;
	int col = 0;
	int index = 0;

	//src_kers_mat_diff.show_shape();
	//dst_kers_diff.show_shape();
	if (NULL == src_kers_mat_diff.mp_data){
		DEBUG_PRINT("(NULL == src_kers_mat_diff.mp_data)\
										layer::reshape_(matrix& src_kers_mat_diff, kernels& dst_kers_diff)");
		return false;
	}
	if (NULL == dst_kers_diff.mp_kers){
		dst_kers_diff = kernels(m_kers.m_channels, \
			m_kers.m_rows, m_kers.m_cols, m_kers.m_kers_counts, 0.0);
	}

	for (int i = 0; i < src_kers_mat_diff.m_rows; ++i){
		for (int j = 0; j < src_kers_mat_diff.m_cols; ++j){
			;/* todo �˴���������Ż� */
			ROW = i / (m_kers.m_rows*m_kers.m_cols);
			COL = j;
			index = i - ROW*(m_kers.m_rows*m_kers.m_cols);
			row = index / m_kers.m_cols;
			col = index - row*m_kers.m_cols;
			dst_kers_diff.mp_kers[COL].mp_matrixes[ROW].mp_data[row*m_kers.m_cols + col] \
				= src_kers_mat_diff.mp_data[i*src_kers_mat_diff.m_cols + j];
		}
	}
	/* �����Ǻ��Ĵ��� */
	return true;
}

/* forward propagation �����ͼ1 */
bool layer::reshape(features& src_fts, matrix& dst_fts_mat){
	if (NULL == src_fts.mp_matrixes){
		DEBUG_PRINT("(NULL == src_fts.mp_matrixes)\
									   layer::reshape(features& src_fts, matrix& dst_fts_mat)\n");
		return false;
	}

	if (NULL == dst_fts_mat.mp_data){
		if (VALID_PADDING == m_padding_mode){
			int rows = (src_fts.m_rows - m_kers.m_rows) / m_stride + 1;
			rows *= ((src_fts.m_cols - m_kers.m_cols) / m_stride + 1);
			int cols = m_kers.m_rows*m_kers.m_cols*m_kers.m_channels;
			dst_fts_mat = matrix(rows, cols, 0.0);
		}
		else{
			DEBUG_PRINT("todo (VALID_PADDING == padding_mode)\n");
			return false;
		}
	}
	/* �˴��Ǻ��Ĵ��� */
	/* ��G: features -> matrix */
	/* ����Ҫѧϰ������һ��ӳ���ϵf  ����һ�������ֵ�Ĺ��� */
	/* s.t. f: matrix�еĵ�(i,j)��pixel ->  features�е�(channel,row,col)��Ԫ�� */
	/* �򻯼��� f: (i,j) -> (channel,rpf,cpf) *******************************
	******(channel,rpf,cpf) = (channel,row_pixel_feature,col_pixel_feature): */
	/* ���� rpf cpf �Ķ������� */
	int channel = 0;/* channel channel_in_features ��features_matrix��(i,j)��pixel ��ԭʼ����ͼ�е�ͨ���� */
	int rpf = 0;    /* rpf row_pixel_feature ��features_matrix��(i,j)��pixel ��ԭʼ����ͼ�е����� */
	int cpf = 0;    /* cpf col_pixel_feature ��features_matrix��(i,j)��pixel ��ԭʼ����ͼ�е����� */

	int rpk = 0;/* rpk ��features_matrix��(i,j)��pixel �ھ����(��ά)�е����� */
	int cpk = 0;/* cpk ��features_matrix��(i,j)��pixel �ھ����(��ά)�е����� */
	/* rkf ��features_matrix��(i,j)��pixel ��Ӧ�Ķ�ά�����(���Ϸ�Ԫ��)�������е����� */
	int rkf = 0;
	/* ckf ��features_matrix��(i,j)��pixel ��Ӧ�Ķ�ά�����(���Ϸ�Ԫ��)�������е����� */
	int ckf = 0;
	/* ����ѧϰ�Ĳ�����ֱ�ӵõ� f: (i,j) -> (channel,rpf,cpf) ��ӳ���ϵ */
	/* ʵ��������Ѱ�ҵ�����ӳ���ϵ g��h,  s.t. f=h*g ������һ�����Ϻ����Ĺ�ϵ */
	/* ��һ���� g: (i,j)->(c,rpk,cpk,rkf,ckf)��ӳ���ϵ,
	/* �ڶ����� h:(channel,rpk,cpk,rkf,ckf)-> (channel,rpf,cpf) */
	/* f=h*g��һ�����Ϻ�����ϵ */

	/* index_in_kernels��������������Ԫ������ڵ���(��ά)����˵����λ�ã�һά��*/
	int index_in_kernel = 0;
	/* ����ţ����ѧ�е����λ�ã�������ת����\
	�ܹ�ȷ��features_matrixԪ�ض�Ӧ����ԭʼfeatures�еľ���λ�� */
	/* �����֮������ A�����C��λ�� = A�����B��λ�� + B�����C��λ�� */
	switch (m_padding_mode){
		/* features 2 matrix */
	case VALID_PADDING: /* (N+2P-K)/S +1 */
		/* �����Ǻ��Ĵ��� features2matrix */
		/* todo �˴���������Ż� */
		for (int i = 0; i < dst_fts_mat.m_rows; ++i){
			for (int j = 0; j < dst_fts_mat.m_cols; ++j){
				/* (i,j) -> (channel,rpk,cpk,rkf,ckf) */
				channel = j / (m_kers.m_rows*m_kers.m_cols);
				index_in_kernel = j - channel*(m_kers.m_rows*m_kers.m_cols);
				rpk = index_in_kernel / m_kers.m_cols;
				cpk = index_in_kernel - rpk*m_kers.m_cols;
				rkf = i / ((src_fts.m_cols - m_kers.m_cols) / m_stride + 1);
				ckf = i - rkf*((src_fts.m_cols - m_kers.m_cols) / m_stride + 1);

				/* (channel,rpk,cpk,rkf,ckf) -> (channel,rpf,cpf)*/
				//channel=channel;
				/* A�����C��λ�� = A�����B��λ�� + B�����C��λ�� */
				rpf = rpk + rkf;/* Ԫ����ԭʼ�����е����� = Ԫ���ھ����(��ά)�е����� + �����(��ά)�������е����� */
				cpf = cpk + ckf;/* Ԫ����ԭʼ�����е����� = Ԫ���ھ����(��ά)�е����� + �����(��ά)�������е����� */
				/* Ԫ���ھ�����е�λ����ָԪ������ھ�������Ϸ�Ԫ�ض��� */
				/* �����������ͼ�е�λ����ָ��������Ϸ�Ԫ�����������ͼ���Ϸ�Ԫ�ص�λ�� */
				dst_fts_mat.mp_data[i*dst_fts_mat.m_cols + j] = \
					src_fts.mp_matrixes[channel].mp_data[rpf*src_fts.m_cols + cpf];
				//std::cout << "i=" << i << " j=" << j << std::endl;
			}
		}
		break;
	case SAME_PADDING:
		//todo
		break;
	default:
		break;
	}
	return true;
}

/* back popagation ��������Ƿ��򴫲�ʱ������,��Ҫ�޸� */
bool layer::reshape_(matrix& src_fts_mat_diff, features& dst_fts_diff)
{
	//src_fts_mat_diff.show();
	/* �˴��Ǻ��Ĵ��� */
	/* �� feature_matrix(i,j) �ع鵽ԭʼ�ĵ� features(channel,rpf,cpf) */
	/* ����Ҫѧϰ������һ��ӳ���ϵf-1, */
	/* s.t. f-1: (channel,rpf,cpf) -> (i,j) */
	/* ����һ�������ֵ�Ĺ��� ���Լ���ܶ������ ����������汻ע�͵�ǰ���ֵ���� */
	int channel = 0;/* channel channel_in_features ��features_matrix��(i,j)��pixel ��ԭʼ����ͼ�е�ͨ���� */
	int rpf = 0;    /* rpf row_pixel_feature ��features_matrix��(i,j)��pixel ��ԭʼ����ͼ�е����� */
	int cpf = 0;    /* cpf col_pixel_feature ��features_matrix��(i,j)��pixel ��ԭʼ����ͼ�е����� */

	int rpk = 0;/* rpk row_pixel_kernel ��features_matrix��(i,j)��pixel �ھ����(��ά)�е����� */
	int cpk = 0;/* cpk col_pixel_kernel ��features_matrix��(i,j)��pixel �ھ����(��ά)�е����� */
	/* rkf ��features_matrix��(i,j)��pixel ��Ӧ�Ķ�ά�����(���Ϸ�Ԫ��)�������е����� */
	int rkf = 0;
	/* ckf ��features_matrix��(i,j)��pixel ��Ӧ�Ķ�ά�����(���Ϸ�Ԫ��)�������е����� */
	int ckf = 0;
	/* index_in_kernel��������������Ԫ������ڵ���(��ά)����˵����λ�ã�*/
	int index_in_kernel = 0;

	if (NULL == src_fts_mat_diff.mp_data){
		std::cout << "(NULL == src_fts_mat_diff.mp_data)"
			<< "layer::reshape_" << std::endl;
		return false;
	}

	if (NULL == dst_fts_diff.mp_matrixes){
		std::cout << "(NULL == dst_fts_diff.mp_matrixes)"
			<< "layer::reshape_" << std::endl;
		dst_fts_diff = features(m_fts.m_channels, m_fts.m_rows, m_fts.m_cols, 0.0);
	}
	dst_fts_diff.reset(0.0);
	switch (m_padding_mode)
	{
	case VALID_PADDING:
		/* (i,j) (g)-> (channel,rpk,cpk,rkf,ckf) (h)-> (channel,rpf,cpf) */
		/* (i,j) (f)-> (channel,rpf,cpf)  ��һ����������� */
		/* ����  (channel,rpf,cpf) (f-1)-> (i,j)  ��f-1ʵ������һ��������� */
		/* �������ô����һ�δ���д��������Ҫ˼�� */
		/* ��ʵ���򴫲���ʱ����Ҫ������� f-1,��Ϊ(i,j)��ƫ����Ҫ�ۼӻ�features�е�(channel,rpf,cpf)Ԫ */
		/* todo */
		//for (channel = 0; channel < m_tensor.m_channels; ++channel){
		//	for (rpf = 0; rpf < m_tensor.m_rows; ++rpf){
		//		for (cpf = 0; cpf < m_tensor.m_cols; ++cpf){}}}

		/* mat -> features */
		/* ���´�����Ȼ��ȷ������features�кܶ�Ԫ�ر��ظ���������K*K�������˷Ѽ�����Դ */
		/* �ܶ�Ԫ�ر��ظ�����K*K���Ǳ���ģ���Ϊ���򴫲���ʱ���ݶ�features��Ԫ��ӳ�䵽
		features_matrix�ж�Σ����features��Ԫ�ص��ݶ��ݶ���Ҫ�ۼ� */
		for (int i = 0; i < src_fts_mat_diff.m_rows; ++i){
			for (int j = 0; j < src_fts_mat_diff.m_cols; ++j){
				/* g: (i,j) -> (channel,rpk,cpk,rkf,ckf) */
				channel = j / (m_kers.m_rows*m_kers.m_cols);/* �˴��˷������Ż� */
				index_in_kernel = j - channel*(m_kers.m_rows*m_kers.m_cols);
				rpk = index_in_kernel / m_kers.m_cols;
				cpk = index_in_kernel - rpk*m_kers.m_cols;
				/* this bug take me a lot of time finally i solve it
				rkf = i / ( (src_fts_mat_diff.m_cols - m_kers.m_cols)/stride + 1 );
				ckf = i - rkf*((src_fts_mat_diff.m_cols - m_kers.m_cols)/stride + 1);
				about two hours 8th Aug 2019 19:35 solved  successful */
				rkf = i / ((dst_fts_diff.m_cols - m_kers.m_cols) / m_stride + 1);
				ckf = i - rkf*((dst_fts_diff.m_cols - m_kers.m_cols) / m_stride + 1);
				/* h: (channel,rpk,cpk,rkf,ckf) -> (channel,rpf,cpf) */
				//channel = channel;
				rpf = rpk + rkf;
				cpf = cpk + ckf;
				dst_fts_diff.mp_matrixes[channel].mp_data[rpf*dst_fts_diff.m_cols + cpf]\
					+= src_fts_mat_diff.mp_data[i*src_fts_mat_diff.m_cols + j];
			}
		}
		break;
	case SAME_PADDING:
		/*todo*/
		break;
		//default:
		//	break;
	}
	return true;
}
bool layer::reshape(matrix& src_conv_mat, features& dst_conv_mat2fts){
	if (NULL == src_conv_mat.mp_data){
		DEBUG_PRINT("(NULL == src_conv_mat.mp_data)  \
										layer::reshape\n");
		return false;
	}
	if (NULL == dst_conv_mat2fts.mp_matrixes){
		int channels = m_kers.m_kers_counts;
		if (VALID_PADDING == m_padding_mode){
			int rows = (m_fts.m_rows - m_kers.m_rows) / m_stride + 1;
			int cols = (m_fts.m_cols - m_kers.m_cols) / m_stride + 1;
			dst_conv_mat2fts = features(channels, rows, cols, 0.0);
		}
		else{
			/* todo */
			DEBUG_PRINT("(VALID_PADDING == padding_mode)\n");
			return false;
		}
	}

	/* conv_mat(i,j) -> out_features(channel,row,col) */
	/* src -> dst */
	/* ���ݺ����ֵ��˼· ������Ҫ�ҵ�������һ��ӳ���ϵ f */
	/* s.t. f: (channel,row,col) -> (i,j) */
	int i = 0;
	int j = 0;
	for (int channel = 0; channel < dst_conv_mat2fts.m_channels; ++channel){
		for (int row = 0; row < dst_conv_mat2fts.m_rows; ++row){
			for (int col = 0; col < dst_conv_mat2fts.m_cols; ++col){
				j = channel;
				i = row*dst_conv_mat2fts.m_cols + col;

				//dst_conv_mat2fts.mp_matrixes[channel].mp_data[row*dst_conv_mat2fts.m_cols + col]
				dst_conv_mat2fts.mp_matrixes[channel].mp_data[i]
					= src_conv_mat.mp_data[i*src_conv_mat.m_cols + j];
			}
		}
	}
	return true;
}

bool layer::reshape_(features& src_conv_mat2fts_diff, matrix& dst_conv_mat_diff){
	if (NULL == src_conv_mat2fts_diff.mp_matrixes){
		DEBUG_PRINT("(NULL == src_conv_mat2fts_diff.mp_matrixes)\n");
		return false;
	}
	if (NULL == dst_conv_mat_diff.mp_data){
		int rows = src_conv_mat2fts_diff.m_rows*src_conv_mat2fts_diff.m_cols;
		int cols = src_conv_mat2fts_diff.m_channels;
		dst_conv_mat_diff = matrix(rows, cols, 0.0);
	}

	/* diff_features -> diff_matrix */
	/* (channel,row,col) -> (i,j) */
	/* ���ݺ����ֵ,Ҫ�� f:(i,j) -> (channel,row,col)�Ĺ�ϵ */
	int channel = 0;
	int row = 0;
	int col = 0;
	/* ���¹��̿����Ż� */
	for (int i = 0; i < dst_conv_mat_diff.m_rows; ++i){
		for (int j = 0; j < dst_conv_mat_diff.m_cols; ++j){
			channel = j;
			row = i / src_conv_mat2fts_diff.m_cols;
			col = i - row*src_conv_mat2fts_diff.m_cols;
			dst_conv_mat_diff.mp_data[i*dst_conv_mat_diff.m_cols + j] = \
				src_conv_mat2fts_diff.mp_matrixes[channel].\
				mp_data[row*src_conv_mat2fts_diff.m_cols + col];
		}
	}
	return true;
}

/* reshape for pooling layer */
bool layer::reshape(features& pooling_mask, features& dst_fts){
	if (MAX_POOLING == m_pooling_mode){
		if (0 != m_fts.m_rows%m_pooling_size || 0 != m_fts.m_cols%m_pooling_size){
			return false;
		}
		else{
			pooling_mask.reset(0);
			int rows = m_fts.m_rows / m_pooling_size;
			int cols = m_fts.m_cols / m_pooling_size;
			int max_row = 0;
			int max_col = 0;
			DATA_TYPE max = 0;
			/* todo �˴������Ż� */
			for (int channel = 0; channel < m_fts.m_channels; ++channel){
				for (int i = 0; i < rows; ++i){
					for (int j = 0; j < cols; ++j){
						max = m_fts.mp_matrixes[channel].mp_data\
							[i*m_pooling_size*m_fts.m_cols + j*m_pooling_size];
						max_row = i*m_pooling_size;
						max_col = j*m_pooling_size;
						for (int s = m_pooling_size*i; s < m_pooling_size*(i + 1); ++s){
							for (int t = m_pooling_size*j; t < m_pooling_size*(j + 1); ++t){
								if (max < m_fts.mp_matrixes[channel].mp_data[s*m_fts.m_cols + t]){
									max = m_fts.mp_matrixes[channel].mp_data[s*m_fts.m_cols + t];
									max_row = s;
									max_col = t;
								}
							}/* end t */
						}/* end s */
						pooling_mask.mp_matrixes[channel].\
							mp_data[max_row*pooling_mask.m_cols + max_col] = 1;
						dst_fts.mp_matrixes[channel].mp_data[i*dst_fts.m_cols + j] = max;
					}
				}
			}//end channel
			//dst_fts.show();
			//int xxx = 0;
		}
	}
	else if (AVE_POOLING == m_pooling_mode){
		;/* todo */
	}
	else{
		;/* error*/
	}
}

bool layer::show_shapes(){
	switch (m_layer_mode)
	{
	case POOLING_LAYER:
		std::cout << "POOLING LAYER\n";
		break;
	case CONVOLUTION_LAYER:
		std::cout << "CONVOLUTION_LAYER\n";
		break;
	case FULLCONNECTION_LAYER:
		std::cout << "FULLCONNECTION_LAYER\n";
		break;
	default:
		break;
	}
	std::cout << "features parameters" << std::endl;
	std::cout << "channels:" << (m_fts).m_channels << "  ";
	std::cout << "rows:" << (m_fts).m_rows << "  ";
	std::cout << "cols:" << (m_fts).m_cols << "  " << std::endl;
	std::cout << "kernels parameters" << std::endl;
	std::cout << "channels:" << (m_kers).m_channels << "  ";
	std::cout << "kernel_rows:" << (m_kers).m_rows << "  ";
	std::cout << "kernel_cols:" << (m_kers).m_cols << "  ";
	std::cout << "kernel_counts:" << (m_kers).m_kers_counts << "  " << std::endl;
	switch (m_relu)
	{
	case RELU_OFF:
		std::cout << "RELU_OFF" << std::endl;
		break;
	case RELU_ON:
		std::cout << "RELU_ON" << std::endl;
		break;
	default:
		break;
	}

	std::cout << "POOLING SIZE:" << m_pooling_size << std::endl;
	return true;
}

bool layer::show(){
	show_shapes();
	switch (m_layer_mode)
	{
	case FULLCONNECTION_LAYER:
	case CONVOLUTION_LAYER:
		m_kers.show();
		break;
	default:
		break;
	}
	return true;
}

bool layer::transposition(const matrix& src, matrix& dst){
	if (NULL == src.mp_data || src.m_rows <= 0 || src.m_cols <= 0){
		DEBUG_PRINT("ERROR\n");
		return false;
	}
	if (NULL == dst.mp_data || 0 >= dst.mp_data || 0 >= dst.mp_data){
		return false;
	}

	if (src.m_rows == dst.m_cols&&src.m_cols == dst.m_rows){
		for (int i = 0; i < src.m_rows; ++i){
			for (int j = 0; j < src.m_cols; ++j){
				dst.mp_data[j*dst.m_cols + i] = src.mp_data[i*src.m_cols + j];
			}
		}
		return true;
	}
	else{
		return false;
	}
}

bool layer::hadamard_product(matrix& src, matrix& mask, matrix& dst){
	if (NULL == src.mp_data || NULL == mask.mp_data || NULL == dst.mp_data){
		DEBUG_PRINT("(NULL == src.mp_data || NULL == mask.mp_data || NULL == dst.mp_data)\
					layer::hadamard_product\n");
		return false;
	}
	if (src.m_rows == mask.m_rows&&src.m_rows == dst.m_rows&&\
		src.m_cols == mask.m_cols&&src.m_cols == dst.m_cols){

		/* todo check ���� */
		int k = 0;
		for (int i = 0; i < src.m_rows; ++i){
			for (int j = 0; j < src.m_cols; ++j){
				dst.mp_data[k] = src.mp_data[k] * mask.mp_data[k];
				++k;
			}
		}
		return true;
	}
	//int xxx = 0;
	//src.show();
	//mask.show();
	//dst.show();
	return false;
}