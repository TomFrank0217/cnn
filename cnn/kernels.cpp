#include "kernels.h"

kernels::kernels(int kernels_count, int kernels_row, int kernels_col, int val):
m_kernels_features_count(kernels_count),m_kernels_features_row(kernels_row), m_kernels_features_col(kernels_col)
{
    if (0 >= m_kernels_features_count){
        DEBUG_PRINT("0 >= m_kernels_count\n");
        return;
    }

    m_p_kernels_features = new matrix[m_kernels_features_count];
    if (NULL == m_p_kernels_features){
        DEBUG_PRINT("NULL == m_p_kernels\n");
        return;
    }

    if (0 == m_kernels_features_row || 0 == m_kernels_features_col){
        DEBUG_PRINT("0 == m_kernels_row || 0 == m_kernels_col\n");
        m_p_kernels_features = NULL;
        return;
    }

    if (0 > m_kernels_features_row || 0 > m_kernels_features_col){
        DEBUG_PRINT("0 > m_kernels_row || 0 > m_kernels_col\n");
        m_p_kernels_features = NULL;
        return;
     }

    for (int i = 0; i < m_kernels_features_count; ++i){
        m_p_kernels_features[i] = matrix(m_kernels_features_row, m_kernels_features_col, val);
    }
    return;
}

kernels::kernels(int kernels_count, int kernels_row, int kernels_col, DATA_TYPE val):
m_kernels_features_count(kernels_count),m_kernels_features_row(kernels_row),m_kernels_features_col(kernels_col)
{
    if (0 >= m_kernels_features_count){
        DEBUG_PRINT("0 >= m_kernels_count\n");
        return;
    }

    m_p_kernels_features = new matrix[m_kernels_features_count];
    if (NULL == m_p_kernels_features){
        DEBUG_PRINT("NULL == m_p_kernels\n");
        return;
    }

    if (0 == m_kernels_features_row || 0 == m_kernels_features_col){
        DEBUG_PRINT("0 == m_kernels_row || 0 == m_kernels_col\n");
        m_p_kernels_features = NULL;
        return;
    }

    if (0 > m_kernels_features_row || 0 > m_kernels_features_col){
        DEBUG_PRINT("0 > m_kernels_row || 0 > m_kernels_col\n");
        m_p_kernels_features = NULL;
        return;
    }

    for (int i = 0; i < m_kernels_features_count; ++i){
        m_p_kernels_features[i] = matrix(m_kernels_features_row, m_kernels_features_col, val);
    }
    return;
}

kernels::kernels(int kernels_count, int kernels_row, int kernels_col, int min, int max):\
m_kernels_features_count(kernels_count), m_kernels_features_row(kernels_row), m_kernels_features_col(kernels_col)
    {
        if (0 >= m_kernels_features_count){
            DEBUG_PRINT("0 >= m_kernels_count\n");
            return;
        }

        m_p_kernels_features = new matrix[m_kernels_features_count];
        if (NULL == m_p_kernels_features){
            DEBUG_PRINT("NULL == m_p_kernels\n");
            return;
        }

        if (0 == m_kernels_features_row || 0 == m_kernels_features_col){
            DEBUG_PRINT("0 == m_kernels_row || 0 == m_kernels_col\n");
            m_p_kernels_features = NULL;
            return;
        }

        if (0 > m_kernels_features_row || 0 > m_kernels_features_col){
            DEBUG_PRINT("0 > m_kernels_row || 0 > m_kernels_col\n");
            m_p_kernels_features = NULL;
            return;
        }

        for (int i = 0; i < m_kernels_features_count; ++i){
            m_p_kernels_features[i] = matrix(m_kernels_features_row, m_kernels_features_col, min, max);
        }
        return;
    }

