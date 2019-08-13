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
////		/* 此处是核心代码 */
////		/* 将 feature_matrix 回归到原始的的 features */
////		/* 就是要学习这样的一个映射关系f-1, */
////		/*s.t. f-1: (channel,rpf,cpf) -> (i,j) */
////		/* 这是一个后向插值的过程 可以减轻很多计算量 ，相比于下面被注释的前向插值而言 */
////		int channel = 0;/* channel 表示元素所在特征图中的的几个通道 */
////		int rpf = 0;/* rpf 是第channel个feature 元素所在行数 */
////		int cpf = 0;/* rpf 是第channel个feature 元素所在列数 */
////		int rpk = 0;/*rpk 是features中(channel,rpf,cpf)个元素在卷积核(二维)中的行数 */
////		int cpk = 0;/*cpk 是features中(channel,rpf,cpf)个元素在卷积核(二维)中的列数 */
////
////		/*rkf 是features第(channel,rpf,cpf)个pixel 在二维卷积核(左上方元素)在特征中的行数 */
////		int rkf = 0;
////		/*ckf 是features第(channel,rpf,cpf)个pixel 在二维卷积核(左上方元素)在特征中的列数 */
////		int ckf = 0;
////		/* index_in_kernel辅助变量，描述元素相对于单个(二维)卷积核的相对位置）*/
////		int index_in_kernel = 0;
////		switch (padding_mode)
////		{
////		case VALID_PADDING:
////			/* (i,j) (g)-> (channel,rpk,cpk,rkf,ckf) (h)-> (channel,rpf,cpf) */
////			/* (i,j) (f)-> (channel,rpf,cpf)  是一个不可逆过程 */
////			/* 所以  (channel,rpf,cpf) (f-1)-> (i,j)  的f-1实际上是一个多射过程 */
////			/* 具体的怎么把这一段代码写出来还需要思考 */
////			/* todo */
////			//for (channel = 0; channel < m_tensor.m_channels; ++channel){
////			//	for (rpf = 0; rpf < m_tensor.m_rows; ++rpf){
////			//		for (cpf = 0; cpf < m_tensor.m_cols; ++cpf){
////
////			//		}
////			//	}
////			//}
////
////			/* 以下代码虽然正确，但是features中很多元素被重复被计算了K*K次严重浪费计算资源 */
////			for (int i = 0; i < m_features_matrix.m_rows; ++i){
////				for (int j = 0; j < m_features_matrix.m_cols; ++j){
////					/* g: (i,j) -> (channel,rpk,cpk,rkf,ckf) */
////					channel = j / (m_kernel_rows*m_kernel_cols);/* 此处乘法可以优化 */
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
////			/* 留这一段代码的原因是以后参考和注意，要注意正向计算和反向计算的区别 */
////			/* 这就好比前向插值和反向插值的区别 */
////			/* 以上代码虽然正确，但是features中很多元素被重复被计算了K*K次严重浪费计算资源 */
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
////		/* 此处是核心代码 */
////		/* 将G: features -> matrix */
////		/* 我们要学习这样的一个映射关系f  这是一个逆向的过程 */
////		/* s.t. f: matrix中的第(i,j)pixel ->  features中第(channel,row,col)个元素 */
////		/* 简化即是 f: (i,j) -> (channel,rpf,cpf) *******************************
////		******(channel,rpf,cpf) = (channel,row_pixel_feature,col_pixel_feature): */
////		/* 关于 rpf cpf 的定义如下 */
////		int channel = 0;/* channel channel_in_features 是features_matrix第(i,j)个pixel 在原始特征图中的通道数 */
////		int rpf = 0;    /* rpf row_pixel_feature 是features_matrix第(i,j)个pixel 在原始特征图中的行数 */
////		int cpf = 0;    /* cpf col_pixel_feature 是features_matrix第(i,j)个pixel 在原始特征图中的列数 */
////
////		int rpk = 0;/*rpk 是features_matrix第(i,j)个pixel 在卷积核(二维)中的行数 */
////		int cpk = 0;/*cpk 是features_matrix第(i,j)个pixel 在卷积核(二维)中的列数 */
////		/*rkf 是features_matrix第(i,j)个pixel 在二维卷积核(左上方元素)在特征中的行数 */
////		int rkf = 0;
////		/*ckf 是features_matrix第(i,j)个pixel 在二维卷积核(左上方元素)在特征中的列数 */
////		int ckf = 0;
////		/* 我们学习的并不是直接得到 f: (i,j) -> (channel,rpf,cpf) 的映射关系 */
////		/* 实际上我们寻找到两个映射关系 g和h,  s.t. f=h*g 这样的一个复合函数的关系 */
////		/* 第一个是 g: (i,j)->(c,rpk,cpk,rkf,ckf)的映射关系,
////		/* 第二个是 h:(channel,rpk,cpk,rkf,ckf)-> (channel,rpf,cpf) */
////		/* f=h*g的一个复合函数关系 */
////
////		/* index_in_kernels辅助变量，描述元素相对于单个卷积核的相对位置（一维）*/
////		int index_in_kernel = 0;
////		/* 仿照牛顿力学中的相对位置，即坐标转换，\
////		   能够确定features_matrix元素对应的在原始features中的绝对位置 */
////		/* 简而言之，就是 A相对于C的位移 = A相对于B的位移 + B相对于C的位移 */
////		switch (padding_mode){
////			/* features2matrix */
////		case VALID_PADDING: /* (N+2P-K)/S +1 */
////			m_features_matrix = matrix(((m_rows - m_kernel_rows) / stride + 1)* \
////				((m_cols - m_kernel_cols) / stride + 1), \
////				m_kernel_rows*m_kernel_cols*m_channels);
////			/* 下面是核心代码 features2matrix */
////			/* todo 此处计算可以优化 */
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
////					/* A相对于C的位移 = A相对于B的位移 + B相对于C的位移 */
////					rpf = rpk + rkf;/* 元素在原始特征中的行(列)数 = 元素在卷积核中的行(列)数 + 卷积核在特征中的(行列)数 */
////					cpf = cpk + ckf;/* 此处的卷积核特指二维卷积核 */
////					/* 元素在卷积核中的位置是指元素相对于卷积核左上方元素而言 */
////					/* 卷积核在特征图中的位置是指卷积核左上方元素相对于特征图左上方元素的位置 */
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
////		/* fts是输入  fts_matrix是输出 */
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
////		/* 此处是核心代码 */
////		/* 将G: features -> matrix */
////		/* 我们要学习这样的一个映射关系f  这是一个后向插值的过程 */
////		/* s.t. f: matrix中的第(i,j)pixel ->  features中第(channel,row,col)个元素 */
////		/* 简化即是 f: (i,j) -> (channel,rpf,cpf) *******************************
////		******(channel,rpf,cpf) = (channel,row_pixel_feature,col_pixel_feature): */
////		/* 关于 rpf cpf 的定义如下 */
////		int channel = 0;/* channel channel_in_features 是features_matrix第(i,j)个pixel 在原始特征图中的通道数 */
////		int rpf = 0;    /* rpf row_pixel_feature 是features_matrix第(i,j)个pixel 在原始特征图中的行数 */
////		int cpf = 0;    /* cpf col_pixel_feature 是features_matrix第(i,j)个pixel 在原始特征图中的列数 */
////
////		int rpk = 0;/*rpk 是features_matrix第(i,j)个pixel 在卷积核(二维)中的行数 */
////		int cpk = 0;/*cpk 是features_matrix第(i,j)个pixel 在卷积核(二维)中的列数 */
////		/*rkf 是features_matrix第(i,j)个pixel 在二维卷积核(左上方元素)在特征中的行数 */
////		int rkf = 0;
////		/*ckf 是features_matrix第(i,j)个pixel 在二维卷积核(左上方元素)在特征中的列数 */
////		int ckf = 0;
////		/* 我们学习的并不是直接得到 f: (i,j) -> (channel,rpf,cpf) 的映射关系 */
////		/* 实际上我们寻找到两个映射关系 g和h,  s.t. f=h*g 这样的一个复合函数的关系 */
////		/* 第一个是 g: (i,j)->(c,rpk,cpk,rkf,ckf)的映射关系,
////		/* 第二个是 h:(channel,rpk,cpk,rkf,ckf)-> (channel,rpf,cpf) */
////		/* f=h*g的一个复合函数关系 */
////
////		/* index_in_kernels辅助变量，描述元素相对于单个(二维)卷积核的相对位置（一维）*/
////		int index_in_kernel = 0;
////		/* 仿照牛顿力学中的相对位置，即坐标转换，\
////		能够确定features_matrix元素对应的在原始features中的绝对位置 */
////		/* 简而言之，就是 A相对于C的位移 = A相对于B的位移 + B相对于C的位移 */
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
////			/* 下面是核心代码 features2matrix */
////			/* todo 此处计算可以优化 */
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
////					/* A相对于C的位移 = A相对于B的位移 + B相对于C的位移 */
////					rpf = rpk + rkf;/* 元素在原始特征中的行(列)数 = 元素在卷积核中的行(列)数 + 卷积核在特征中的(行列)数 */
////					cpf = cpk + ckf;/* 此处的卷积核特指二维卷积核 */
////					/* 元素在卷积核中的位置是指元素相对于卷积核左上方元素而言 */
////					/* 卷积核在特征图中的位置是指卷积核左上方元素相对于特征图左上方元素的位置 */
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
////		/* 此处是核心代码 */
////		/* 将 feature_matrix(i,j) 回归到原始的的 features(channel,rpf,cpf) */
////		/* 就是要学习这样的一个映射关系f-1, */
////		/*s.t. f-1: (channel,rpf,cpf) -> (i,j) */
////		/* 这是一个后向插值的过程 可以减轻很多计算量 ，相比于下面被注释的前向插值而言 */
////		int channel = 0;/* channel 表示元素所在特征图中的的几个通道 */
////		int rpf = 0;/* rpf 是第channel个feature 元素所在行数 */
////		int cpf = 0;/* rpf 是第channel个feature 元素所在列数 */
////		int rpk = 0;/*rpk 是features中(channel,rpf,cpf)个元素在卷积核(二维)中的行数 */
////		int cpk = 0;/*cpk 是features中(channel,rpf,cpf)个元素在卷积核(二维)中的列数 */
////
////		/*rkf 是features第(channel,rpf,cpf)个pixel 在二维卷积核(左上方元素)在特征中的行数 */
////		int rkf = 0;
////		/*ckf 是features第(channel,rpf,cpf)个pixel 在二维卷积核(左上方元素)在特征中的列数 */
////		int ckf = 0;
////		/* index_in_kernel辅助变量，描述元素相对于单个(二维)卷积核的相对位置）*/
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
////		/* fts_matrix是输入  fts是输出 */
////		fts_matrix.show(SHOW_IMAGE_INITAIL_VALUE);
////		switch (padding_mode)
////		{
////		case VALID_PADDING:
////			/* (i,j) (g)-> (channel,rpk,cpk,rkf,ckf) (h)-> (channel,rpf,cpf) */
////			/* (i,j) (f)-> (channel,rpf,cpf)  是一个不可逆过程 */
////			/* 所以  (channel,rpf,cpf) (f-1)-> (i,j)  的f-1实际上是一个多射过程 */
////			/* 具体的怎么把这一段代码写出来还需要思考 */
////			/* todo */
////			//for (channel = 0; channel < m_tensor.m_channels; ++channel){
////			//	for (rpf = 0; rpf < m_tensor.m_rows; ++rpf){
////			//		for (cpf = 0; cpf < m_tensor.m_cols; ++cpf){}}}
////
////			/* 以下代码虽然正确，但是features中很多元素被重复被计算了K*K次严重浪费计算资源 */
////			for (int i = 0; i < fts_matrix.m_rows; ++i){
////				for (int j = 0; j < fts_matrix.m_cols; ++j){
////					/* g: (i,j) -> (channel,rpk,cpk,rkf,ckf) */
////					channel = j / (kernel_rows*kernel_cols);/* 此处乘法可以优化 */
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
////			/* 留这一段代码的原因是以后参考和注意，要注意正向计算和反向计算的区别 */
////			/* 这就好比前向插值和反向插值的区别 */
////			/* 以上代码虽然正确，但是features中很多元素被重复被计算了K*K次严重浪费计算资源 todo */
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