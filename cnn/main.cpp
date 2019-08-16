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
//#include "layers_parameters.cpp"

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

    //int layers_counts = sizeof(layers_parameters[0]);
    //for (int i = 0; i < LAYERS_COUNTS; ++i){
    //    std::cout << layers_parameters[i].kernel_channels << std::endl;
    //}
    //std::cout << layers_counts << std::endl;
    int xxx = 0;
	{
		//matrix A(3, 3, 0, 1);
		//matrix B(3, 3, 0, 1);
		//A.show(SHOW_IMAGE_INITAIL_VALUE);
		//A += 2;
		//A.show(SHOW_IMAGE_INITAIL_VALUE);
		//A -= 2;
		//A.show(SHOW_IMAGE_INITAIL_VALUE);
		//A *= 2;
		//A.show(SHOW_IMAGE_INITAIL_VALUE);
		//B.show(SHOW_IMAGE_INITAIL_VALUE);
		//matrix C = A*B;
		//C = C;
		//C = A * 5;
		////C.show(SHOW_IMAGE_INITAIL_VALUE);
		//int xx = 0;
		//matrix C(3, 3);
		//for (int i = 0; i < 10000; i++){
		//	matrix AA = C;
		//	//if (NULL != AA.mp_data){
		//	//	std::cout << i << std::endl;
		//	//	std::cout << AA.mp_data << std::endl;
		//	//}
		}
	int xyz = 0;
	//}
	{//todo
		//features fs(1, 3, 2, -1, 2);
		//fs.show(SHOW_IMAGE_INITAIL_VALUE);
		//
		//(fs * 2).show();
		//(2 * fs).show();
		//fs *= 2;
		//fs.show();
  //      fs = fs - 1;
  //      fs.show(SHOW_IMAGE_INITAIL_VALUE);
  //      fs -= 1;
  //      fs.show(SHOW_IMAGE_INITAIL_VALUE);
		//fs = 1 - fs;
  //      fs.show(SHOW_IMAGE_INITAIL_VALUE);
  //      features f2(fs);
  //      f2 -= fs;
  //      f2.show(SHOW_IMAGE_INITAIL_VALUE);
  //      f2 = fs - f2;/* 此处指针视乎可以优化 */
		//f2.show(SHOW_IMAGE_INITAIL_VALUE);
	}
	int xy = 0;
	int y = 0;
	{
		kernels kers(2, 2, 2, 2, -2, 2);
		//kers.reshape();
		kers.show(SHOW_IMAGE_INITAIL_VALUE);
		//kers.show(SHOW_IMAGE_INITAIL_VALUE);
		kernels k2 = 2 * kers + 1;
		k2.show(SHOW_IMAGE_INITAIL_VALUE);
		k2 = k2 * 2;
		k2.show();
		cout << endl;
		//kernels operator+(DATA_TYPE add_num);//matrix operator+(DATA_TYPE addition_num);
		//bool operator+=(DATA_TYPE add_num);//bool operator+=(DATA_TYPE addition_num);
		//friend kernels operator+(const DATA_TYPE add_num, const kernels &add_kernels);//friend matrix operator+(const DATA_TYPE val, const matrix &add_matrix);
		//kernels operator+(const kernels &add_features);//matrix operator+(const matrix &add_matrix);
		//bool operator+=(const kernels& add_features);//bool operator+=(const matrix&add_matrix);

		//kernels operator-(DATA_TYPE minus_num);
		//bool operator-=(DATA_TYPE minus_num);
		//friend kernels operator-(const DATA_TYPE minus, const kernels &minus_kernels);
		//kernels operator-(const kernels &minus_kernels);
		//bool operator-=(const kernels& minus_kernels);

		//friend kernels operator*(const DATA_TYPE scale, const kernels &mutiplier_kernels);
		//kernels operator*(const DATA_TYPE scale);
		//bool operator*=(const DATA_TYPE scale);
		int x = 0;
	}
	{
		//layer(kers_channels,kers_rows,kers_cols,kers_count,fts_channels/*kers_channels*/,fts_rows, fts_cols);
		//      ly.m_kers.show();
		////bool layer::reshape(kernels& src_kers, matrix& dst_kers_mat)
		//ly.reshape(ly.m_kers, ly.m_kers_mat);
		//ly.m_kers_mat.show();
		//kernels kkk;
		//ly.reshape_(ly.m_kers_mat, kkk);
		//kkk.show();

		//ly.m_fts.show();
		//ly.m_kers.show();
		//ly.conv();
		//ly.m_conv_mat.show();
		//ly.reshape(ly.m_conv_mat, ly.m_conv_mat2fts);
		//ly.m_conv_mat2fts.show();
		//matrix xxxx;
		//ly.reshape_(ly.m_conv_mat2fts, xxxx);
		//xxxx.show();

		//int channels = 2;
		//layer ly(channels, 2, 2, 1, channels, 3, 3);
		//ly.m_fts.show();
		//ly.reshape(ly.m_fts, ly.m_fts_mat);
		//ly.m_fts_mat.show();
		//ly.reshape_(ly.m_fts_mat, ly.m_fts);
		//ly.m_fts.show(SHOW_IMAGE_INITAIL_VALUE);
		// ly.m_fts_mat.show();
		//.reshape_(ly.m_fts_mat, fff);
		//ly.reshape_(ly.m_fts_mat, ly.m_fts);
		//fff.show();
	
		//fff.show();
		//ly.reshape(matrix2features);
		//ly.conv_matrix_fts.show(show_image_initail_value);
		//ly.reshape(features2matrix);
		//ly.conv_matrix.show();

    }
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


