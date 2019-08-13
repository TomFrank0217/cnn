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
#include "tensor.h"
#include "kernels.h"
#include "features.h"
#include "layer.h"

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
	//matrix A(3, 3, -3, 3);
 //   matrix B(3, 3, -5, 3);
 //   matrix C = 1 - A;
 //   A.show(SHOW_IMAGE_INITAIL_VALUE);
 //   B.show(SHOW_IMAGE_INITAIL_VALUE);
	//C.show(SHOW_IMAGE_INITAIL_VALUE);

	//{
	//	tensor ts(5, 3, 3, -2, 2);
	//	ts.show(SHOW_IMAGE_INITAIL_VALUE);
	//	tensor ts1;
	//	ts1 = ts;
	//	ts1.show();
	//}

	{
		//features fs(3, 5, 6, 0, 9);
		//fs.show(SHOW_IMAGE_INITAIL_VALUE);
		//fs.reshape(FEATURES2MATRIX);
		//fs.m_features_matrix.show(SHOW_IMAGE_INITAIL_VALUE);

		//fs.reshape(MATRIX2FEATURES);
		//fs.m_tensor.show(SHOW_IMAGE_INITAIL_VALUE);
		//features fs1;
		//fs1 = fs;
		//fs1.show();
	}

	{
		//kernels kers(2, 3, 3, 4, -2, 2);
		////kers.reshape();
		//kers.show(SHOW_IMAGE_INITAIL_VALUE, KERNELS2MATRIEX);
		//kers.show(SHOW_IMAGE_INITAIL_VALUE, MATRIEX2KERNELS);
		//kernels k2 = kers;
		//k2 = kers;
		//k2.show(SHOW_IMAGE_INITAIL_VALUE, MATRIEX2KERNELS);
		//cout << endl;
		//cout << kers.m_channels << "  " << kers.m_rows << "  "\
		//	<< kers.m_cols << "  " << kers.m_kernels_count << endl;
		//for (int i = 0; i < kers.m_kernels_count; ++i){
		//	cout << "kernel " << i << endl;
		//	cout << kers.mp_tensors[i].m_channels << "  " \
		//		<< kers.mp_tensors[i].m_rows << "  " << kers.mp_tensors[i].m_cols;
		//	cout << endl;
		//	(kers.mp_tensors[i]).show(SHOW_IMAGE_INITAIL_VALUE);
		//}
	}
    {
        //layer(kers_channels,kers_rows,kers_cols,kers_count,fts_channels/*kers_channels*/,fts_rows, fts_cols);
		layer ly(2, 2, 2, 3, 2, 5, 8);
        ly.fts.show(SHOW_IMAGE_INITAIL_VALUE);
        //bool reshape(int mode = FEATURES2MATRIX, int kernels_rows = KERNEL_ROWS, \
        //    int kernels_cols = KERNEL_COLS, int stride = 1, int padding_mode = VALID_PADDING);
        ly.fts.reshape(FEATURES2MATRIX, ly.kers.m_rows, ly.kers.m_cols, 1, VALID_PADDING);

        ly.kers.show(SHOW_IMAGE_INITAIL_VALUE, KERNELS2MATRIEX);
        ly.kers.reshape(KERNELS2MATRIEX);

        matrix m = ly.conv();
		m.show(SHOW_IMAGE_INITAIL_VALUE);

		ly.reshape(MATRIX2FEATURES);
		//ly.conv_matrix_fts.show(SHOW_IMAGE_INITAIL_VALUE);
		ly.reshape(FEATURES2MATRIX);
		ly.conv_matrix.show();
    }
    int x = 0;
 //   string file_name = "F:\\chromeDownload\\trainimage\\pic2\\0\\*.bmp";
	//cout << file_name << endl;
 //   vector<num_path> vec_path_label;
 //   get_image_path_and_label(vec_path_label, file_name);
	//string str = "**************************************************************";
 //   for (int i = 0; i < vec_path_label.size(); ++i){
 //       cout << vec_path_label[i].path << endl;
 //       Mat image = imread(vec_path_label[i].path,0);
	//	show(image, SHOW_IMAGE_SHAPE);
	//	features fea(image);
	//	fea.show(SHOW_IMAGE_SHAPE);
	//	kernels ker(image);
	//	ker.show(SHOW_IMAGE_SHAPE);
	//	cout << str << endl << str << endl << str << endl;
 //   }

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
	//int i = -1;
    do{
        //cout << file_info.name << endl;
        files.push_back(full_name + file_info.name);
		//cout << files[++i] << endl, Mat image = imread(files[i], 0);
		
		//cout << image.rows << "   " << image.cols << endl;
		//imshow("000000",image);
		//waitKey(100);
		int todo = 0;
	} while (0== _findnext(handle, &file_info));

    return true;
}

bool show(Mat &image, int show_image_mode){
    //namedwindow(window_name,1);
	//imshow(window_name, image);//ÏÔÊ¾Í¼Æ¬
    //waitKey(100);
    int num = 0;
    string str;
    switch (show_image_mode)
    {
    case SHOW_IMAGE_SHAPE:
        
        for (int i = SHOW_IAMGE_CROP_LENGTH; i < image.rows - SHOW_IAMGE_CROP_LENGTH; ++i){
            for (int j = SHOW_IAMGE_CROP_LENGTH; j < image.cols - SHOW_IAMGE_CROP_LENGTH; ++j){
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
        for (int i = SHOW_IAMGE_CROP_LENGTH; i < image.rows - SHOW_IAMGE_CROP_LENGTH; ++i){
            for (int j = SHOW_IAMGE_CROP_LENGTH; j < image.cols - SHOW_IAMGE_CROP_LENGTH; ++j){
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


