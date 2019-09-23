#include "../include/layers.h"
#include <math.h>/* for exp */

layers::layers(){
	mp_layers = NULL;
	m_layers_counts = 0;
}

layers::layers(int channels, int rows, int cols, layer_parameters* mp_layers_params, int layers_counts){
	//layer* mp_layers = new layer[LAYERS_COUNTS], *t = NULL;
	m_layers_counts = layers_counts;
	mp_layers = new layer[m_layers_counts];
	layer *tmp = NULL;
	mp_layers[0] = layer(channels, rows, cols, mp_layers_params);
	for (int i = 1; i < LAYERS_COUNTS; ++i){
		//std::cout << layers_parameters[i].kernel_channels << std::endl;
		mp_layers[i].m_stride = layers_parameters[i].stride;
		int channels = 0;
		int rows = 0;
		int cols = 0;
		int P = 0;/* valid padding */
		switch (layers_parameters[i - 1].layer_mode){
		case POOLING_LAYER:
			tmp = mp_layers + i - 1;
			mp_layers[i] = layer(tmp->m_fts.m_channels, tmp->m_fts.m_rows / POOLING_SIZE, \
				tmp->m_fts.m_cols / POOLING_SIZE, layers_parameters + i);

			break;
		case CONVOLUTION_LAYER:
			tmp = mp_layers + i - 1;
			channels = tmp->m_conv_mat.m_cols;
			rows = tmp->m_fts.m_rows - tmp->m_kers.m_rows;
			cols = tmp->m_fts.m_cols - tmp->m_kers.m_cols;

			if (SAME_PADDING == tmp->m_padding_mode){
				P = (tmp->m_kers.m_rows - 1) / 2;
			}
			rows = (rows + 2 * P) / tmp->m_stride + 1;
			cols = (cols + 2 * P) / tmp->m_stride + 1;
			mp_layers[i] = layer(channels, rows, cols, layers_parameters + i);
			break;
		case FULLCONNECTION_LAYER:
			tmp = mp_layers + i - 1;
			channels = tmp->m_conv_mat.m_cols;
			rows = tmp->m_fts.m_rows - tmp->m_kers.m_rows;
			cols = tmp->m_fts.m_cols - tmp->m_kers.m_cols;

			rows = rows / tmp->m_stride + 1;
			cols = cols / tmp->m_stride + 1;
			mp_layers[i] = layer(channels, rows, cols, layers_parameters + i);
			break;
		default:;
			break;
		}

		if (LAYERS_COUNTS - 1 == i){/* 最后一层确定输出的大小 */
			y = features(mp_layers[i].m_kers.m_kers_counts, 1, 1, 0.0);
			t = features(mp_layers[i].m_kers.m_kers_counts, 1, 1, 0.0);
			q = features(mp_layers[i].m_kers.m_kers_counts, 1, 1, 0.0);
			y_diff = features(mp_layers[i].m_kers.m_kers_counts, 1, 1, 0.0);
			t_diff = features(mp_layers[i].m_kers.m_kers_counts, 1, 1, 0.0);
			q_diff = features(mp_layers[i].m_kers.m_kers_counts, 1, 1, 0.0);
		}
	}
}

layers::~layers(){
	if (NULL != mp_layers){
		delete[] mp_layers;
		mp_layers = NULL;
	}
	m_layers_counts = 0;
}

bool layers::show_shapes(){
	if (NULL == mp_layers || 0 >= m_layers_counts){
		return false;
	}
	for (int i = 0; i < m_layers_counts; i++){
		std::cout << "第 " << i + 1 << " 层参数 " << std::endl;
		//show_layer_parameters(p_layers + i);
		mp_layers[i].show_shapes();
		std::cout << std::endl;
	}
	return true;
}

bool layers::show(){
	for (int i = 0; i < LAYERS_COUNTS; ++i){
		mp_layers[i].show();
		std::cout << "*****************************************\n";
	}
	return true;
}

