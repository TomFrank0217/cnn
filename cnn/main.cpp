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

#include "matrix.h"
#include "kernels.h"
#include "features.h"
#include "layer.h"
#include "layers_parameters.h"

using namespace cv;
using namespace std;

struct num_path{
    int num;
    string path;
};

bool get_files(string file_name, vector<string> &files);
bool show(Mat &image, int show_image_mode = SHOW_IMAGE_SCALE_VALUE);
bool get_image_path_and_label(vector<num_path> &vec_path_label, string file_name);
bool show_layers_parameters(layer* players, int layers_count);
bool show_layer_parameters(layer* player);
int main(int argc, char* argv[]){
	string img_name = "F:\\chromeDownload\\trainimage\\pic2\\0\\0_0.bmp";
	Mat image = imread(img_name, 0);  
	int channels = image.channels();
	int rows = image.rows;
	int cols = image.cols;

    int layers_counts = sizeof(layers_parameters[0]);
    /* 一般的卷积网络第一层都是卷积层,所以第一层默认卷积层，todo 第一层不是卷积层需要重新考虑*/
	layer* players = new layer[LAYERS_COUNTS], *t = NULL;
    //layer(int kers_channels, int kers_rows, int kers_cols, int kers_count, \
        int fts_channels/*kers_channels*/, int fts_rows, int fts_cols);
 //   players[0] = layer(layers_parameters[0].kernel_channels, \
 //       layers_parameters[0].kernel_rows, layers_parameters[0].kernel_cols, \
 //       layers_parameters[0].kernel_counts, \
 //       input_channels, input_rows, input_cols);

 //   /* todo 此处初始化必须重新写一个函数，否则每一个图像初始化都需要申请内存 这个不行 */
 //   players[0].m_fts = features(image);
	//players[0].layer_mode = layers_parameters[0].layer_mode;
	//players[0].pooling_size = layers_parameters[0].pooling_size;
	//players[0].relu = layers_parameters[0].relu;
	//players[0].stride = 1;
	players[0] = layer(channels, rows, cols, layers_parameters);
	std::cout << "第 " << "1" << "层:" << std::endl;
	show_layer_parameters(players);
    /* 同样的，layers中实例化的所有参数都必须始终不能重新申请，否则系统会不停的申请释放内存，甚至是奔溃 */
	

    for (int i = 1; i < LAYERS_COUNTS; ++i){
        //std::cout << layers_parameters[i].kernel_channels << std::endl;
		players[i].m_stride = layers_parameters[i].stride;
		int channels = 0;
		int rows = 0;
		int cols = 0;
		int P = 0;/* valid padding */
		switch (layers_parameters[i-1].layer_mode){
		case POOLING_LAYER:
			t = players + i - 1;
			players[i] = layer(t->m_fts.m_channels, t->m_fts.m_rows / POOLING_SIZE, \
				t->m_fts.m_cols / POOLING_SIZE, layers_parameters + i);

			/* todo 此处只实现了max_pooling average pooling未实现 */
			/* 此处假设是最大值pooling */
			//players[i] = layer(0, 0, 0, 0, players[i - 1].m_conv_relu_mat2fts.m_channels, \
			//	players[i - 1].m_conv_relu_mat2fts.m_rows, \
			//	players[i - 1].m_conv_relu_mat2fts.m_cols);
			//players[i].layer_mode = layers_parameters[i].layer_mode;
			//players[i].pooling_size = layers_parameters[i].pooling_size;
			//players[i].relu = layers_parameters[i].relu;
			//players[i].stride = 1;
			/* todo layeri中features的初始化 image i-1 out features 需要重新写*/
			break;
		case CONVOLUTION_LAYER:
			t = players + i - 1;
			channels = t->m_conv_mat.m_cols;
			rows = t->m_fts.m_rows - t->m_kers.m_rows;
			cols = t->m_fts.m_cols - t->m_kers.m_cols;
			
			if (SAME_PADDING == t->m_padding_mode){
				P = (t->m_kers.m_rows - 1) / 2;
			}
			rows = (rows + 2 * P) / t->m_stride + 1;
			cols = (cols + 2 * P) / t->m_stride + 1;
			players[i] = layer(channels, rows, cols, layers_parameters + i);
			break;
		case FULLCONNECTION_LAYER:
			t = players + i - 1;
			channels = t->m_conv_mat.m_cols;
			rows = t->m_fts.m_rows - t->m_kers.m_rows;
			cols = t->m_fts.m_cols - t->m_kers.m_cols;

			rows = rows / t->m_stride + 1;
			cols = cols / t->m_stride + 1;
			players[i] = layer(channels, rows, cols, layers_parameters + i);
			break;
		default:;
			break;
		}
		std::cout << std::endl;
		std::cout << "第 " << i + 1 << "层:" << std::endl;
		show_layer_parameters(players + i);
		int xxx = 0;
    }
    //std::cout << layers_counts << std::endl;
	show_layers_parameters(players, LAYERS_COUNTS);
	string file_name = "F:\\chromeDownload\\trainimage\\pic2\\0\\*.bmp";
	std::cout << file_name << endl;
	vector<num_path> vec_path_label;
	get_image_path_and_label(vec_path_label, file_name);
	string str = "**************************************************************";
	for (int i = 0; i < vec_path_label.size(); ++i){
		std::cout << vec_path_label[i].path << endl;
		Mat image = imread(vec_path_label[i].path, 0);
		show(image, SHOW_IMAGE_SHAPE);
		features fea(image);
		fea.show(SHOW_IMAGE_SHAPE);
		features fts(image);
		fts.show(SHOW_IMAGE_SHAPE);
		std::cout << str << endl << str << endl << str << endl;
	}

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

bool show_layers_parameters(layer* players, int layers_count){
    if (NULL == players || 0 >= layers_count){
        return false;
    }
    for (int i = 0; i < layers_count; i++){
        std::cout << "第 " << i << " 层参数 " << std::endl;
        show_layer_parameters(players + i);
        std::cout << std::endl;
    }
}

bool show_layer_parameters(layer* player){
    if (NULL == player){
        return false;
    }
    switch (player->m_layer_mode)
    {
    case POOLING_LAYER:
        std::cout << "POOLING LAYER\n";
		break;
    case CONVOLUTION_LAYER:
        std::cout << "CONVOLUTION_LAYER\n";
		break;
    case FULLCONNECTION_LAYER:
        std::cout << "FULLCONNECTION_LAYER\n";
		break;
    default:
        break;
    }
	std::cout << "features parameters" << endl;
	std::cout << "channels:" << (player->m_fts).m_channels << "  ";
	std::cout << "rows:" << (player->m_fts).m_rows << "  ";
	std::cout << "cols:" << (player->m_fts).m_cols << "  " << std::endl;
    std::cout << "kernels parameters" << endl;
    std::cout << "channels:" << (player->m_kers).m_channels << "  ";
	std::cout << "kernel_rows:" << (player->m_kers).m_rows << "  ";
	std::cout << "kernel_cols:" << (player->m_kers).m_cols << "  ";
	std::cout << "kernel_counts:" << (player->m_kers).m_kers_counts << "  " << std::endl;
    switch (player->m_relu)
    {
    case RELU_OFF:
        std::cout << "RELU_OFF" << std::endl;
		break;
    case RELU_ON:
        std::cout << "RELU_ON" << std::endl;
		break;
    default: 
        break;
    }

    std::cout << "POOLING SIZE:" << player->m_pooling_size << std::endl;
    return true;
}
