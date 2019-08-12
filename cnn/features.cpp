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

		/* �˴��Ǻ��Ĵ��� */
		/* ��feature_matrix�ع鵽ԭʼ�ĵ�features */
		/* ����Ҫѧϰ������һ��ӳ���ϵf, */
		/*s.t. f: features_matrix(i,j)->features(channel,row,col) */
		int channel = 0;/* channel ��features_matrix��(i,j)��pixel ��ԭʼ����ͼ�е�ͨ���� */
		int rpf = 0;/* rpf ��features_matrix��(i,j)��pixel ��ԭʼ����ͼ�е����� */
		int cpf = 0;/* cpf ��features_matrix��(i,j)��pixel ��ԭʼ����ͼ�е����� */

		int rpk = 0;/*rpk ��features_matrix��(i,j)��pixel �ھ����(��ά)�е����� */
		int cpk = 0;/*cpk ��features_matrix��(i,j)��pixel �ھ����(��ά)�е����� */

		/*rkf ��features_matrix��(i,j)��pixel �ڶ�ά�����(���Ϸ�Ԫ��)�������е����� */
		int rkf = 0;
		/*ckf ��features_matrix��(i,j)��pixel �ڶ�ά�����(���Ϸ�Ԫ��)�������е����� */
		int ckf = 0;

		/* ����ѧϰ�Ĳ����� f:(i,j) -> (channel,rpf,cpf)��ֱ��ӳ���ϵ
		(channel,rpf,cpf)=(channel_in_features,row_pixel_feature,col_pixel_feature) */

		/* ʵ��������Ѱ�ҵ�����ӳ���ϵ g��h  s.t. f=h*g */
		/* ��һ���� g:(i,j)->(c,rpk,cpk,rkf,ckf)��ӳ���ϵ,(c,rpk,cpk,rkf,ckf):=
		(channel,row_pixel_ker,col_pixel_ker,row_ker_feature,col_ker_feature) */
		/* �ڶ����� h:(channel,rpk,cpk,rkf,ckf)-> (channel,rpf,cpf) */
		/* (channel,rpf,cpf):=(c,row_pixel_feature,col_pixel_feature)*/

		/* f=h*g��һ�����Ϻ�����ϵ */

		/* index_in_kernel��������������Ԫ������ڵ���(��ά)����˵����λ�ã�*/
		int index_in_kernel = 0;

		switch (padding_mode)
		{
		case VALID_PADDING:
			for (int i = 0; i < m_features_matrix.m_rows; ++i){
				for (int j = 0; j < m_features_matrix.m_cols; ++j){
					/* g: (i,j) -> (channel,rpk,cpk,rkf,ckf) */
					channel = j / (m_kernel_rows*m_kernel_cols);/* �˴��˷������Ż� */
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


		/* ��������������ȷ��������Ϸ�Ԫ�ص���kernel�е�λ�� */
		int channel = 0;/* ��channel_in_features, channel����ڼ��������(����) */
		int rpk = 0;     /* row����Ԫ������ھ����(��ά)���Ϸ�Ԫ�ص����� ��kernels(4 dims)kernel(3 dims)����Ĳ�һ��)*/
		int cpk = 0;    /*  ����ͬ�� col����Ԫ������ھ�������Ϸ�Ԫ�ص����� */
		/* ��������������ȷ��������������Ϸ�Ԫ�ص���kernel�е�λ�� */
		
		/* index_in_kernels��������������Ԫ������ڵ�������˵����λ�ã�һά��*/
		int index_in_kernel = 0;
		/* ��������������ȷ����������Ͻ�Ԫ������ڵ���������λ�� */
		int rkf = 0;
		int ckf = 0;
		/* ����ţ����ѧ�е����λ�ã�������ת����\
		   �ܹ�ȷ��features_matrixԪ�ض�Ӧ����ԭʼfeatures�еľ���λ�� */

		int rpf = 0;
		int cpf = 0;
		switch (padding_mode){
			/* features2matrix */
		case VALID_PADDING: /* (N+2P-K)/S +1 */
			m_features_matrix = matrix(((m_rows - m_kernel_rows) / stride + 1)* \
				((m_cols - m_kernel_cols) / stride + 1), \
				m_kernel_rows*m_kernel_cols*m_channels);
			/* �����Ǻ��Ĵ��� features2matrix */
			/* todo �˴���������Ż� */
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
					/* A�����C��λ�� = A�����B��λ�� + B�����C��λ�� */
					rpf = rpk + rkf;/* Ԫ����ԭʼ�����е���(��)�� = Ԫ���ھ�����е���(��)�� + ������������е�(����)�� */
					cpf = cpk + ckf;/* �˴��ľ������ָ��ά����� */
					/* Ԫ���ھ�����е�λ����ָԪ������ھ�������Ϸ�Ԫ�ض��� */
					/* �����������ͼ�е�λ����ָ��������Ϸ�Ԫ�����������ͼ���Ϸ�Ԫ�ص�λ�� */
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