bool layers::forward_propagation(){
	;/* todo */
	for (int i = 0; i < m_layers_counts; ++i){

		switch (mp_layers[i].m_layer_mode)
		{
		case FULLCONNECTION_LAYER:/* 全连接层当作卷积层的特殊情况 */
			;
		case CONVOLUTION_LAYER:
			mp_layers[i].reshape(mp_layers[i].m_fts, mp_layers[i].m_fts_mat);
			mp_layers[i].reshape(mp_layers[i].m_kers, mp_layers[i].m_kers_mat);
			mp_layers[i].conv();
			//mp_layers[i].m_relu_mask.reset(1);/* relu mask 默认打开 */
			if (RELU_ON == mp_layers[i].m_relu){
				int t = 0;
				for (int r = 0; r < mp_layers[i].m_conv_mat.m_rows; ++r){
					for (int c = 0; c < mp_layers[i].m_conv_mat.m_cols; ++c){
						if (mp_layers[i].m_conv_mat.mp_data[t] < 0){
							mp_layers[i].m_conv_relu_mat.mp_data[t] = 0;
							mp_layers[i].m_relu_mask.mp_data[t] = 0;
						}
						else{
							mp_layers[i].m_conv_relu_mat.mp_data[t] = mp_layers[i].m_conv_mat.mp_data[t];
							mp_layers[i].m_relu_mask.mp_data[t] = 1;
						}
						++t;
					}
				}
				if (LAYERS_COUNTS - 1 != i){/* 不是最后一层，将结果输入下一层 */
					mp_layers[i].reshape(mp_layers[i].m_conv_relu_mat, mp_layers[i + 1].m_fts);
				}
				else{/* 最后一层实际上是不打开relu的，所以在这儿写就是为了保险 */
					mp_layers[i].reshape(mp_layers[i].m_conv_relu_mat, y);
				}
			}/* end relu_on */
			else{/* relu off */
				if (LAYERS_COUNTS - 1 != i){/* 不是最后一层，将结果输入下一层 */
					mp_layers[i].reshape(mp_layers[i].m_conv_mat, mp_layers[i + 1].m_fts);
				}
				else{/* 最后一层实际上是不打开relu的，所以在这儿写就是为了保险 */
					mp_layers[i].reshape(mp_layers[i].m_conv_mat, y);
				}
			}
			break;
		case POOLING_LAYER:/* todo 实际上我们认为pooling 不是最后一层 */
			if (MAX_POOLING == mp_layers[i].m_pooling_mode){
				mp_layers[i].reshape(mp_layers[i].m_pooling_mask, mp_layers[i + 1].m_fts);
			}
			else if (AVE_POOLING == mp_layers[i].m_padding_mode){
				;/* todo */
			}
			else{
				DEBUG_PRINT("   forward_propagation  POOLING_LAYER: ");
			}

			break;

		default:;
			break;
		}

		//mp_layers[i].m_fts.show();
		//std::cout << "******************************************i=" << i << std::endl;
		//int xxx = 0;
	}
	probability();
	for (int i = 0; i < LAYERS_COUNTS; ++i){
		;
	}
	return true;
}