kernels::kernels(int kernels_count, int kernels_row, int kernels_col, DATA_TYPE min, DATA_TYPE max):\
    m_kernels_features_count(kernels_count), m_kernels_features_row(kernels_row), m_kernels_features_col(kernels_col)
    {
        if (0 >= m_kernels_features_count){
            DEBUG_PRINT("0 >= m_kernels_count\n");
            return;
        }

        m_p_kernels_features = new matrix[m_kernels_features_count];
        if (NULL == m_p_kernels_features){
            DEBUG_PRINT("NULL == m_p_kernels\n");
            return;
        }

        if (0 == m_kernels_features_row || 0 == m_kernels_features_col){
            DEBUG_PRINT("0 == m_kernels_row || 0 == m_kernels_col\n");
            m_p_kernels_features = NULL;
            return;
        }

        if (0 > m_kernels_features_row || 0 > m_kernels_features_col){
            DEBUG_PRINT("0 > m_kernels_row || 0 > m_kernels_col\n");
            m_p_kernels_features = NULL;
            return;
        }

        for (int i = 0; i < m_kernels_features_count; ++i){
            m_p_kernels_features[i] = matrix(m_kernels_features_row, m_kernels_features_col, min, max);
        }
        return;
    }

kernels::~kernels(){
    if (NULL == m_p_kernels_features){
        return;
    }

    if (m_kernels_features_count <= 0 || m_kernels_features_row <= 0 || m_kernels_features_col <= 0){
        return;
    }

    delete[] m_p_kernels_features;
    //for (int i = 0; i < m_kernels_count; ++i){
    //    DEBUG_PRINT("i=%d\n", i);
    //    delete (m_p_kernels + i);/* todo */
    //}
    //delete m_p_kernels;
    return;

}

bool kernels::show(int show_image_mode){
    if (0 >= m_kernels_features_row || 0 >= m_kernels_features_col){
        DEBUG_PRINT("bool kernels::show() \n \
            0 >= m_kernels_row || 0 >= m_kernels_col\n");
        return false;
    }

    if (0 >= m_kernels_features_count){
        DEBUG_PRINT("bool kernels::show()\n \
                                        0 >= m_kernels_count");
        return false;
    }

    for (int i = 0; i < m_kernels_features_count; ++i){
        DEBUG_PRINT("kernels %3d\n", i);
        m_p_kernels_features[i].show(show_image_mode);
    }

    return true;
}

kernels::kernels(const cv::Mat &image,DATA_TYPE translation, DATA_TYPE scale){
    //int img_channels = image.channels();
    this->m_kernels_features_count = image.channels();
    this->m_kernels_features_row = image.rows;
    this->m_kernels_features_col = image.cols;
    
    this->m_p_kernels_features = new matrix[m_kernels_features_count];

    if (NULL == m_p_kernels_features){
        DEBUG_PRINT("NULL == m_p_kernels\n");
        return;
    }

    for (int i = 0; i < m_kernels_features_count; ++i){
        m_p_kernels_features[i] = \
            matrix(m_kernels_features_row, m_kernels_features_col, DATA_TYPE(0.0));
    }
    
    int k = 0;
    switch (m_kernels_features_count)
    {
    case 1:
        //int k = -1;
        for (int i = 0; i < m_kernels_features_row; ++i){
            for (int j = 0; j < m_kernels_features_col; ++j){
                m_p_kernels_features[0].m_p_data[k] = \
                    DATA_TYPE((int)image.at<uchar>(i, j)) - translation;
                m_p_kernels_features[0].m_p_data[k] *= scale;
                ++k;
                //
            }
        }
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    default:
        break;
    }
    return;
}

bool kernels::features_2_matrix(){
    m_padding = VALID_PADDING;/* todo 初始化m_padding */
    switch (m_padding){
    case VALID_PADDING:
        int row = (m_kernels_features_row - m_ker)/* kernels_row features_row 分开定义 */
        m_feature_matrix_row = 0;
        break;
    case SAME_PADDING:/* todo */
        break;
    default:
        break;/*  todo */
    }

}