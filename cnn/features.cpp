#include "features.h"

features::features(){
	m_features_matrix = matrix();
	m_tensor = tensor();
}

features::features(int feature_channels, int features_rows, int features_cols, int val):\
tensor(feature_channels, features_rows, features_cols, val){
	m_features_matrix = matrix();
	m_tensor = tensor();
}

features::features(const cv::Mat &image, DATA_TYPE translation, DATA_TYPE scale)
	     :tensor(image, translation, scale){
	m_features_matrix = matrix();
	m_tensor = tensor();
}

features::features(int feature_channels, int features_rows, int features_cols, DATA_TYPE min, DATA_TYPE max) : \
tensor(feature_channels, features_rows, features_cols, min, max)
{
	m_features_matrix = matrix();
	m_tensor = tensor();
	return;
}

features::features(int feature_channels, int features_rows, int features_cols, int min, int max) : \
tensor(feature_channels, features_rows, features_cols, min, max)
{
	m_features_matrix = matrix();
	m_tensor = tensor();
	return;
}


features::~features(){
	;
}

//virtual bool reshape(int kernels_width = KERNEL_ROW, int kernels_height = KERNEL_COL, \
//	int stride = 1, int padding_mode = VALID_PADDING);
bool features::reshape(int reshape_mode, int kernels_rows,int kernels_cols, int stride, int padding_mode){
	if (0 >= kernels_rows || 0 >= kernels_cols){
		DEBUG_PRINT("(0 >= kernel_rows || 0 >= kernel_cols) \n features::reshape \n");
		return false;
	}
	if (0 >= stride){
		DEBUG_PRINT("(0 >= stride) \n features::reshape \n");
		return false;
	}

	m_tensor = tensor(m_channels, m_rows, m_cols);
	m_kernel_rows = kernels_rows;
	m_kernel_cols = kernels_cols;
	m_stride = stride;
	m_padding_mode = padding_mode;

	if (MATRIX2FEATURES == reshape_mode){

		/* 此处是核心代码 */
		/* 将feature_matrix回归到原始的的features */
		/* 就是要学习这样的一个映射关系f, */
		/*s.t. f: features_matrix(i,j)->features(channel,row,col) */
		int channel = 0;/* channel 是features_matrix第(i,j)个pixel 在原始特征图中的通道数 */
		int rpf = 0;/* rpf 是features_matrix第(i,j)个pixel 在原始特征图中的行数 */
		int cpf = 0;/* cpf 是features_matrix第(i,j)个pixel 在原始特征图中的列数 */

		int rpk = 0;/*rpk 是features_matrix第(i,j)个pixel 在卷积核(二维)中的行数 */
		int cpk = 0;/*cpk 是features_matrix第(i,j)个pixel 在卷积核(二维)中的列数 */

		/*rkf 是features_matrix第(i,j)个pixel 在二维卷积核(左上方元素)在特征中的行数 */
		int rkf = 0;
		/*ckf 是features_matrix第(i,j)个pixel 在二维卷积核(左上方元素)在特征中的列数 */
		int ckf = 0;

		/* 我们学习的并不是 f:(i,j) -> (channel,rpf,cpf)的直接映射关系
		(channel,rpf,cpf)=(channel_in_features,row_pixel_feature,col_pixel_feature) */

		/* 实际上我们寻找到两个映射关系 g和h  s.t. f=h*g */
		/* 第一个是 g:(i,j)->(c,rpk,cpk,rkf,ckf)的映射关系,(c,rpk,cpk,rkf,ckf):=
		(channel,row_pixel_ker,col_pixel_ker,row_ker_feature,col_ker_feature) */
		/* 第二个是 h:(channel,rpk,cpk,rkf,ckf)-> (channel,rpf,cpf) */
		/* (channel,rpf,cpf):=(c,row_pixel_feature,col_pixel_feature)*/

		/* f=h*g的一个复合函数关系 */

		/* index_in_kernel辅助变量，描述元素相对于单个(二维)卷积核的相对位置）*/
		int index_in_kernel = 0;

		switch (padding_mode)
		{
		case VALID_PADDING:
			for (int i = 0; i < m_features_matrix.m_rows; ++i){
				for (int j = 0; j < m_features_matrix.m_cols; ++j){
					/* g: (i,j) -> (channel,rpk,cpk,rkf,ckf) */
					channel = j / (m_kernel_rows*m_kernel_cols);/* 此处乘法可以优化 */
					index_in_kernel = j - channel*m_kernel_rows*m_kernel_cols;
					rpk = index_in_kernel / m_kernel_cols;
					cpk = index_in_kernel - rpk*m_kernel_cols;
					rkf = i / (  (mp_matrixes[0].m_cols - m_kernel_cols) / stride + 1  );
					ckf = i - rkf*( (mp_matrixes[0].m_cols - m_kernel_cols) / stride + 1 );

					/* h: (channel,rpk,cpk,rkf,ckf) -> (channel,rpf,cpf) */
					//channel = channel;
					rpf = rpk + rkf;
					cpf = cpk + ckf;
					int tmp = m_tensor.mp_matrixes[channel].mp_data[rpf*mp_matrixes[0].m_cols + cpf]\
						= m_features_matrix.mp_data[i*m_features_matrix.m_cols + j];
					std::cout << tmp << "  ";
				}
			}
			break;
		case SAME_PADDING:
			/*todo*/
			break;
		//default:
		//	break;
		}
	}

	if (FEATURES2MATRIX == reshape_mode){


		/* 以下三个变量来确定卷积左上方元素的在kernel中的位置 */
		int channel = 0;/* 即channel_in_features, channel代表第几个卷积核(特征) */
		int rpk = 0;     /* row代表元素相对于卷积核(二维)左上方元素的行数 和kernels(4 dims)kernel(3 dims)定义的不一致)*/
		int cpk = 0;    /*  解释同上 col代表元素相对于卷积核左上方元素的列数 */
		/* 以上三个变量来确定单个卷积核左上方元素的在kernel中的位置 */
		
		/* index_in_kernels辅助变量，描述元素相对于单个卷积核的相对位置（一维）*/
		int index_in_kernel = 0;
		/* 以下两个变量来确定卷积核左上角元素相对于单个特征的位置 */
		int rkf = 0;
		int ckf = 0;
		/* 仿照牛顿力学中的相对位置，即坐标转换，\
		   能够确定features_matrix元素对应的在原始features中的绝对位置 */

		int rpf = 0;
		int cpf = 0;
		switch (padding_mode){
			/* features2matrix */
		case VALID_PADDING: /* (N+2P-K)/S +1 */
			m_features_matrix = matrix(((m_rows - m_kernel_rows) / stride + 1)* \
				((m_cols - m_kernel_cols) / stride + 1), \
				m_kernel_rows*m_kernel_cols*m_channels);
			/* 下面是核心代码 features2matrix */
			/* todo 此处计算可以优化 */
			for (int i = 0; i < m_features_matrix.m_rows; ++i){
				for (int j = 0; j < m_features_matrix.m_cols; ++j){
					/* (i,j) -> (channel,rpk,cpk,rkf,ckf) */
					channel = j / (m_kernel_rows*m_kernel_cols);
					index_in_kernel = j - channel*m_kernel_rows*m_kernel_cols;
					rpk = index_in_kernel / m_kernel_cols;
					cpk = index_in_kernel - rpk*m_kernel_cols;
					rkf = i / ((m_cols - m_kernel_cols) / stride + 1);
					ckf = i - rkf*((m_cols - m_kernel_cols) / stride + 1);

					/* (channel,rpk,cpk,rkf,ckf) -> (rpf,cpf)*/
					//channel=channel;
					/* A相对于C的位移 = A相对于B的位移 + B相对于C的位移 */
					rpf = rpk + rkf;/* 元素在原始特征中的行(列)数 = 元素在卷积核中的行(列)数 + 卷积核在特征中的(行列)数 */
					cpf = cpk + ckf;/* 此处的卷积核特指二维卷积核 */
					/* 元素在卷积核中的位置是指元素相对于卷积核左上方元素而言 */
					/* 卷积核在特征图中的位置是指卷积核左上方元素相对于特征图左上方元素的位置 */
					m_features_matrix.mp_data[i*m_features_matrix.m_cols + j] = \
						mp_matrixes[channel].mp_data\
						[rpf*m_cols + cpf];

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

	DEBUG_PRINT("do nothing \n features::reshape \n");
	return false;
}

features::features(features &fs_){
	m_channels = fs_.m_channels;
	m_rows = fs_.m_rows;
	m_cols = fs_.m_cols;
	if (NULL != mp_matrixes){
		delete[] mp_matrixes;
		mp_matrixes = NULL;
	}
	mp_matrixes = new matrix[m_channels];
	if (NULL == mp_matrixes){
		DEBUG_PRINT("(NULL == mp_matrixes) \n features::features(features &fs_)");
		return;
	}
	for (int i = 0; i < m_channels; ++i){
		mp_matrixes[i] = fs_.mp_matrixes[i];
	}
	m_features_matrix = fs_.m_features_matrix;
	m_kernel_rows = fs_.m_kernel_rows;
	m_kernel_cols = fs_.m_kernel_cols;
	m_stride = fs_.m_stride;
	m_padding_mode = fs_.m_padding_mode;
	m_tensor = fs_.m_tensor;
}

features& features::operator=(const features& fs_){
	if (&fs_ == this){
		return *this;
	}
	m_channels = fs_.m_channels;
	m_rows = fs_.m_rows;
	m_cols = fs_.m_cols;
	if (NULL != mp_matrixes){
		delete[] mp_matrixes;
		mp_matrixes = NULL;
	}
	mp_matrixes = new matrix[m_channels];
	if (NULL == mp_matrixes){
		DEBUG_PRINT("(NULL == mp_matrixes) \n features& \
					features::operator=(const features& fs_");
		/* todo */
		return *this;
	}
	for (int i = 0; i < m_channels; ++i){
		mp_matrixes[i] = fs_.mp_matrixes[i];
	}
	m_features_matrix = fs_.m_features_matrix;
	m_kernel_rows = fs_.m_kernel_rows;
	m_kernel_cols = fs_.m_kernel_cols;
	m_stride = fs_.m_stride;
	m_padding_mode = fs_.m_padding_mode;
	m_tensor = fs_.m_tensor;

	return *this;
}