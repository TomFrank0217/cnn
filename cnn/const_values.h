#ifndef _CONST_VALUES_H_
#define _CONST_VALUES_H_

#define DATA_TYPE                   double

#define RANDOM_INITIAL_VAL          0.05

#define KERS_MIN_VAL                -RANDOM_INITIAL_VAL
#define KERS_MAX_VAL                RANDOM_INITIAL_VAL

#define INITIAL_NUMBER              0.0

#define SHOW_IMAGE_SCALE_VALUE      0
#define SHOW_IMAGE_INITAIL_VALUE    1 
#define SHOW_IMAGE_SHAPE            2
#define SHOW_IMAGE_CROP_LENGTH      0
#define SHOW_WIDTH                  5

#define VALID_PADDING               0
#define SAME_PADDING                1

#define STRIDE                      1

#define MAX_POOLING                 0
#define AVE_POOLING                 1
#define POOLING_SIZE                2

#define IMAGE_UNIT_VALUE            5.0
#define  AVE_VALUE                  127.5

#define MINUS                       -1
#define KERNEL_ROWS                 2
#define KERNEL_COLS                 3

#define KERNELS2MATRIEX             0
#define MATRIEX2KERNELS             1

#define FEATURES2MATRIX             0
#define MATRIX2FEATURES             1

#define ABS(X)                      ((X)>0.0?(X):-(X))
#define DELTA                       0.001

#define CONVOLUTION_LAYER           0
#define POOLING_LAYER               1
#define FULLCONNECTION_LAYER        2

#define RELU_OFF                    0
#define RELU_ON                     1

#define LAYER_INITIAL_LENGTH        0
#define LAYERS_COUNTS               7

#define POW_NUM                     1.5

#define  TEST_TIMES                 10000

#define EPSILON                     0.01
#define EPSILON2                    0.001
#define MAX_UP                      500
#endif