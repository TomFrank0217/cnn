#include "layers_parameters.h"
#include "const_values.h"

//layer_parameters layers_parameters[LAYERS_COUNTS] = {
//layer_parameters{//1
//	CONVOLUTION_LAYER,
//	1,
//	2,
//	2,
//	2,
//	STRIDE,
//	VALID_PADDING,
//	RELU_ON,
//	MINUS,
//	MINUS
//},
//layer_parameters{//2
//		POOLING_LAYER,
//		MINUS,
//		MINUS,
//		MINUS,
//		MINUS,
//		MINUS,
//		MINUS,
//		RELU_OFF,
//		MAX_POOLING,
//		POOLING_SIZE
//	},
//	layer_parameters{//3
//			FULLCONNECTION_LAYER,
//			2,
//			2,
//			2,
//			3,
//			STRIDE,
//			VALID_PADDING,
//			RELU_OFF,
//			MINUS,
//			MINUS
//		},
//};

layer_parameters layers_parameters[LAYERS_COUNTS] = {
    layer_parameters{//1
        CONVOLUTION_LAYER,
        1,
        3,
        3,
        8,
        STRIDE,
        VALID_PADDING,
        RELU_OFF,
        MINUS,
        MINUS
    },
	layer_parameters{//1
		CONVOLUTION_LAYER,
		8,
		3,
		3,
		20,
		STRIDE,
		VALID_PADDING,
		RELU_OFF,
		MINUS,
		MINUS
	},
	layer_parameters{//2
			POOLING_LAYER,
			MINUS,
			MINUS,
			MINUS,
			MINUS,
			MINUS,
			MINUS,
			RELU_OFF,
			MAX_POOLING,
			POOLING_SIZE
		},
		layer_parameters{//3
				CONVOLUTION_LAYER,
				20,
				5,
				5,
				30,
				STRIDE,
				VALID_PADDING,
				RELU_OFF,
				MINUS,
				MINUS
			},
			layer_parameters{//4
					POOLING_LAYER,
					MINUS,
					MINUS,
					MINUS,
					MINUS,
					MINUS,
					MINUS,
					RELU_ON,
					MAX_POOLING,
					POOLING_SIZE
				},
				layer_parameters{//5
						FULLCONNECTION_LAYER,
						30,
						5,
						5,
						180,
						STRIDE,
						VALID_PADDING,
						RELU_ON,
						MINUS,
						MINUS
					},
					layer_parameters{//6
							FULLCONNECTION_LAYER,
							180,
							1,
							1,
							100,
							STRIDE,
							VALID_PADDING,
							RELU_OFF,
							MINUS,
							MINUS
						},
						layer_parameters{//7
								FULLCONNECTION_LAYER,
								100,
								1,
								1,
								10,
								STRIDE,
								VALID_PADDING,
								RELU_OFF,
								MINUS,
								MINUS
							}
};



//layer_parameters layers_parameters[LAYERS_COUNTS] = {
//    layer_parameters{//1
//		CONVOLUTION_LAYER,
//		1,
//		5,
//		5,
//		2,
//		STRIDE,
//		VALID_PADDING,
//		RELU_OFF,
//		MINUS,
//		MINUS
//	},
//    layer_parameters{//2
//		POOLING_LAYER,
//		MINUS,
//		MINUS,
//		MINUS,
//		MINUS,
//		MINUS,
//		MINUS,
//		RELU_OFF,
//		MAX_POOLING,
//		 POOLING_SIZE
//	},
//    layer_parameters{//3
//		CONVOLUTION_LAYER,
//		 2,
//		 5,
//		 5,
//		16,
//		STRIDE,
//		VALID_PADDING,
//		RELU_OFF,
//		MINUS,
//		MINUS
//	},
//    layer_parameters{//4
//			POOLING_LAYER,
//			MINUS,
//			MINUS,
//			MINUS,
//			MINUS,
//			MINUS,
//			MINUS,
//			RELU_OFF,
//			MAX_POOLING,
//			POOLING_SIZE
//	},
//    layer_parameters{//5
//		FULLCONNECTION_LAYER,
//		16,
//		 5,
//		 5,
//	   120,
//	   STRIDE,
//	   VALID_PADDING,
//	   RELU_ON,
//	   MINUS,
//	   MINUS
//	},
//    layer_parameters{//6
//		FULLCONNECTION_LAYER,
//	  120,
//		1,
//		1,
//	   84,
//	   STRIDE,
//	   VALID_PADDING,
//	   RELU_ON,
//	   MINUS,
//	   MINUS
//	},
//    layer_parameters{//7
//		FULLCONNECTION_LAYER,
//	   84,
//		1,
//		1,
//	   10,
//	   STRIDE,
//	   VALID_PADDING,
//	   RELU_OFF,
//	   MINUS,
//	   MINUS
//	}	
//};
//layer_parameters layers_parameters[LAYERS_COUNTS] = {
//    layer_parameters{//1
//		CONVOLUTION_LAYER,
//		1,
//		5,
//		5,
//		2,
//		STRIDE,
//		VALID_PADDING,
//		RELU_ON,
//		MINUS,
//		MINUS
//	},
//    layer_parameters{//2
//		POOLING_LAYER,
//		MINUS,
//		MINUS,
//		MINUS,
//		MINUS,
//		MINUS,
//		MINUS,
//		RELU_ON,
//		MAX_POOLING,
//		 POOLING_SIZE
//	},
//    layer_parameters{//3
//		CONVOLUTION_LAYER,
//		 2,
//		 5,
//		 5,
//		16,
//		STRIDE,
//		VALID_PADDING,
//		RELU_ON,
//		MINUS,
//		MINUS
//	},
//    layer_parameters{//4
//			POOLING_LAYER,
//			MINUS,
//			MINUS,
//			MINUS,
//			MINUS,
//			MINUS,
//			MINUS,
//			RELU_ON,
//			MAX_POOLING,
//			POOLING_SIZE
//	},
//    layer_parameters{//5
//		FULLCONNECTION_LAYER,
//		16,
//		 5,
//		 5,
//	   120,
//	   STRIDE,
//	   VALID_PADDING,
//	   RELU_ON,
//	   MINUS,
//	   MINUS
//	},
//    layer_parameters{//6
//		FULLCONNECTION_LAYER,
//	  120,
//		1,
//		1,
//	   84,
//	   STRIDE,
//	   VALID_PADDING,
//	   RELU_ON,
//	   MINUS,
//	   MINUS
//	},
//    layer_parameters{//7
//		FULLCONNECTION_LAYER,
//	   84,
//		1,
//		1,
//	   10,
//	   STRIDE,
//	   VALID_PADDING,
//	   RELU_OFF,
//	   MINUS,
//	   MINUS
//	}	
//};
////layer_parameters layers_parameters[LAYERS_COUNTS] = {
//	layer_parameters{//1
//		CONVOLUTION_LAYER,
//		1,
//		2,
//		2,
//		2,
//		STRIDE,
//		VALID_PADDING,
//		RELU_ON,
//		MINUS,
//		MINUS
//	},
//	{
//	POOLING_LAYER,
//	0,
//	0,
//	0,
//	0,
//	STRIDE,
//	VALID_PADDING,
//	RELU_ON,
//	MAX_POOLING,
//	POOLING_SIZE
//    },
//	{
//		FULLCONNECTION_LAYER,
//		2,
//		2,
//		2,
//		3,
//		STRIDE,
//		VALID_PADDING,
//		RELU_ON,
//		MINUS,
//		MINUS
//	}
//};
