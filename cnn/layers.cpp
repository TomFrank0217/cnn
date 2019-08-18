#include "layers.h"
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
			y = features(mp_layers[i].m_kers.m_kers_counts, 1, 1);
			t = features(mp_layers[i].m_kers.m_kers_counts, 1, 1);
			p_ = features(mp_layers[i].m_kers.m_kers_counts, 1, 1);
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
	}

	return true;
}

bool layers::back_propagation(){
	/* todo */
	return true;
}