bool layers::back_propagation(int gt_label[]){
	/* todo */
	//p_.reset(0.0);
	int i = -1;

	for (int j = 0; j < q.m_channels; ++j){
		if (0 != gt_label[j]){
			i = j;
			break;
		}
	}
	int qmax_index = 0;
	double q_max = q.mp_matrixes[0].mp_data[0];
	for (int j = 1; j < q.m_channels; ++j){
		if (q_max < q.mp_matrixes[j].mp_data[0]){
			qmax_index = j;
			q_max = q.mp_matrixes[j].mp_data[0];
		}
	}
	double loss = -log(q.mp_matrixes[i].mp_data[0]);
	//for (int j = 0; j < q.m_channels; ++j){
	//	if (0 == i - j){
	//		q_diff.mp_matrixes[i].mp_data[0] = -1.0 / q.mp_matrixes[i].mp_data[0];
	//	}
	//	else{
	//		q_diff.mp_matrixes[j].mp_data[0] = 0.0;
	//	}
	//}

	double sum_t = 0.0;

	for (int j = 0; j < t.m_channels; ++j){
		sum_t += t.mp_matrixes[j].mp_data[0];
	}

	for (int j = 0; j < LABELS_COUNTS; ++j){
		if (j == i){
			y_diff.mp_matrixes[i].mp_data[0] = (t.mp_matrixes[i].mp_data[0] - sum_t)*(t.mp_matrixes[i].mp_data[0] - DELTA);
		}
		else{
			y_diff.mp_matrixes[j].mp_data[0] = t.mp_matrixes[j].mp_data[0] * (t.mp_matrixes[j].mp_data[0] - DELTA);
		}
	}

	//double max = y_diff.mp_matrixes[0].mp_data[0];
	//double min = y_diff.mp_matrixes[0].mp_data[0];
	//for (int j = 0; j < 10; ++j){
	//	if (max < y_diff.mp_matrixes[j].mp_data[0]){
	//		max = y_diff.mp_matrixes[j].mp_data[0];
	//	}
	//	if (min > y_diff.mp_matrixes[j].mp_data[0]){
	//		min = y_diff.mp_matrixes[j].mp_data[0];
	//	}
	//}

	////double p = y.mp_matrixes[i].mp_data[0];/* todo 此处有问题 */
	////double p = q.mp_matrixes[i].mp_data[0] - EPSILON;
	////double scale = (1.0 - sqrt(p));
	//double p = q.mp_matrixes[i].mp_data[0] - EPSILON;
	//double scale = (1.0 - p);
	//for (int j = 0; j < 10; ++j){
	//	y_diff.mp_matrixes[j].mp_data[0] = 2.0*(y_diff.mp_matrixes[j].mp_data[0] - min) / (max - min) - 1.0;
	//	y_diff.mp_matrixes[j].mp_data[0] *= scale;
	//}

	double max = ABS(y_diff.mp_matrixes[0].mp_data[0]);
	int index = 0;
	/* qj tj  ydiffj （j!=i） 正相关    ti最大 max=y_diff[i]   else max=最大的y_diff[j] */
	//double min = y_diff.mp_matrixes[0].mp_data[0];
	for (int j = 1; j < LABELS_COUNTS; ++j){
		if (max < ABS(y_diff.mp_matrixes[j].mp_data[0])){
			max = ABS(y_diff.mp_matrixes[j].mp_data[0]);
			index = j;
		}
	}

	//double p = y.mp_matrixes[i].mp_data[0];/* todo 此处有问题 */
	//double p = q.mp_matrixes[i].mp_data[0] - EPSILON;
	//double scale = (1.0 - sqrt(p));
	double scale = 0;
	double p = q.mp_matrixes[i].mp_data[0] - EPSILON;
	if (p > THRESHOLD_){
		//if (p > 0.998){
		//	scale = -0.010;
		//}
		//else{
		//	scale = 0.012;
		//}
		scale = 0;
	}
	else{
		if (p > 0.5){
			scale = 1.0 - p;
			if (scale > 0.15){
				scale = 0.15;
			}
		}
		else{
			scale = 1.2 - p;
			if (p < 0.15){
				scale *= 2.0;
			}
		}
	}
	for (int j = 0; j < 10; ++j){
		//y_diff.mp_matrixes[j].mp_data[0] = 2.0*(y_diff.mp_matrixes[j].mp_data[0] - min) / (max - min) - 1.0;
		y_diff.mp_matrixes[j].mp_data[0] /= max;
		y_diff.mp_matrixes[j].mp_data[0] *= scale;
	}

	//double const_num = sum_t;/* 线性scale */
	//for (int j = 0; j < t.m_channels; ++j){
	//	if (0 == i - j){
	//		//t_diff.mp_matrixes[i].mp_data[0] = q_diff.mp_matrixes[i].mp_data[0] * \
							//		//	(sum_t - t.mp_matrixes[i].mp_data[0]) / (sum_t*sum_t);

	//		//t_diff.mp_matrixes[i].mp_data[0] = (t.mp_matrixes[i].mp_data[0] - sum_t) / const_num;
	//		y_diff.mp_matrixes[i].mp_data[0] = (t.mp_matrixes[i].mp_data[0] - sum_t)*(t.mp_matrixes[i].mp_data[0] - EPSILON) / const_num;
	//	}
	//	else{
	//		//t_diff.mp_matrixes[j].mp_data[0] = q_diff.mp_matrixes[i].mp_data[0] * \
							//		//	(-t.mp_matrixes[j].mp_data[0]) / (sum_t*sum_t);
	//		//t_diff.mp_matrixes[j].mp_data[0] = (t.mp_matrixes[j].mp_data[0]) / const_num;
	//		y_diff.mp_matrixes[j].mp_data[0] = (t.mp_matrixes[j].mp_data[0])*(t.mp_matrixes[j].mp_data[0] - EPSILON) / const_num;
	//	}
	//}

	//for (int j = 0; j < y.m_channels; ++j){
	//	y_diff.mp_matrixes[j].mp_data[0] = t_diff.mp_matrixes[j].mp_data[0] * (t.mp_matrixes[j].mp_data[0] - EPSILON);
	//}

	/* 先处理最后一层 */
	/* 最后一层是没有relu的 所以好处理一些 */
	mp_layers[LAYERS_COUNTS - 1].reshape_(y_diff, mp_layers[LAYERS_COUNTS - 1].m_conv_mat_diff);
	mp_layers[LAYERS_COUNTS - 1].transposition(mp_layers[LAYERS_COUNTS - 1].m_kers_mat, mp_layers[LAYERS_COUNTS - 1].m_kers_mat_T);
	mp_layers[LAYERS_COUNTS - 1].transposition(mp_layers[LAYERS_COUNTS - 1].m_fts_mat, mp_layers[LAYERS_COUNTS - 1].m_fts_mat_T);
	mp_layers[LAYERS_COUNTS - 1].m_kers_mat_diff = mp_layers[LAYERS_COUNTS - 1].m_fts_mat_T*mp_layers[LAYERS_COUNTS - 1].m_conv_mat_diff;/* 此处的乘法会有内存的申请释放 todo */
	mp_layers[LAYERS_COUNTS - 1].m_fts_mat_diff = mp_layers[LAYERS_COUNTS - 1].m_conv_mat_diff*mp_layers[LAYERS_COUNTS - 1].m_kers_mat_T;
	mp_layers[LAYERS_COUNTS - 1].reshape_(mp_layers[LAYERS_COUNTS - 1].m_kers_mat_diff, \
		mp_layers[LAYERS_COUNTS - 1].m_kers_diff);
	mp_layers[LAYERS_COUNTS - 1].reshape_(mp_layers[LAYERS_COUNTS - 1].m_fts_mat_diff, \
		mp_layers[LAYERS_COUNTS - 1].m_fts_diff);
	//std::cout << "LAYERS_COUNTS-1" << std::endl;
	//mp_layers[LAYERS_COUNTS - 1].m_fts_diff.show();
	for (int i = LAYERS_COUNTS - 2; i >= 0; --i){
		switch (mp_layers[i].m_layer_mode)
		{
		case FULLCONNECTION_LAYER:
		case CONVOLUTION_LAYER:/* 卷积层实际上是默认 relu_on 的 */
			if (RELU_OFF == mp_layers[i].m_relu){
				mp_layers[i].reshape_(mp_layers[i + 1].m_fts_diff, mp_layers[i].m_conv_mat_diff);
				mp_layers[i].transposition(mp_layers[i].m_kers_mat, mp_layers[i].m_kers_mat_T);
				mp_layers[i].transposition(mp_layers[i].m_fts_mat, mp_layers[i].m_fts_mat_T);
				mp_layers[i].m_kers_mat_diff = mp_layers[i].m_fts_mat_T*mp_layers[i].m_conv_mat_diff;/* 此处的乘法会有内存的申请释放 todo */
				mp_layers[i].m_fts_mat_diff = mp_layers[i].m_conv_mat_diff*mp_layers[i].m_kers_mat_T;
				mp_layers[i].reshape_(mp_layers[i].m_kers_mat_diff, \
					mp_layers[i].m_kers_diff);
				mp_layers[i].reshape_(mp_layers[i].m_fts_mat_diff, \
					mp_layers[i].m_fts_diff);

			}
			else if (RELU_ON == mp_layers[i].m_relu){
				mp_layers[i].reshape_(mp_layers[i + 1].m_fts_diff, mp_layers[i].m_conv_relu_mat_diff);
				//mp_layers[i].m_conv_relu_mat_diff.show();
				//mp_layers[i].m_relu_mask.show();
				mp_layers[i].hadamard_product(mp_layers[i].m_conv_relu_mat_diff, mp_layers[i].m_relu_mask, mp_layers[i].m_conv_mat_diff);
				//mp_layers[i].m_conv_mat_diff.show();
				mp_layers[i].transposition(mp_layers[i].m_kers_mat, mp_layers[i].m_kers_mat_T);
				//mp_layers[i].m_kers_mat_T.show();
				mp_layers[i].transposition(mp_layers[i].m_fts_mat, mp_layers[i].m_fts_mat_T);
				//mp_layers[i].m_fts_mat_T.show();
				mp_layers[i].m_kers_mat_diff = mp_layers[i].m_fts_mat_T*mp_layers[i].m_conv_mat_diff;/* 此处的乘法会有内存的申请释放 todo */
				//mp_layers[i].m_kers_mat_diff.show();
				mp_layers[i].m_fts_mat_diff = mp_layers[i].m_conv_mat_diff*mp_layers[i].m_kers_mat_T;
				//mp_layers[i].m_kers_mat_diff.show();
				mp_layers[i].reshape_(mp_layers[i].m_kers_mat_diff, \
					mp_layers[i].m_kers_diff);
				//mp_layers[i].m_kers_diff.show();
				mp_layers[i].reshape_(mp_layers[i].m_fts_mat_diff, \
					mp_layers[i].m_fts_diff);
				//mp_layers[i].m_fts_diff.show();
			}
			else{
				;/* todo */
				DEBUG_PRINT("back propagation error\n");
				return false;
			}
			break;
		case POOLING_LAYER:
			int t0 = 0;
			switch (mp_layers[i].m_pooling_mode){

			case MAX_POOLING:
				mp_layers[i].m_fts_diff.reset(0.0);
				t0 = 0;
				for (int channel = 0; channel < mp_layers[i].m_fts_diff.m_channels; ++channel){
					for (int k = 0; k < mp_layers[i].m_fts_diff.m_rows; ++k){
						t0 = k*mp_layers[i].m_fts_diff.m_cols;
						for (int j = 0; j < mp_layers[i].m_fts_diff.m_cols; ++j){
							//if (1 == mp_layers[i].m_pooling_mask.mp_matrixes[channel].\
							//	mp_data[k*mp_layers[i].m_fts_diff.m_cols + j]){
							//	mp_layers[i].m_fts_diff.mp_matrixes[channel].mp_data\
							//		[k*mp_layers[i].m_fts_diff.m_cols + j] = \
							//		mp_layers[i + 1].m_fts_diff.mp_matrixes[channel].\
							//		mp_data[(k / mp_layers[i].m_pooling_size)*mp_layers[i + 1].\
							//		m_fts_diff.m_cols + (j / mp_layers[i].m_pooling_size)];
							//}
							if (1 == mp_layers[i].m_pooling_mask.mp_matrixes[channel].mp_data[t0 + j]){
								mp_layers[i].m_fts_diff.mp_matrixes[channel].mp_data[t0+ j] = \
									mp_layers[i + 1].m_fts_diff.mp_matrixes[channel].\
									mp_data[(k / mp_layers[i].m_pooling_size)*mp_layers[i + 1].m_fts_diff.m_cols \
									+ (j / mp_layers[i].m_pooling_size)];
							}
						}
					}
				}
				break;
			case AVE_POOLING:
				/* todo */
				break;
			}
		}
	}

	return true;
}

