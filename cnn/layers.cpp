#include "layers.h"
layers::layers(){
	mp_layers = NULL;
	m_layers_counts = 0;
}

layers::layers(int channels, int rows, int cols, layer_parameters* mp_layers_params, int layers_counts){
	//layer* mp_layers = new layer[LAYERS_COUNTS], *t = NULL;
	m_layers_counts = layers_counts;
	mp_layers = new layer[m_layers_counts];
	layer *t = NULL;
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
			t = mp_layers + i - 1;
			mp_layers[i] = layer(t->m_fts.m_channels, t->m_fts.m_rows / POOLING_SIZE, \
				t->m_fts.m_cols / POOLING_SIZE, layers_parameters + i);

			break;
		case CONVOLUTION_LAYER:
			t = mp_layers + i - 1;
			channels = t->m_conv_mat.m_cols;
			rows = t->m_fts.m_rows - t->m_kers.m_rows;
			cols = t->m_fts.m_cols - t->m_kers.m_cols;

			if (SAME_PADDING == t->m_padding_mode){
				P = (t->m_kers.m_rows - 1) / 2;
			}
			rows = (rows + 2 * P) / t->m_stride + 1;
			cols = (cols + 2 * P) / t->m_stride + 1;
			mp_layers[i] = layer(channels, rows, cols, layers_parameters + i);
			break;
		case FULLCONNECTION_LAYER:
			t = mp_layers + i - 1;
			channels = t->m_conv_mat.m_cols;
			rows = t->m_fts.m_rows - t->m_kers.m_rows;
			cols = t->m_fts.m_cols - t->m_kers.m_cols;

			rows = rows / t->m_stride + 1;
			cols = cols / t->m_stride + 1;
			mp_layers[i] = layer(channels, rows, cols, layers_parameters + i);
			break;
		default:;
			break;
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
		std::cout << "µÚ " << i + 1 << " ²ã²ÎÊý " << std::endl;
		//show_layer_parameters(p_layers + i);
		mp_layers[i].show_shapes();
		std::cout << std::endl;
	}
}