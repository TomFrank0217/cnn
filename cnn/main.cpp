/******************************************************************************
****    Author:Hanzhi Fan                                                  ****
****    Date: 5th, Oct, 2019                                               ****
****    This a project to test my math(algorithm) and code.                ****
****    Hello, cnn.                                                        ****
*******************************************************************************/                    
#include <iostream>
#include <string>
#include <io.h>
#include <vector>
#include <algorithm> /* random_shuffle */
#include <iomanip>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "layers_parameters.h"

#include "matrix.h"
#include "features.h"
#include "kernels.h"
#include "layer.h"
#include "layers.h"

#include <windows.h>

using namespace cv;
using namespace std;

struct num_path{
    int num;
    string path;
};

bool get_files(string file_name, vector<string> &files);
bool show(Mat &image, int show_image_mode = SHOW_IMAGE_SHAPE);
bool get_image_path_and_label(vector<num_path> &vec_path_label, string file_name);
bool show_layers_parameters(layer* players, int layers_count);
bool show_layer_parameters(layer* player);
bool get_gt_label(int *gt_10, num_path& np);

int main(int argc, char* argv[]){
    /* todo random初始化不是很好 */
	/* 一般的卷积网络第一层都是卷积层,所以第一层默认卷积层，todo 第一层不是卷积层需要重新考虑*/
	/* 同样的，layers中实例化的所有参数都必须始终不能重新申请，否则系统会不停的申请释放内存，甚至是奔溃 */

	string  ttt = "*********************************************************************************************************************************************************************";
	string train_file_name = "F:\\chromeDownload\\trainimage\\pic2\\0\\*.bmp";
	string test_file_name = "F:\\chromeDownload\\test_image\\pic2\\0\\*.bmp";
	vector<num_path> train_path_label;
	vector<num_path> test_path_label;
	get_image_path_and_label(train_path_label, train_file_name);
	std::cout << "train_counts = "<<train_path_label.size() << std::endl;
	get_image_path_and_label(test_path_label, test_file_name);
	std::cout << "test_counts = " << test_path_label.size() << std::endl;
	for (int i = 0; i < test_path_label.size(); ++i){
		//std::cout << test_path_label[i].path << std::endl;
		;
	}
	Mat image = imread(train_path_label[0].path, 0);
	layers lys(image.channels(), image.rows, image.cols, layers_parameters, LAYERS_COUNTS);
	int gt_10[10] = { 0 };
	double accuracy[TEST_TIMES][11] = { 0.0 };
	DATA_TYPE base_learning_rate = 0.010;
	int rate_num = 100;
	DATA_TYPE learning_rate = 0;
	int mini_batches = 200;
	
	for (int i = 0; i < rate_num * TEST_TIMES; ++i){/* 是 i*mini_bathes=输入图像的总次数 */
		for (int k = 0; k < LAYERS_COUNTS; ++k){
			switch (lys.mp_layers[k].m_layer_mode){
			case FULLCONNECTION_LAYER:
			case CONVOLUTION_LAYER:
				lys.mp_layers[k].m_fts_diffs.reset(0.0);lys.mp_layers[k].m_fts_mat_diffs.reset(0.0);lys.mp_layers[k].m_kers_diffs.reset(0.0);
				lys.mp_layers[k].m_conv_mat_diffs.reset(0.0);lys.mp_layers[k].m_conv_relu_mat_diffs.reset(0.0);lys.mp_layers[k].m_conv_relu_mat2fts_diffs.reset(0.0);
				break;
			case POOLING_LAYER:
				lys.mp_layers[k].m_fts_diffs.reset(0.0);
				break;
			}
		}
		learning_rate = base_learning_rate*pow(0.96, i / rate_num);
		for ( int j = 0; j < mini_batches; ++j){
			get_gt_label(gt_10, train_path_label[(i*mini_batches + j) % train_path_label.size()]);
			image = imread(train_path_label[(i*mini_batches + j) % train_path_label.size()].path, 0);
            lys.mp_layers[0].m_fts = image;/* todo */
			lys.forward_propagation();
            if (i % 7 == 0){
                if (j % 58 == 0){
                    std::cout << "\n\niterations  " << i*mini_batches + j  << "   " << std::endl;
                    for (int sss = 0; sss < 10; ++sss){
						if (0 == gt_10[sss]){
							for (int kkk = 0; kkk < SHOW_PROBABILITY_WIDTH; ++kkk){
								std::cout << " ";
							}
						}
						else{
							for (int kkk = 0; kkk < SHOW_PROBABILITY_WIDTH - 2; ++kkk){
								std::cout << " ";
							}
							std::cout << sss << " ";
						}
                    }
                    std::cout << std::endl;
                    for (int sss = 0; sss < 10; ++sss){
                        if (0 == gt_10[sss]){
                            for (int kkk = 0; kkk < SHOW_PROBABILITY_WIDTH; ++kkk){
                                std::cout << " ";
                            }
                        }
                        else{
                            for (int kkk = 0; kkk < SHOW_PROBABILITY_WIDTH - 5; ++kkk){
                                std::cout << " ";
                            }
                            std::cout << "*****";
                        }
                    }//end sss
                    std::cout << std::endl;
                    for (int sss = 0; sss < 10; ++sss){
                        std::cout << setw(SHOW_PROBABILITY_WIDTH) << lys.y.mp_matrixes[sss].mp_data[0];
                    }
                    std::cout << std::endl;
                    for (int sss = 0; sss < 10; ++sss){
                        std::cout << setw(SHOW_PROBABILITY_WIDTH) << lys.t.mp_matrixes[sss].mp_data[0];
                    }
                    std::cout << std::endl;
                    for (int sss = 0; sss < 10; ++sss){
                        std::cout << setw(SHOW_PROBABILITY_WIDTH) << 100.0*lys.q.mp_matrixes[sss].mp_data[0];
                    }
                    std::cout << std::endl;
                }
            }//end i%50==0
			lys.back_propagation(gt_10);
			for (int k = LAYERS_COUNTS - 1; k >= 0; --k){
				switch (lys.mp_layers[k].m_layer_mode){
				case FULLCONNECTION_LAYER:
				case CONVOLUTION_LAYER:
					lys.mp_layers[k].m_fts_diffs += lys.mp_layers[k].m_fts_diff;
					lys.mp_layers[k].m_fts_mat_diffs += lys.mp_layers[k].m_fts_mat_diff;
					lys.mp_layers[k].m_kers_diffs += lys.mp_layers[k].m_kers_diff;
					lys.mp_layers[k].m_conv_mat_diffs += lys.mp_layers[k].m_conv_mat_diff;
					lys.mp_layers[k].m_conv_relu_mat_diffs += lys.mp_layers[k].m_conv_relu_mat_diff;
					lys.mp_layers[k].m_conv_relu_mat2fts_diffs += lys.mp_layers[k].m_conv_relu_mat2fts_diff;
					break;
				case POOLING_LAYER:
					lys.mp_layers[k].m_fts_diffs += lys.mp_layers[k].m_fts_diff;
					break;
				}
			}// end k
		}//end j mini_batches

		for (int k = 0; k < LAYERS_COUNTS; ++k){
			switch (lys.mp_layers[k].m_layer_mode){
			case FULLCONNECTION_LAYER:
			case CONVOLUTION_LAYER:
				lys.mp_layers[k].m_kers -= (learning_rate/mini_batches)*(lys.mp_layers[k].m_kers_diffs);
				break;
			case POOLING_LAYER: break;/* do nothing */
			}
		}
		int rate_num_x = rate_num;
		if (0 == i % (rate_num_x) /*&& 3 == j%mini_batches*/){
            std::cout << "\n\niterations  " << i*mini_batches << "   " << std::endl;
            std::cout << std::endl;
            for (int sss = 0; sss < 10; ++sss){
                std::cout << setw(SHOW_PROBABILITY_WIDTH - 1) << sss;
                std::cout << " ";
            }

            std::cout << std::endl;
            for (int sss = 0; sss < 10; ++sss){

                if (0 == gt_10[sss]){
                    for (int kkk = 0; kkk < SHOW_PROBABILITY_WIDTH; ++kkk){
                        std::cout << " ";
                    }
                }
                else{
                    for (int kkk = 0; kkk < SHOW_PROBABILITY_WIDTH - 5; ++kkk){
                        std::cout << " ";
                    }
                    std::cout << "*****";
                }
            }
            std::cout << std::endl;
            for (int sss = 0; sss < 10; ++sss){
				std::cout << setw(SHOW_PROBABILITY_WIDTH) << lys.y.mp_matrixes[sss].mp_data[0];
            }
            std::cout << std::endl;
            for (int sss = 0; sss < 10; ++sss){
				std::cout << setw(SHOW_PROBABILITY_WIDTH) << lys.t.mp_matrixes[sss].mp_data[0];
            }
            std::cout << std::endl;
            for (int sss = 0; sss < 10; ++sss){
				std::cout << setw(SHOW_PROBABILITY_WIDTH) << 100.0*lys.q.mp_matrixes[sss].mp_data[0];
            }
            std::cout << std::endl;


            int right[11] = { 0 };
            int counts[11] = { 0 };
            int n = test_path_label.size();
            for (int k = 0; k < n; ++k){
                ++counts[10];
                cv::Mat image = imread(test_path_label[k].path, 0);
                lys.mp_layers[0].m_fts = image;
                lys.forward_propagation();
                double max = lys.q.mp_matrixes[0].mp_data[0];
                int index = 0;
                for (int j = 1; j < 10; ++j){
                    if (max < lys.q.mp_matrixes[j].mp_data[0]){
                        max = lys.q.mp_matrixes[j].mp_data[0];
                        index = j;
                    }
                }
                ++counts[test_path_label[k].num];
                if (index == test_path_label[k].num){
                    ++right[test_path_label[k].num];
                }
            }
            right[10] = 0;
            for (int r = 0; r < 10; ++r){
                right[10] += right[r];
            }
            for (int r = 0; r < 11; ++r){
				accuracy[i / rate_num_x][r] = (0.0 + right[r]) \
                    / (0.0 + counts[r]);
            }
            std::cout << "******************************************************" << std::endl;
            std::cout << ttt << std::endl;
            for (int kkk = 0; kkk < 10; ++kkk){
                std::cout << setw(SHOW_PROBABILITY_WIDTH) << kkk;
                //std::cout << " ";
            }
            std::cout << std::endl;
			for (int t = 0; t <= i / rate_num_x; ++t){
                //for (int s = 0; s < 11; ++s){
                //    std::cout << setw(10) << right[s];
                //}
                //std::cout << std::endl;
                //for (int s = 0; s < 11; ++s){
                //    std::cout << setw(10) << counts[s];
                //}
                //std::cout << std::endl;
                for (int s = 0; s < 11; ++s){
					std::cout << setw(SHOW_PROBABILITY_WIDTH) << 100.0*accuracy[t][s];
                }
                std::cout << endl;
            }
			std::cout << std::endl << ttt << std::endl;
            std::cout << "******************************************************" << std::endl;
            int xxx = 0;
        }//end if (0 == i%rate_num)

	}// end i

    std::cout << std::endl << "****************************************************************************************************************" << std::endl;
	for (int i = 0; i < TEST_TIMES; ++i){
        for (int j = 0; j < 11; ++j){
            std::cout << setw(6) << 100.0*accuracy[i][j] << " ";
        }
        std::cout << endl;
	}
	std::cout << std::endl;
    std::cout << std::endl << "****************************************************************************************************************" << std::endl;
    return 0;
}


