#ifndef _LAYER_PARAMETERS_H_
#define _LAYER_PARAMETERS_H_

typedef struct layer_parameters{
	int layer_mode;
	int kernel_channels;
	int kernel_rows;
	int kernel_cols;
	int kernels_counts;
	int stride;
	int padding_mode; /* valid padding_size=0,same padding_size=(kernel_rows-1)/2 ...... */
	int relu;
	int pooling_mode;
	int pooling_size;
}layer_parameters;//layer_parameters;

extern layer_parameters layers_parameters[];

#endif