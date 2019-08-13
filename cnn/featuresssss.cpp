//#include "featuresssss.h"
//#include "matrix.h"
//featuresssss::featuresssss(){
//	m_features_matrix = matrix();
//	m_tensor = features();
//}
//
//featuresssss::featuresssss(int feature_channels, int features_rows, int features_cols, int val):\
//features(feature_channels, features_rows, features_cols, val){
//	m_features_matrix = matrix();
//	m_tensor = features();
//}
//
//featuresssss::featuresssss(int feature_channels, int features_rows, int features_cols, DATA_TYPE val):
//features(feature_channels, features_rows, features_cols, val){
//	m_features_matrix = matrix();
//	m_tensor = features();
//}
//featuresssss::featuresssss(const cv::Mat &image, DATA_TYPE translation, DATA_TYPE scale)
//	     :features(image, translation, scale){
//	m_features_matrix = matrix();
//	m_tensor = features();
//}
//
//featuresssss::featuresssss(int feature_channels, int features_rows, int features_cols, DATA_TYPE min, DATA_TYPE max) : \
//features(feature_channels, features_rows, features_cols, min, max)
//{
//	m_features_matrix = matrix();
//	m_tensor = features();
//	return;
//}
//
//featuresssss::featuresssss(int feature_channels, int features_rows, int features_cols, int min, int max) : \
//features(feature_channels, features_rows, features_cols, min, max)
//{
//	m_features_matrix = matrix();
//	m_tensor = features();
//	return;
//}
//
//
//featuresssss::~featuresssss(){
//	;
//}
//
////virtual bool reshape(int kernels_width = KERNEL_ROW, int kernels_height = KERNEL_COL, \
////	int stride = 1, int padding_mode = VALID_PADDING);
////bool features::reshape(int reshape_mode, int kernels_rows,int kernels_cols, int stride, int padding_mode){
////	if (0 >= kernels_rows || 0 >= kernels_cols){
////		DEBUG_PRINT("(0 >= kernel_rows || 0 >= kernel_cols) \n features::reshape \n");
////		return false;
////	}
////	if (0 >= stride){
////		DEBUG_PRINT("(0 >= stride) \n features::reshape \n");
////		return false;
////	}
////
////	m_tensor = tensor(m_channels, m_rows, m_cols);
////	m_kernel_rows = kernels_rows;
////	m_kernel_cols = kernels_cols;
////	m_stride = stride;
////	m_padding_mode = padding_mode;
////
////	if (MATRIX2FEATURES == reshape_mode){
////
////		/* �˴��Ǻ��Ĵ��� */
////		/* �� feature_matrix �ع鵽ԭʼ�ĵ� features */
////		/* ����Ҫѧϰ������һ��ӳ���ϵf-1, */
////		/*s.t. f-1: (channel,rpf,cpf) -> (i,j) */
////		/* ����һ�������ֵ�Ĺ��� ���Լ���ܶ������ ����������汻ע�͵�ǰ���ֵ���� */
////		int channel = 0;/* channel ��ʾԪ����������ͼ�еĵļ���ͨ�� */
////		int rpf = 0;/* rpf �ǵ�channel��feature Ԫ���������� */
////		int cpf = 0;/* rpf �ǵ�channel��feature Ԫ���������� */
////		int rpk = 0;/*rpk ��features��(channel,rpf,cpf)��Ԫ���ھ����(��ά)�е����� */
////		int cpk = 0;/*cpk ��features��(channel,rpf,cpf)��Ԫ���ھ����(��ά)�е����� */
////
////		/*rkf ��features��(channel,rpf,cpf)��pixel �ڶ�ά�����(���Ϸ�Ԫ��)�������е����� */
////		int rkf = 0;
////		/*ckf ��features��(channel,rpf,cpf)��pixel �ڶ�ά�����(���Ϸ�Ԫ��)�������е����� */
////		int ckf = 0;
////		/* index_in_kernel��������������Ԫ������ڵ���(��ά)����˵����λ�ã�*/
////		int index_in_kernel = 0;
////		switch (padding_mode)
////		{
////		case VALID_PADDING:
////			/* (i,j) (g)-> (channel,rpk,cpk,rkf,ckf) (h)-> (channel,rpf,cpf) */
////			/* (i,j) (f)-> (channel,rpf,cpf)  ��һ����������� */
////			/* ����  (channel,rpf,cpf) (f-1)-> (i,j)  ��f-1ʵ������һ��������� */
////			/* �������ô����һ�δ���д��������Ҫ˼�� */
////			/* todo */
////			//for (channel = 0; channel < m_tensor.m_channels; ++channel){
////			//	for (rpf = 0; rpf < m_tensor.m_rows; ++rpf){
////			//		for (cpf = 0; cpf < m_tensor.m_cols; ++cpf){
////
////			//		}
////			//	}
////			//}
////
////			/* ���´�����Ȼ��ȷ������features�кܶ�Ԫ�ر��ظ���������K*K�������˷Ѽ�����Դ */
////			for (int i = 0; i < m_features_matrix.m_rows; ++i){
////				for (int j = 0; j < m_features_matrix.m_cols; ++j){
////					/* g: (i,j) -> (channel,rpk,cpk,rkf,ckf) */
////					channel = j / (m_kernel_rows*m_kernel_cols);/* �˴��˷������Ż� */
////					index_in_kernel = j - channel*m_kernel_rows*m_kernel_cols;
////					rpk = index_in_kernel / m_kernel_cols;
////					cpk = index_in_kernel - rpk*m_kernel_cols;
////					rkf = i / (  (mp_matrixes[0].m_cols - m_kernel_cols) / stride + 1  );
////					ckf = i - rkf*( (mp_matrixes[0].m_cols - m_kernel_cols) / stride + 1 );
////
////					/* h: (channel,rpk,cpk,rkf,ckf) -> (channel,rpf,cpf) */
////					//channel = channel;
////					rpf = rpk + rkf;
////					cpf = cpk + ckf;
////					m_tensor.mp_matrixes[channel].mp_data[rpf*mp_matrixes[0].m_cols + cpf]\
////						= m_features_matrix.mp_data[i*m_features_matrix.m_cols + j];
////					
////				}
////			}
////			/* ����һ�δ����ԭ�����Ժ�ο���ע�⣬Ҫע���������ͷ����������� */
////			/* ��ͺñ�ǰ���ֵ�ͷ����ֵ������ */
////			/* ���ϴ�����Ȼ��ȷ������features�кܶ�Ԫ�ر��ظ���������K*K�������˷Ѽ�����Դ */
////			break;
////		case SAME_PADDING:
////			/*todo*/
////			break;
////		//default:
////		//	break;
////		}
////	}
////
////	if (FEATURES2MATRIX == reshape_mode){
////
////		/* �˴��Ǻ��Ĵ��� */
////		/* ��G: features -> matrix */
////		/* ����Ҫѧϰ������һ��ӳ���ϵf  ����һ������Ĺ��� */
////		/* s.t. f: matrix�еĵ�(i,j)pixel ->  features�е�(channel,row,col)��Ԫ�� */
////		/* �򻯼��� f: (i,j) -> (channel,rpf,cpf) *******************************
////		******(channel,rpf,cpf) = (channel,row_pixel_feature,col_pixel_feature): */
////		/* ���� rpf cpf �Ķ������� */
////		int channel = 0;/* channel channel_in_features ��features_matrix��(i,j)��pixel ��ԭʼ����ͼ�е�ͨ���� */
////		int rpf = 0;    /* rpf row_pixel_feature ��features_matrix��(i,j)��pixel ��ԭʼ����ͼ�е����� */
////		int cpf = 0;    /* cpf col_pixel_feature ��features_matrix��(i,j)��pixel ��ԭʼ����ͼ�е����� */
////
////		int rpk = 0;/*rpk ��features_matrix��(i,j)��pixel �ھ����(��ά)�е����� */
////		int cpk = 0;/*cpk ��features_matrix��(i,j)��pixel �ھ����(��ά)�е����� */
////		/*rkf ��features_matrix��(i,j)��pixel �ڶ�ά�����(���Ϸ�Ԫ��)�������е����� */
////		int rkf = 0;
////		/*ckf ��features_matrix��(i,j)��pixel �ڶ�ά�����(���Ϸ�Ԫ��)�������е����� */
////		int ckf = 0;
////		/* ����ѧϰ�Ĳ�����ֱ�ӵõ� f: (i,j) -> (channel,rpf,cpf) ��ӳ���ϵ */
////		/* ʵ��������Ѱ�ҵ�����ӳ���ϵ g��h,  s.t. f=h*g ������һ�����Ϻ����Ĺ�ϵ */
////		/* ��һ���� g: (i,j)->(c,rpk,cpk,rkf,ckf)��ӳ���ϵ,
////		/* �ڶ����� h:(channel,rpk,cpk,rkf,ckf)-> (channel,rpf,cpf) */
////		/* f=h*g��һ�����Ϻ�����ϵ */
////
////		/* index_in_kernels��������������Ԫ������ڵ�������˵����λ�ã�һά��*/
////		int index_in_kernel = 0;
////		/* ����ţ����ѧ�е����λ�ã�������ת����\
////		   �ܹ�ȷ��features_matrixԪ�ض�Ӧ����ԭʼfeatures�еľ���λ�� */
////		/* �����֮������ A�����C��λ�� = A�����B��λ�� + B�����C��λ�� */
////		switch (padding_mode){
////			/* features2matrix */
////		case VALID_PADDING: /* (N+2P-K)/S +1 */
////			m_features_matrix = matrix(((m_rows - m_kernel_rows) / stride + 1)* \
////				((m_cols - m_kernel_cols) / stride + 1), \
////				m_kernel_rows*m_kernel_cols*m_channels);
////			/* �����Ǻ��Ĵ��� features2matrix */
////			/* todo �˴���������Ż� */
////			for (int i = 0; i < m_features_matrix.m_rows; ++i){
////				for (int j = 0; j < m_features_matrix.m_cols; ++j){
////					/* (i,j) -> (channel,rpk,cpk,rkf,ckf) */
////					channel = j / (m_kernel_rows*m_kernel_cols);
////					index_in_kernel = j - channel*m_kernel_rows*m_kernel_cols;
////					rpk = index_in_kernel / m_kernel_cols;
////					cpk = index_in_kernel - rpk*m_kernel_cols;
////					rkf = i / ((m_cols - m_kernel_cols) / stride + 1);
////					ckf = i - rkf*((m_cols - m_kernel_cols) / stride + 1);
////
////					/* (channel,rpk,cpk,rkf,ckf) -> (channel,rpf,cpf)*/
////					//channel=channel;
////					/* A�����C��λ�� = A�����B��λ�� + B�����C��λ�� */
////					rpf = rpk + rkf;/* Ԫ����ԭʼ�����е���(��)�� = Ԫ���ھ�����е���(��)�� + ������������е�(����)�� */
////					cpf = cpk + ckf;/* �˴��ľ������ָ��ά����� */
////					/* Ԫ���ھ�����е�λ����ָԪ������ھ�������Ϸ�Ԫ�ض��� */
////					/* �����������ͼ�е�λ����ָ��������Ϸ�Ԫ�����������ͼ���Ϸ�Ԫ�ص�λ�� */
////					m_features_matrix.mp_data[i*m_features_matrix.m_cols + j] = \
////						mp_matrixes[channel].mp_data\
////						[rpf*m_cols + cpf];
////
////				}
////			}
////			break;
////		case SAME_PADDING:
////			//todo
////			break;
////		default:
////			break;
////		}
////		return true;
////	}
////
////	DEBUG_PRINT("do nothing \n features::reshape \n");
////	return false;
////}
//
////bool featuresssss::reshape(features& tsr, matrix& fts_matrix, int reshape_mode, int kernel_rows, \
////	int kernel_cols, int stride, int padding_mode){
////	if (0 >= kernel_rows || 0 >= kernel_cols){
////		DEBUG_PRINT("(0 >= kernel_rows || 0 >= kernel_cols) \n features::reshape \n");
////		return false;
////	}
////	if (0 >= stride){
////		DEBUG_PRINT("(0 >= stride) \n features::reshape \n");
////		return false;
////	}
////
////	if (FEATURES2MATRIX == reshape_mode){
////		/* fts������  fts_matrix����� */
////		tsr = features(m_channels, m_rows, m_cols, 0.0);
////		for (int i = 0; i < tsr.m_channels; ++i){
////			tsr.mp_matrixes[i] = mp_matrixes[i];
////		}
////
////		if (NULL == tsr.mp_matrixes){
////			std::cout << "(NULL == mp_matrixes)(FEATURES2MATRIX == reshape_mode)\
////						features::reshape " << std::endl;
////			return false;
////		}
////		/* �˴��Ǻ��Ĵ��� */
////		/* ��G: features -> matrix */
////		/* ����Ҫѧϰ������һ��ӳ���ϵf  ����һ�������ֵ�Ĺ��� */
////		/* s.t. f: matrix�еĵ�(i,j)pixel ->  features�е�(channel,row,col)��Ԫ�� */
////		/* �򻯼��� f: (i,j) -> (channel,rpf,cpf) *******************************
////		******(channel,rpf,cpf) = (channel,row_pixel_feature,col_pixel_feature): */
////		/* ���� rpf cpf �Ķ������� */
////		int channel = 0;/* channel channel_in_features ��features_matrix��(i,j)��pixel ��ԭʼ����ͼ�е�ͨ���� */
////		int rpf = 0;    /* rpf row_pixel_feature ��features_matrix��(i,j)��pixel ��ԭʼ����ͼ�е����� */
////		int cpf = 0;    /* cpf col_pixel_feature ��features_matrix��(i,j)��pixel ��ԭʼ����ͼ�е����� */
////
////		int rpk = 0;/*rpk ��features_matrix��(i,j)��pixel �ھ����(��ά)�е����� */
////		int cpk = 0;/*cpk ��features_matrix��(i,j)��pixel �ھ����(��ά)�е����� */
////		/*rkf ��features_matrix��(i,j)��pixel �ڶ�ά�����(���Ϸ�Ԫ��)�������е����� */
////		int rkf = 0;
////		/*ckf ��features_matrix��(i,j)��pixel �ڶ�ά�����(���Ϸ�Ԫ��)�������е����� */
////		int ckf = 0;
////		/* ����ѧϰ�Ĳ�����ֱ�ӵõ� f: (i,j) -> (channel,rpf,cpf) ��ӳ���ϵ */
////		/* ʵ��������Ѱ�ҵ�����ӳ���ϵ g��h,  s.t. f=h*g ������һ�����Ϻ����Ĺ�ϵ */
////		/* ��һ���� g: (i,j)->(c,rpk,cpk,rkf,ckf)��ӳ���ϵ,
////		/* �ڶ����� h:(channel,rpk,cpk,rkf,ckf)-> (channel,rpf,cpf) */
////		/* f=h*g��һ�����Ϻ�����ϵ */
////
////		/* index_in_kernels��������������Ԫ������ڵ���(��ά)����˵����λ�ã�һά��*/
////		int index_in_kernel = 0;
////		/* ����ţ����ѧ�е����λ�ã�������ת����\
////		�ܹ�ȷ��features_matrixԪ�ض�Ӧ����ԭʼfeatures�еľ���λ�� */
////		/* �����֮������ A�����C��λ�� = A�����B��λ�� + B�����C��λ�� */
////		switch (padding_mode){
////			/* features2matrix */
////		case VALID_PADDING: /* (N+2P-K)/S +1 */
////			fts_matrix = matrix(((tsr.m_rows - kernel_rows) / stride + 1)* \
////				((tsr.m_cols - kernel_cols) / stride + 1), \
////				kernel_rows*kernel_cols*tsr.m_channels);
////			if (NULL == &fts_matrix){
////				std::cout << "(NULL == &m_features_matrix) \n features::reshape\n";
////				return false;
////			}
////			/* �����Ǻ��Ĵ��� features2matrix */
////			/* todo �˴���������Ż� */
////			for (int i = 0; i < fts_matrix.m_rows; ++i){
////				for (int j = 0; j < fts_matrix.m_cols; ++j){
////					/* (i,j) -> (channel,rpk,cpk,rkf,ckf) */
////					channel = j / (kernel_rows*kernel_cols);
////					index_in_kernel = j - channel*kernel_rows*kernel_cols;
////					rpk = index_in_kernel / kernel_cols;
////					cpk = index_in_kernel - rpk*kernel_cols;
////					rkf = i / ( (tsr.m_cols - kernel_cols)/stride + 1 );
////					ckf = i - rkf*( (tsr.m_cols - kernel_cols)/stride + 1 );
////
////					/* (channel,rpk,cpk,rkf,ckf) -> (channel,rpf,cpf)*/
////					//channel=channel;
////					/* A�����C��λ�� = A�����B��λ�� + B�����C��λ�� */
////					rpf = rpk + rkf;/* Ԫ����ԭʼ�����е���(��)�� = Ԫ���ھ�����е���(��)�� + ������������е�(����)�� */
////					cpf = cpk + ckf;/* �˴��ľ������ָ��ά����� */
////					/* Ԫ���ھ�����е�λ����ָԪ������ھ�������Ϸ�Ԫ�ض��� */
////					/* �����������ͼ�е�λ����ָ��������Ϸ�Ԫ�����������ͼ���Ϸ�Ԫ�ص�λ�� */
////					fts_matrix.mp_data[i*fts_matrix.m_cols + j] = \
////						tsr.mp_matrixes[channel].mp_data[rpf*tsr.m_cols + cpf];
////				}
////			}
////			break;
////		case SAME_PADDING:
////			//todo
////			break;
////		default:
////			break;
////		}
////		return true;
////	}
////	else if (MATRIX2FEATURES == reshape_mode){
////
////		/* �˴��Ǻ��Ĵ��� */
////		/* �� feature_matrix(i,j) �ع鵽ԭʼ�ĵ� features(channel,rpf,cpf) */
////		/* ����Ҫѧϰ������һ��ӳ���ϵf-1, */
////		/*s.t. f-1: (channel,rpf,cpf) -> (i,j) */
////		/* ����һ�������ֵ�Ĺ��� ���Լ���ܶ������ ����������汻ע�͵�ǰ���ֵ���� */
////		int channel = 0;/* channel ��ʾԪ����������ͼ�еĵļ���ͨ�� */
////		int rpf = 0;/* rpf �ǵ�channel��feature Ԫ���������� */
////		int cpf = 0;/* rpf �ǵ�channel��feature Ԫ���������� */
////		int rpk = 0;/*rpk ��features��(channel,rpf,cpf)��Ԫ���ھ����(��ά)�е����� */
////		int cpk = 0;/*cpk ��features��(channel,rpf,cpf)��Ԫ���ھ����(��ά)�е����� */
////
////		/*rkf ��features��(channel,rpf,cpf)��pixel �ڶ�ά�����(���Ϸ�Ԫ��)�������е����� */
////		int rkf = 0;
////		/*ckf ��features��(channel,rpf,cpf)��pixel �ڶ�ά�����(���Ϸ�Ԫ��)�������е����� */
////		int ckf = 0;
////		/* index_in_kernel��������������Ԫ������ڵ���(��ά)����˵����λ�ã�*/
////		int index_in_kernel = 0;
////
////		if (NULL == fts_matrix.mp_data){
////			std::cout << "(NULL == fts_matrix.mp_data)" << "(MATRIX2FEATURES == reshape_mode)"
////				<< "features::reshape" << std::endl;
////			return false;
////		}
////
////		//tsr = tensor(m_rows, m_cols, m_channels, 0.0);
////		if (NULL == &tsr){
////			std::cout << "(NULL == &fts)" << "(MATRIX2FEATURES == reshape_mode)"
////				<< "features::reshape" << std::endl;
////		}
////		if (NULL == &fts_matrix || NULL == fts_matrix.mp_data){
////			std::cout << "(NULL == &fts_matrix||NULL==fts_matrix.mp_data)   "
////				<< "(MATRIX2FEATURES == reshape_mode)  " << "features::reshape\n";
////		}
////		/* fts_matrix������  fts����� */
////		fts_matrix.show(SHOW_IMAGE_INITAIL_VALUE);
////		switch (padding_mode)
////		{
////		case VALID_PADDING:
////			/* (i,j) (g)-> (channel,rpk,cpk,rkf,ckf) (h)-> (channel,rpf,cpf) */
////			/* (i,j) (f)-> (channel,rpf,cpf)  ��һ����������� */
////			/* ����  (channel,rpf,cpf) (f-1)-> (i,j)  ��f-1ʵ������һ��������� */
////			/* �������ô����һ�δ���д��������Ҫ˼�� */
////			/* todo */
////			//for (channel = 0; channel < m_tensor.m_channels; ++channel){
////			//	for (rpf = 0; rpf < m_tensor.m_rows; ++rpf){
////			//		for (cpf = 0; cpf < m_tensor.m_cols; ++cpf){}}}
////
////			/* ���´�����Ȼ��ȷ������features�кܶ�Ԫ�ر��ظ���������K*K�������˷Ѽ�����Դ */
////			for (int i = 0; i < fts_matrix.m_rows; ++i){
////				for (int j = 0; j < fts_matrix.m_cols; ++j){
////					/* g: (i,j) -> (channel,rpk,cpk,rkf,ckf) */
////					channel = j / (kernel_rows*kernel_cols);/* �˴��˷������Ż� */
////					index_in_kernel = j - channel*kernel_rows*kernel_cols;
////					rpk = index_in_kernel / kernel_cols;
////					cpk = index_in_kernel - rpk*kernel_cols;
////					rkf = i / ((fts_matrix.m_cols - kernel_cols) / stride + 1);
////					ckf = i - rkf*((fts_matrix.m_cols - kernel_cols) / stride + 1);
////
////					/* h: (channel,rpk,cpk,rkf,ckf) -> (channel,rpf,cpf) */
////					//channel = channel;
////					rpf = rpk + rkf;
////					cpf = cpk + ckf;
////					//tsr.mp_matrixes[channel].mp_data[rpf*mp_matrixes[0].m_cols + cpf]\
////					//	= fts_matrix.mp_data[i*m_features_matrix.m_cols + j];
////					tsr.mp_matrixes[channel].mp_data[rpf*tsr.mp_matrixes[0].m_cols + cpf]\
////						  = fts_matrix.mp_data[i*fts_matrix.m_cols + j];
////				}
////			}
////			/* ����һ�δ����ԭ�����Ժ�ο���ע�⣬Ҫע���������ͷ����������� */
////			/* ��ͺñ�ǰ���ֵ�ͷ����ֵ������ */
////			/* ���ϴ�����Ȼ��ȷ������features�кܶ�Ԫ�ر��ظ���������K*K�������˷Ѽ�����Դ todo */
////			break;
////		case SAME_PADDING:
////			/*todo*/
////			break;
////			//default:
////			//	break;
////		}
////		return true;
////	}
////	else{
////		std::cout << "FEATURES2MATRIX!=reshape_mode && MATRIEX2KERNELS!=reshape_mode\n";
////		return false;
////	}
////}
//
//featuresssss::featuresssss(featuresssss &fs_){
//	m_channels = fs_.m_channels;
//	m_rows = fs_.m_rows;
//	m_cols = fs_.m_cols;
//	if (NULL != mp_matrixes){
//		delete[] mp_matrixes;
//		mp_matrixes = NULL;
//	}
//	mp_matrixes = new matrix[m_channels];
//	if (NULL == mp_matrixes){
//		DEBUG_PRINT("(NULL == mp_matrixes) \n features::features(features &fs_)");
//		return;
//	}
//	for (int i = 0; i < m_channels; ++i){
//		mp_matrixes[i] = fs_.mp_matrixes[i];
//	}
//	m_features_matrix = fs_.m_features_matrix;
//	m_kernel_rows = fs_.m_kernel_rows;
//	m_kernel_cols = fs_.m_kernel_cols;
//	m_stride = fs_.m_stride;
//	m_padding_mode = fs_.m_padding_mode;
//	m_tensor = fs_.m_tensor;
//}
//
//featuresssss& featuresssss::operator=(const featuresssss& fs_){
//	if (&fs_ == this){
//		return *this;
//	}
//	m_channels = fs_.m_channels;
//	m_rows = fs_.m_rows;
//	m_cols = fs_.m_cols;
//	if (NULL != mp_matrixes){
//		delete[] mp_matrixes;
//		mp_matrixes = NULL;
//	}
//	mp_matrixes = new matrix[m_channels];
//	if (NULL == mp_matrixes){
//		DEBUG_PRINT("(NULL == mp_matrixes) \n features& \
//					features::operator=(const features& fs_");
//		/* todo */
//		return *this;
//	}
//	for (int i = 0; i < m_channels; ++i){
//		mp_matrixes[i] = fs_.mp_matrixes[i];
//	}
//	m_features_matrix = fs_.m_features_matrix;
//	m_kernel_rows = fs_.m_kernel_rows;
//	m_kernel_cols = fs_.m_kernel_cols;
//	m_stride = fs_.m_stride;
//	m_padding_mode = fs_.m_padding_mode;
//	m_tensor = fs_.m_tensor;
//
//	return *this;
//}