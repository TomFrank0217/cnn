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
int main(int argc, char* argv[]){
    /* todo random初始化不是很好 */
	string img_name = "F:\\chromeDownload\\trainimage\\pic2\\0\\0_0.bmp";
	Mat image = imread(img_name, 0);
	int channels = image.channels();
	int rows = image.rows;
	int cols = image.cols;
    int test_10[10] = { 1, 0, 0 };
	layers lys(1, 32, 32, layers_parameters, LAYERS_COUNTS);
	lys.mp_layers[0].m_fts = image;
	//lys.mp_layers[0].m_fts = features(channels, rows, cols, -1, 1);
	//lys.mp_layers[0].m_fts.show();
	//lys.mp_layers[0].m_kers = kernels(channels, 2, 2, 2, 0, 1);
	//lys.mp_layers[0].m_kers.show();
	//lys.mp_layers[2].m_kers = kernels(2, 2, 2, 3, 0, 1);
	//lys.show_shapes();

	string file_name = "F:\\chromeDownload\\trainimage\\pic2\\0\\*.bmp";
	std::cout << file_name << endl;
	vector<num_path> vec_path_label;
	get_image_path_and_label(vec_path_label, file_name);
	//string str = "**************************************************************";
	//for (int i = 0; i < vec_path_label.size(); ++i){
	//	std::cout << vec_path_label[i].path << endl;
	//	Mat image = imread(vec_path_label[i].path, 0);
	//	//show(image, SHOW_IMAGE_SHAPE);
	//	lys.mp_layers[0].m_fts = image;
	//}
	std::cout << vec_path_label.size() << std::endl;
	for (int i = 0; i < vec_path_label.size(); ++i){
		std::cout << vec_path_label[i].path << "  " << vec_path_label[i].num << std::endl;
	}
	DATA_TYPE base_rate = RANDOM_INITIAL_VAL * 15;
	int rate_num = 500;
	DATA_TYPE rate = 0;
	int mini_batches = 1;
	for (int i = 0; i < 1000000; ++i){
		
		for (int k = 0; k < LAYERS_COUNTS; ++k){
			//image = imread(img_name, 0);
			//lys.mp_layers[0].m_fts = image;
			switch (lys.mp_layers[k].m_layer_mode)
			{
			case FULLCONNECTION_LAYER:
			case CONVOLUTION_LAYER:
				lys.mp_layers[k].m_fts_diffs.reset(0.0);
				lys.mp_layers[k].m_fts_mat_diffs.reset(0.0);
				lys.mp_layers[k].m_kers_diffs.reset(0.0);
				lys.mp_layers[k].m_conv_mat_diffs.reset(0.0);
				lys.mp_layers[k].m_conv_relu_mat_diffs.reset(0.0);
				lys.mp_layers[k].m_conv_relu_mat2fts_diffs.reset(0.0);
				break;
			case POOLING_LAYER:
				lys.mp_layers[k].m_fts_diffs.reset(0.0);
				break;
			default:
				break;
			}
		}

		rate = base_rate*pow(0.2, i / rate_num);
		for (int j = 0; j < mini_batches; ++j){
			std::cout << "\n\niterations  " << i*mini_batches + j << std::endl;
			image = imread(vec_path_label[(i*mini_batches + j) % vec_path_label.size()].path, 0);
			//show(image);
			lys.mp_layers[0].m_fts = image;
			//lys.mp_layers[0].m_fts.show(SHOW_IMAGE_SHAPE);
			for (int s = 0; s < 10; ++s){
				if (s == vec_path_label[(i*mini_batches + j) % vec_path_label.size()].num){
					test_10[s] = 1;
				}
				else{
					test_10[s] = 0;
				}
			}
			std::cout << "mini bacth " << j << std::endl;
			std::cout << vec_path_label[(i*mini_batches + j) % vec_path_label.size()].path << "    " \
				<< vec_path_label[(i*mini_batches + j) % vec_path_label.size()].num << std::endl;
			cout << endl;
			lys.mp_layers[0].m_fts = image;
			lys.forward_propagation();
			//lys.back_propagation();
			for (int sss = 0; sss < 10; ++sss){
				std::cout << setw(10) << sss;
			}
			std::cout << std::endl;
			for (int sss = 0; sss < 10; ++sss){
				std::cout << setw(10) << test_10[sss];
			}
			std::cout << std::endl;
			for (int sss = 0; sss < 10; ++sss){
				std::cout << setw(10) << lys.y.mp_matrixes[sss].mp_data[0];
			}
			std::cout << std::endl;
			for (int sss = 0; sss < 10; ++sss){
				std::cout << setw(10) << lys.t.mp_matrixes[sss].mp_data[0];
			}
			std::cout << std::endl;
			for (int sss = 0; sss < 10; ++sss){
				std::cout << setw(10) /*<< setprecision(6)*/ << lys.q.mp_matrixes[sss].mp_data[0] * 100.0;
			}
			std::cout << std::endl;
			lys.back_propagation(test_10);
			for (int k = LAYERS_COUNTS - 1; k >= 0; --k){
				switch (lys.mp_layers[k].m_layer_mode)
				{
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
				default:
					break;
				}
			}//end mini_batch
			int xxx = 0;
			for (int k = 0; k < LAYERS_COUNTS; ++k){
				switch (lys.mp_layers[k].m_layer_mode)
				{
				case FULLCONNECTION_LAYER:
				case CONVOLUTION_LAYER:
					//lys.mp_layers[k].m_fts += rate*lys.mp_layers[k].m_fts_diffs;
					//lys.mp_layers[k].m_fts_mat += rate*lys.mp_layers[k].m_fts_mat_diffs;
					//rate*lys.mp_layers[k].m_kers_diffs.show();
					//lys.mp_layers[k].m_kers.show();
					lys.mp_layers[k].m_kers += (rate/mini_batches)*lys.mp_layers[k].m_kers_diffs;
					//lys.mp_layers[k].m_kers.show();
					//lys.mp_layers[k].m_conv_mat += rate*lys.mp_layers[k].m_conv_mat_diffs;
					//lys.mp_layers[k].m_conv_relu_mat += rate*lys.mp_layers[k].m_conv_relu_mat_diffs;
					//lys.mp_layers[k].m_conv_relu_mat2fts += rate*lys.mp_layers[k].m_conv_relu_mat2fts_diffs;
					break;
				case POOLING_LAYER:
					//lys.mp_layers[k].m_fts += rate*lys.mp_layers[k].m_fts_diffs;
					break;
				default:
					break;
				}
			}
		}//end mini_batches
		//std::cout << vec_path_label[i*mini_batches + mini_batches - 1].path << "    " \
			<< vec_path_label[i*mini_batches + mini_batches - 1].num << std::endl;

		//lys.q.show();
		int xxx = 0;
	}
	int xxx = 0;
	//lys.mp_layers[0].m_fts.show();
	//lys.mp_layers[0].m_kers.show();
	//lys.mp_layers[0].m_conv_mat.show();
	//lys.mp_layers[0].reshape(lys.mp_layers[0].m_conv_mat, lys.mp_layers[0].m_conv_relu_mat2fts);
	//lys.mp_layers[0].m_conv_relu_mat2fts.show();
	//lys.mp_layers[0].reshape(lys.mp_layers[0].m_relu_mask, lys.mp_layers[0].m_conv_relu_mat2fts);
	//lys.mp_layers[0].m_conv_relu_mat2fts.show();
	//lys.mp_layers[1].m_fts.show();
	//lys.mp_layers[1].m_pooling_mask.show();
	//lys.mp_layers[2].m_fts.show();
	//lys.mp_layers[2].m_kers.show();
	//lys.y.show();
	//lys.mp_layers[3].m_fts = features(1, 6, 10, -5, 5);
	//lys.mp_layers[3].m_fts.show();
	//lys.mp_layers[3].m_pooling_mask = features(1, 6, 10);
	//lys.mp_layers[4].m_fts = features(1, 3, 5);
	//lys.mp_layers[3].reshape(lys.mp_layers[3].m_pooling_mask, lys.mp_layers[4].m_fts);
	//lys.mp_layers[3].m_pooling_mask.show();
	//lys.mp_layers[4].m_fts.show();
    /* 一般的卷积网络第一层都是卷积层,所以第一层默认卷积层，todo 第一层不是卷积层需要重新考虑*/
 // /* todo 此处初始化必须重新写一个函数，否则每一个图像初始化都需要申请内存 这个不行 */
    /* 同样的，layers中实例化的所有参数都必须始终不能重新申请，否则系统会不停的申请释放内存，甚至是奔溃 */

    return 0;
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
		//int todo = 0;
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
