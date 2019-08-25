#include "layers.h"
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

		if (LAYERS_COUNTS - 1 == i){/* ���һ��ȷ������Ĵ�С */
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
		std::cout << "�� " << i + 1 << " ����� " << std::endl;
		//show_layer_parameters(p_layers + i);
		mp_layers[i].show_shapes();
		std::cout << std::endl;
	}
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
		case FULLCONNECTION_LAYER:/* ȫ���Ӳ㵱��������������� */
			;
		case CONVOLUTION_LAYER:
			mp_layers[i].reshape(mp_layers[i].m_fts, mp_layers[i].m_fts_mat);
			mp_layers[i].reshape(mp_layers[i].m_kers, mp_layers[i].m_kers_mat);
			mp_layers[i].conv();
			//mp_layers[i].m_relu_mask.reset(1);/* relu mask Ĭ�ϴ� */
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
				if (LAYERS_COUNTS - 1 != i){/* �������һ�㣬�����������һ�� */
					mp_layers[i].reshape(mp_layers[i].m_conv_relu_mat, mp_layers[i + 1].m_fts);
				}
				else{/* ���һ��ʵ�����ǲ���relu�ģ����������д����Ϊ�˱��� */
					mp_layers[i].reshape(mp_layers[i].m_conv_relu_mat, y);
				}
			}/* end relu_on */
			else{/* relu off */
				if (LAYERS_COUNTS - 1 != i){/* �������һ�㣬�����������һ�� */
					mp_layers[i].reshape(mp_layers[i].m_conv_mat, mp_layers[i + 1].m_fts);
				}
				else{/* ���һ��ʵ�����ǲ���relu�ģ����������д����Ϊ�˱��� */
					mp_layers[i].reshape(mp_layers[i].m_conv_mat, y);
				}
			}
				break;
		case POOLING_LAYER:/* todo ʵ����������Ϊpooling �������һ�� */
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
	int i = 0;
	for (int j = 0; j < q.m_channels; ++j){
		if (0 != gt_label[j]){
			i = j;
			break;
		}
	}

	double loss = -log(q.mp_matrixes[i].mp_data[0]);
	for (int j = 0; j < q.m_channels; ++j){
		if (0 == i - j){
			q_diff.mp_matrixes[i].mp_data[0] = -1.0 / q.mp_matrixes[i].mp_data[0];
		}
		else{
			q_diff.mp_matrixes[j].mp_data[0] = 0.0;
		}
	}

	double sum_t = 0.0;
	for (int j = 0; j < t.m_channels; ++j){
		sum_t += t.mp_matrixes[j].mp_data[0];
	}

	for (int j = 0; j < t.m_channels; ++j){
		if (0 == i - j){
			t_diff.mp_matrixes[i].mp_data[0] = q_diff.mp_matrixes[i].mp_data[0] * \
				(sum_t - t.mp_matrixes[i].mp_data[0]) / (sum_t*sum_t);
		}
		else{
			t_diff.mp_matrixes[j].mp_data[0] = q_diff.mp_matrixes[i].mp_data[0] * \
				(-t.mp_matrixes[j].mp_data[0]) / (sum_t*sum_t);
		}
	}

	for (int j = 0; j < y.m_channels; ++j){
		y_diff.mp_matrixes[j].mp_data[0] = \
			t_diff.mp_matrixes[j].mp_data[0] * t.mp_matrixes[j].mp_data[0];
	}

    /* �ȴ������һ�� */
    /* ���һ����û��relu�� ���Ժô���һЩ */
    mp_layers[LAYERS_COUNTS - 1].reshape_(y_diff, mp_layers[LAYERS_COUNTS - 1].m_conv_mat_diff);
    mp_layers[LAYERS_COUNTS - 1].transposition(mp_layers[LAYERS_COUNTS - 1].m_kers_mat, mp_layers[LAYERS_COUNTS - 1].m_kers_mat_T);
    mp_layers[LAYERS_COUNTS - 1].transposition(mp_layers[LAYERS_COUNTS - 1].m_fts_mat, mp_layers[LAYERS_COUNTS - 1].m_fts_mat_T);
    mp_layers[LAYERS_COUNTS - 1].m_kers_mat_diff = mp_layers[LAYERS_COUNTS - 1].m_fts_mat_T*mp_layers[LAYERS_COUNTS - 1].m_conv_mat_diff;/* �˴��ĳ˷������ڴ�������ͷ� todo */
    mp_layers[LAYERS_COUNTS - 1].m_fts_mat_diff = mp_layers[LAYERS_COUNTS - 1].m_conv_mat_diff*mp_layers[LAYERS_COUNTS - 1].m_kers_mat_T;
    mp_layers[LAYERS_COUNTS - 1].reshape_ (mp_layers[LAYERS_COUNTS - 1].m_kers_mat_diff, \
        mp_layers[LAYERS_COUNTS - 1].m_kers_diff);
    mp_layers[LAYERS_COUNTS - 1].reshape_(mp_layers[LAYERS_COUNTS - 1].m_fts_mat_diff, \
        mp_layers[LAYERS_COUNTS - 1].m_fts_diff);
	//std::cout << "LAYERS_COUNTS-1" << std::endl;
	//mp_layers[LAYERS_COUNTS - 1].m_fts_diff.show();
	for (int i = LAYERS_COUNTS - 2; i >= 0; --i){
        switch (mp_layers[i].m_layer_mode)
        {
        case FULLCONNECTION_LAYER:
        case CONVOLUTION_LAYER:/* �����ʵ������Ĭ�� relu_on �� */
            if (RELU_OFF == mp_layers[i].m_relu){
                mp_layers[i].reshape_(mp_layers[i + 1].m_fts_diff, mp_layers[i].m_conv_mat_diff);
                mp_layers[i].transposition(mp_layers[i].m_kers_mat, mp_layers[i].m_kers_mat_T);
                mp_layers[i].transposition(mp_layers[i].m_fts_mat, mp_layers[i].m_fts_mat_T);
                mp_layers[i].m_kers_mat_diff = mp_layers[i].m_fts_mat_T*mp_layers[i].m_conv_mat_diff;/* �˴��ĳ˷������ڴ�������ͷ� todo */
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
                mp_layers[i].m_kers_mat_diff = mp_layers[i].m_fts_mat_T*mp_layers[i].m_conv_mat_diff;/* �˴��ĳ˷������ڴ�������ͷ� todo */
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
            switch (mp_layers[i].m_pooling_mode){
            case MAX_POOLING:
                mp_layers[i].m_fts_diff.reset(0.0);
                for (int channel = 0; channel < mp_layers[i].m_fts_diff.m_channels; ++channel){
                    for (int k = 0; k < mp_layers[i].m_fts_diff.m_rows; ++k){
                        for (int j = 0; j < mp_layers[i].m_fts_diff.m_cols; ++j){
                            if (1 == mp_layers[i].m_pooling_mask.mp_matrixes[channel].mp_data[k*mp_layers[i].m_fts_diff.m_cols + j]){
                                mp_layers[i].m_fts_diff.mp_matrixes[channel].mp_data[k*mp_layers[i].m_fts_diff.m_cols + j] = mp_layers[i + 1].m_fts_diff.mp_matrixes[channel].mp_data[(k / mp_layers[i].m_pooling_size)*mp_layers[i + 1].m_fts_diff.m_cols + (j / mp_layers[i].m_pooling_size)];
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
        if (y.mp_matrixes[i].mp_data[0] > MAX_UP){
            y.mp_matrixes[i].mp_data[0] = MAX_UP;
        }
        if (y.mp_matrixes[i].mp_data[0] < -MAX_UP){
            y.mp_matrixes[i].mp_data[0] = -MAX_UP;
        }
		t.mp_matrixes[i].mp_data[0] = EPSILON + pow(POW_NUM, y.mp_matrixes[i].mp_data[0]);//exp(y.mp_matrixes[i].mp_data[0]);//pow(2.0, y.mp_matrixes[i].mp_data[0]);
        //if (t.mp_matrixes[i].mp_data[0] > MAX_UP){
        //    t.mp_matrixes[i].mp_data[0] = MAX_UP;
        //}
		sum += t.mp_matrixes[i].mp_data[0];
	}
	
	for (int i = 0; i < y.m_channels; ++i){
		q.mp_matrixes[i].mp_data[0] = EPSILON2 + t.mp_matrixes[i].mp_data[0] / sum;
	}
	return true;
}