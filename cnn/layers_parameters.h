#ifndef _LAYER_PARAMETERS_H_
#define _LAYER_PARAMETERS_H_

typedef struct layer_parameters{
	int layer_mode;
	int kernel_channels;
	int kernel_rows;
	int kernel_cols;
	int kernel_counts;
	int feature_channels;
	int feature_rows;
	int features_cols;
	int relu;
	int pooling_size;
};//layer_parameters;

extern layer_parameters layers_parameters[];

#endif