bool get_gt_label(int *gt_10, num_path& np){
	for (int s = 0; s < 10; ++s){
		if (s == np.num){
			gt_10[s] = 1;
		}
		else{
			gt_10[s] = 0;
		}
	}
	return true;
}
bool get_files(string file_name, vector<string> &files){
    _finddata_t file_info;
	//intptr_t handle = _findfirst(file_name.c_str(), &file_info);/* win7 */
	intptr_t handle = _findfirst(file_name.c_str(), &file_info);  /* win10 */
    //cout << file_name << endl;
    string full_name = file_name.substr(0, 36);
    //cout << full_name << endl;
    if (-1 == handle){
        cerr << "failed to transfer files" << endl;
        return false;
    }
	int i = -1;
    do{
        //cout << file_info.name << endl;
        files.push_back(full_name + file_info.name);
		//cout << files[++i] << endl;
		//Mat image = imread(files[i], 0);
		//cout << image.rows << "   " << image.cols << endl;
		//imshow("000000",image);
		//waitKey(100);
	} while (0== _findnext(handle, &file_info));

    return true;
}

bool show(Mat &image, int show_image_mode){
    //namedwindow(window_name,1);
	//imshow(window_name, image);//显示图片
    //waitKey(100);
    int num = 0;
    string str;
    switch (show_image_mode)
    {
    case SHOW_IMAGE_SHAPE:
        
        for (int i = SHOW_IMAGE_CROP_LENGTH; i < image.rows - SHOW_IMAGE_CROP_LENGTH; ++i){
            for (int j = SHOW_IMAGE_CROP_LENGTH; j < image.cols - SHOW_IMAGE_CROP_LENGTH; ++j){
                if (0 == int(image.at<uchar>(i, j)))
					std::cout << "  ";
                else
					std::cout << "**";
            }
			std::cout << endl;
        }
        break;

    case SHOW_IMAGE_SCALE_VALUE:
        
        for (int k = 0; k < SHOW_WIDTH; ++k){
            str += " ";
        }
        for (int i = SHOW_IMAGE_CROP_LENGTH; i < image.rows - SHOW_IMAGE_CROP_LENGTH; ++i){
            for (int j = SHOW_IMAGE_CROP_LENGTH; j < image.cols - SHOW_IMAGE_CROP_LENGTH; ++j){
                if (0 == (int)image.at<uchar>(i, j)){
					std::cout << str;
                }
                else{
                    std::cout << setw(SHOW_WIDTH) << (int)image.at<uchar>(i, j);
                }
            }
			std::cout << endl;
        }
        break;
    default:    
        return false;
    }
    
    return true;
}