bool layers::probability(){
	DATA_TYPE sum = 0;
	for (int i = 0; i < y.m_channels; ++i){
		//t.mp_matrixes[i].mp_data[0] = exp(y.mp_matrixes[i].mp_data[0]);
		/* todo */
		if (y.mp_matrixes[i].mp_data[0] > MAX_UP){
			y.mp_matrixes[i].mp_data[0] = MAX_UP;
		}
		if (y.mp_matrixes[i].mp_data[0] < -MAX_UP){
			y.mp_matrixes[i].mp_data[0] = -MAX_UP;
		}
		t.mp_matrixes[i].mp_data[0] = DELTA + pow(POW_NUM, y.mp_matrixes[i].mp_data[0]);//exp(y.mp_matrixes[i].mp_data[0]);//pow(2.0, y.mp_matrixes[i].mp_data[0]);
		//if (t.mp_matrixes[i].mp_data[0] > MAX_UP){
		//    t.mp_matrixes[i].mp_data[0] = MAX_UP;
		//}
		sum += t.mp_matrixes[i].mp_data[0];
	}

	for (int i = 0; i < y.m_channels; ++i){
		q.mp_matrixes[i].mp_data[0] = t.mp_matrixes[i].mp_data[0] / sum + EPSILON;
	}
	return true;
}