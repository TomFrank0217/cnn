#ifndef _LAYERS_H_
#define _LAYERS_H_

#include "layer.h"
#include "layers_parameters.h"

class layers{
public:
	layers();
	layers(int channels, int rows, int cols, layer_parameters* players_params, int layers_counts);
	~layers();
	bool show_shapes();
public:
	layer *mp_layers;
	int m_layers_counts;
};
#endif