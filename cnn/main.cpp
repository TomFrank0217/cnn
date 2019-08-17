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

int main(int argc, char* argv[]){
	string img_name = "F:\\chromeDownload\\trainimage\\pic2\\0\\0_0.bmp";
	Mat image = imread(img_name, 0);  
	int input_channels = image.channels();
	int input_rows = image.rows;
	int input_cols = image.cols;

    int layers_counts = sizeof(layers_parameters[0]);
    /* һ��ľ�������һ�㶼�Ǿ����,���Ե�һ��Ĭ�Ͼ���㣬todo ��һ�㲻�Ǿ������Ҫ���¿���*/
    layer* players = new layer[LAYERS_COUNTS];
    //layer(int kers_channels, int kers_rows, int kers_cols, int kers_count, \
        int fts_channels/*kers_channels*/, int fts_rows, int fts_cols);
    players[0] = layer(layers_parameters[0].kernel_channels, \
        layers_parameters[0].kernel_rows, layers_parameters[0].kernel_cols, \
        layers_parameters[0].kernel_counts, \
        input_channels, input_rows, input_cols);

    /* todo �˴���ʼ����������дһ������������ÿһ��ͼ���ʼ������Ҫ�����ڴ� ������� */
    players[0].m_fts = features(image);
    /* ͬ���ģ�layers��ʵ���������в���������ʼ�ղ����������룬����ϵͳ�᲻ͣ�������ͷ��ڴ棬�����Ǳ��� */
    for (int i = 1; i < LAYERS_COUNTS; ++i){
        std::cout << layers_parameters[i].kernel_channels << std::endl;
        switch (layers_parameters[0].layer_mode){
        case POOLING_LAYER:
            /* todo �˴�ֻʵ����max_pooling average poolingδʵ�� */
            /* �˴����������ֵpooling */
            players[i] = layer(0, 0, 0, 0, players[i - 1].m_conv_relu_mat2fts.m_channels, \
                players[i - 1].m_conv_relu_mat2fts.m_rows, \
                players[i - 1].m_conv_relu_mat2fts.m_cols);
            /* todo layeri��features�ĳ�ʼ�� image i-1 out features ��Ҫ����д*/
            break;
        case CONVOLUTION_LAYER:
            players[i] = layer(players[i - 1].m_conv_relu_mat2fts.m_channels, \
                players[i - 1].m_conv_relu_mat2fts.m_rows, \
                players[i - 1].m_conv_relu_mat2fts.m_cols, \
                layers_parameters[i].kernel_channels, \
                layers_parameters[i].kernel_rows, \
                layers_parameters[i].kernel_cols, layers_parameters[i].kernel_counts);
            break;
        case FULLCONNECTION_LAYER:
            players[i] = layer(players[i - 1].m_conv_relu_mat2fts.m_channels, \
                players[i - 1].m_conv_relu_mat2fts.m_rows, \
                players[i - 1].m_conv_relu_mat2fts.m_cols, \
                layers_parameters[i].kernel_channels, \
                layers_parameters[i].kernel_rows, \
                layers_parameters[i].kernel_cols, layers_parameters[i].kernel_counts);
            break;
        default:   ;
            break;
        }
    }
    //std::cout << layers_counts << std::endl;

	string file_name = "F:\\chromeDownload\\trainimage\\pic2\\0\\*.bmp";
	cout << file_name << endl;
	vector<num_path> vec_path_label;
	get_image_path_and_label(vec_path_label, file_name);
	string str = "**************************************************************";
	for (int i = 0; i < vec_path_label.size(); ++i){
		cout << vec_path_label[i].path << endl;
		Mat image = imread(vec_path_label[i].path, 0);
		show(image, SHOW_IMAGE_SHAPE);
		features fea(image);
		fea.show(SHOW_IMAGE_SHAPE);
		features fts(image);
		fts.show(SHOW_IMAGE_SHAPE);
		cout << str << endl << str << endl << str << endl;
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
	//imshow(window_name, image);//��ʾͼƬ
    //waitKey(100);
    int num = 0;
    string str;
    switch (show_image_mode)
    {
    case SHOW_IMAGE_SHAPE:
        
        for (int i = SHOW_IMAGE_CROP_LENGTH; i < image.rows - SHOW_IMAGE_CROP_LENGTH; ++i){
            for (int j = SHOW_IMAGE_CROP_LENGTH; j < image.cols - SHOW_IMAGE_CROP_LENGTH; ++j){
                if (0 == int(image.at<uchar>(i, j)))
                    cout << "  ";
                else
                    cout << "**";
            }
            cout << endl;
        }
        break;

    case SHOW_IMAGE_SCALE_VALUE:
        
        for (int k = 0; k < SHOW_WIDTH; ++k){
            str += " ";
        }
        for (int i = SHOW_IMAGE_CROP_LENGTH; i < image.rows - SHOW_IMAGE_CROP_LENGTH; ++i){
            for (int j = SHOW_IMAGE_CROP_LENGTH; j < image.cols - SHOW_IMAGE_CROP_LENGTH; ++j){
                if (0 == (int)image.at<uchar>(i, j)){
                    cout << str;
                }
                else{
                    std::cout << setw(SHOW_WIDTH) << (int)image.at<uchar>(i, j);
                }
            }
            cout << endl;
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
		cout << file_name << endl;
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


