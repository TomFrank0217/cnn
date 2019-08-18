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
bool show(Mat &image, int show_image_mode = SHOW_IMAGE_SCALE_VALUE);
bool get_image_path_and_label(vector<num_path> &vec_path_label, string file_name);
bool show_layers_parameters(layer* players, int layers_count);
bool show_layer_parameters(layer* player);
int main(int argc, char* argv[]){
	string img_name = "F:\\chromeDownload\\trainimage\\pic2\\0\\0_0.bmp";
	Mat image = imread(img_name, 0);
	Mat img2;
	resize(image, img2, Size(32, 32), 0, 0, CV_INTER_LINEAR);
	int channels = img2.channels();
	int rows = img2.rows;
	int cols = img2.cols;

	layers lys(channels, rows, cols, layers_parameters, LAYERS_COUNTS);
	lys.mp_layers[0].m_fts = image;
	//lys.mp_layers[0].m_fts = features(channels, rows, cols, -1, 1);
	//lys.mp_layers[0].m_fts.show();
	//lys.mp_layers[0].m_kers = kernels(channels, 2, 2, 2, 0, 1);
	//lys.mp_layers[0].m_kers.show();
	//lys.mp_layers[2].m_kers = kernels(2, 2, 2, 3, 0, 1);
	//lys.show_shapes();
	lys.forward_propagation();
	lys.y.show();
	lys.q.show();
	
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

	string file_name = "F:\\chromeDownload\\trainimage\\pic2\\0\\*.bmp";
	std::cout << file_name << endl;
	vector<num_path> vec_path_label;
	get_image_path_and_label(vec_path_label, file_name);
	string str = "**************************************************************";
	for (int i = 0; i < vec_path_label.size(); ++i){
		std::cout << vec_path_label[i].path << endl;
		Mat image = imread(vec_path_label[i].path, 0);
		//show(image, SHOW_IMAGE_SHAPE);
		lys.mp_layers[0].m_fts = image;
		//lys.mp_layers[0].m_fts.show(SHOW_IMAGE_SHAPE);
		//features fts(image);
		//fts.show(SHOW_IMAGE_SHAPE);
		//std::cout << str << endl << str << endl << str << endl;
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