bool get_image_path_and_label(vector<num_path> &vec_path_label, string file_name){
    vector<string> num_file;
    vector<vector<string> > num_files;
    /*                                                        35              */
    vector<string> file_names;
    int num_counts = 0;
    //for (int i = 0; i < 10; ++i){    /* todo */
    for (int i = 0; i < 10; ++i){    /* todo */
        file_name[34] = '0' + i;
		std::cout << file_name << endl;
        file_names.push_back(file_name);
        get_files(file_name, num_file);
        std::cout << i << " num_file= " << num_file.size() << std::endl;
        num_files.push_back(num_file);
        num_counts += num_files[i].size();
        num_file.clear();
    }
    
    vec_path_label.resize(num_counts);
    //vector<num_path> image_label(num_counts);
    int k = -1;
    for (int i = 0; i < num_files.size(); ++i){
        int n = num_files[i].size();
        for (int j = 0; j < n; ++j){
            vec_path_label[++k] = num_path{ i, num_files[i][j] };
            //cout << image_label[k].num << " " << image_label[k].path << endl;
        }
    }
    random_shuffle(vec_path_label.begin(), vec_path_label.end());
    //cout << " images_labels= " << image_label.size() << endl;
    //Mat image;
    //for (int i = 0; i < image_label.size(); ++i){
    //    if (0 == i % 10){
    //        Mat image = imread(image_label[i].path, 0);
    //        //cout << "i=" << setw(8) << i << "   " << image_label[i].num \
    //                                    << "   " << image_label[i].path << endl;
    //        //show(image_label[i].path);
    //        //cout<< "############\n";
    //    }
    //}

    return true;
}
