#ifndef _LAYERS_H_
#define _LAYERS_H_

#include "layer.h"
#include "layers_parameters.h"

class layers{
public:
	layers();
	layers(int channels, int rows, int cols, layer_parameters* players_params, int layers_counts);
	~layers();
	bool forward_propagation();
	bool back_propagation(int gt_label[]);
	bool show();
	bool show_shapes();
	bool probability();
public:
	layer *mp_layers;
	int m_layers_counts;
	features y;/* y0,y1,y2,...,y9 */
	features t;/* ti=e^yi */
	features q;/* p_i=ti/(t0+t1+...+t9) */

	features y_diff;
	features t_diff;
	features q_diff;
};
#endif