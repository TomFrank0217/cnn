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
bool get_image_path_and_label(vector<vector<num_path>>& label_imgs, vector<num_path> &vec_path_label, string file_name);
bool show_layers_parameters(layer* players, int layers_count);
bool show_layer_parameters(layer* player);
bool get_gt_label(int *gt_10, num_path& np);

bool reset_params_before_batches_forward_propagations(layers& lys);
bool show_train_probability(int* gt_10, layers& lys, int iters_count, int bacthes_count);
bool add_batch_diffs(layers& lys);
bool upadate_params_after_batches_back_propagations(layers& lys, double learning_rate);
bool calculate_accuracy(layers& lys, vector<num_path>& test_path_label, double accuracy[][LABELS_COUNTS + 1], int test_count);
/* todo random初始化不是很好 */
/* 一般的卷积网络第一层都是卷积层,所以第一层默认卷积层，todo 第一层不是卷积层需要重新考虑*/
/* 同样的，layers中实例化的所有参数都必须始终不能重新申请，否则系统会不停的申请释放内存，甚至是奔溃 */
int main(int argc, char* argv[]){

	string train_file_name = ".\\data\\train_image_32_small\\0\\*.bmp";
	string valid_file_name = ".\\data\\test_image\\0\\*.bmp";
	string test_file_name =  ".\\data\\test_image_32_small\\0\\*.bmp";
	//vector<num_path> train_label_imgs[LABELS_COUNTS];
	//vector<num_path> valid_label_imgs[LABELS_COUNTS];
	//vector<num_path> test_label_imgs[LABELS_COUNTS];
	vector<vector<num_path>> train_label_imgs; train_label_imgs.resize(LABELS_COUNTS);
	vector<vector<num_path>> valid_label_imgs; valid_label_imgs.resize(LABELS_COUNTS);
	vector<vector<num_path>> test_label_imgs;  test_label_imgs.resize(LABELS_COUNTS);
	vector<num_path> train_path_label;
	vector<num_path> vaild_path_label;
	vector<num_path> test_path_label;
	get_image_path_and_label(train_label_imgs, train_path_label, train_file_name);
	get_image_path_and_label(valid_label_imgs, vaild_path_label, valid_file_name);
	get_image_path_and_label(test_label_imgs, test_path_label, test_file_name);

	num_path num_path_;
	int num_counts[LABELS_COUNTS] = { 0 };
	int nums_counts[LABELS_COUNTS] = { 0 };
	double scale = 0.10;
	for (int i = 0; i < LABELS_COUNTS; ++i){	
		nums_counts[i] = MINI_BATCHES / LABELS_COUNTS;//todo 必须是整数
		std::cout << nums_counts[i] << "  ";
	}

	Mat image = imread(train_path_label[0].path, 0);
	std::cout << train_path_label[0].path << std::endl;
	std::cout << image.rows << "  " << image.cols << std::endl;
	layers lys(image.channels(), image.rows, image.cols, layers_parameters, LAYERS_COUNTS);
	int gt_10[LAYERS_COUNTS] = { 0 };
	double test_accuracy[TEST_TIMES][LABELS_COUNTS + 1] = { 0.0 };
	double valid_accuracy[TEST_TIMES][LABELS_COUNTS + 1] = { 0.0 };
	double errors[LABELS_COUNTS] = { 0.0 }, sum_errors;
	DATA_TYPE learning_rate = 0;

	for (int i = 0; i < RATE_CHANHE_NUMS * TEST_TIMES; ++i){
		learning_rate = BASE_LEARNING_RATE*pow(DECAY_RATE, i / RATE_CHANHE_NUMS);
		reset_params_before_batches_forward_propagations(lys);  /* 每一次batch传播之前所有的梯度清零 */
		int j = 0;
		for (int k = 0; k < LABELS_COUNTS; ++k){
			//std::cout << "nums_counts[" << k << "]=" << nums_counts[k] << "  " << std::endl;
			for (int l = 0; l < nums_counts[k]; ++l){
				++j;
				num_path_ = train_label_imgs[k][(num_counts[k] + l) % train_label_imgs[k].size()];
				std::cout << num_path_.path << "   " << num_path_.num << std::endl;
				get_gt_label(gt_10, num_path_);
				for (int t = 0; t < LABELS_COUNTS; ++t){
					if (1 == gt_10[t]){
						std::cout << t << endl;
					}
				}
				image = imread(num_path_.path, 0);
				//if (i % 7 == 0){
				//	if (j % 58 == 0){
				//		for (int t = 0; t < LABELS_COUNTS; ++t){
				//			if (1 == gt_10[t]){
				//				std::cout << t << endl;
				//			}
				//		}
				//	}
				//}
				//show(image, 2);
				lys.mp_layers[0].m_fts = image;/* todo */
				lys.forward_propagation();
				lys.back_propagation(gt_10);
				show_train_probability(gt_10, lys, i, j);
				add_batch_diffs(lys);
				//++num_counts[k];
			}
			//std::cout << std::endl;
			num_counts[k] += nums_counts[k];
			//std::cout << std::endl;
			//std::cout << "num_counts[" << k << "]=" << num_counts[k] << "  " << std::endl;
			int xxx = 0;
		}   
		upadate_params_after_batches_back_propagations(lys, learning_rate);
		int iii = i / RATE_CHANHE_NUMS;
		if (0 == i % (RATE_CHANHE_NUMS)){/* todo valid accuarcy的下标冲突了 */
			calculate_accuracy(lys, test_path_label, test_accuracy, iii);
			
			/* 由于竞争性学习，概率造成的四舍五入，所以前向传播的minibatch 只是近似等于batch_size */
			sum_errors = 0.0;
			std::cout << "errors" << std::endl;
			for (int j = 0; j < LABELS_COUNTS; ++j){
				errors[j] = 1.0 - test_accuracy[iii][j];
				std::cout << setw(SHOW_PROBABILITY_WIDTH) << errors[j];
				sum_errors += errors[j];
			}
			if (sum_errors / (0.0 + LABELS_COUNTS) > 0.10){
				scale = 0.0;
			}
			else{
				scale = 0.20;
			}
			std::cout << "\n相对 errors" << std::endl;
			for (int j = 0; j < LABELS_COUNTS; ++j){
				errors[j] = (errors[j] + DELTA) / (sum_errors + DELTA*LABELS_COUNTS);
				std::cout << setw(SHOW_PROBABILITY_WIDTH) << errors[j];
			}
			std::cout << std::endl;
			int sum = 0;
			for (int j = 0; j < LABELS_COUNTS; ++j){
				nums_counts[j] = scale*errors[j] * MINI_BATCHES;
				nums_counts[j] += ((scale*errors[j] * MINI_BATCHES > nums_counts[j] + 0.5) ? 1 : 0);
				std::cout << setw(SHOW_PROBABILITY_WIDTH) << nums_counts[j];
				sum += nums_counts[j];
			}
			std::cout << std::endl;
			int t = MINI_BATCHES - sum;
			int xxx = t / LABELS_COUNTS;
			for (int j = 0; j < LABELS_COUNTS; ++j){
				//xxx = double(t) / double(LABELS_COUNTS);
				//xxx = xxx>int(xxx) + 0.35 ? xxx + 1 : xxx;
				nums_counts[j] += xxx;
			}
			//nums_counts[LABELS_COUNTS - 1] += t - int(xxx)*(LABELS_COUNTS - 1);
			int tmp = 0;
			for (int k = 0; k < LABELS_COUNTS; ++k){
				std::cout << setw(SHOW_PROBABILITY_WIDTH) << nums_counts[k];
				tmp += nums_counts[k];
			}

			std::cout << std::endl << "tmp=" << tmp << std::endl;
		}
	}// end i


    std::cout << std::endl << "****************************************************************************************************************" << std::endl;
	for (int i = 0; i < TEST_TIMES; ++i){
        for (int j = 0; j < 11; ++j){
            std::cout << setw(6) << 100.0*test_accuracy[i][j] << " ";
        }
        std::cout << endl;
	}
	std::cout << std::endl;
    std::cout << std::endl << "****************************************************************************************************************" << std::endl;
    return 0;
}

bool get_image_path_and_label(vector<vector<num_path>>& label_imgs, vector<num_path> &vec_path_label, string file_name){
    vector<string> num_file;
    vector<vector<string> > num_files;
    /*                                                        35              */
    vector<string> file_names;
    int num_counts = 0;
    //for (int i = 0; i < 10; ++i){    /* todo */
	int n = 0;
	for (int i = file_name.size() - 1; i >= 0; --i){
		if ('\\' == file_name[i]){
			n = i;
			break;
		}
	}

    for (int i = 0; i < LABELS_COUNTS; ++i){    /* todo */
		file_name[n - 1] = '0' + i;
		std::cout << file_name << endl;
        file_names.push_back(file_name);
        get_files(file_name, num_file);
        std::cout << i << " num_file= " << num_file.size() << std::endl;
        num_files.push_back(num_file);
        num_counts += num_files[i].size();
		label_imgs[i].resize(num_files[i].size());
        num_file.clear();
    }
    
    vec_path_label.resize(num_counts);
    //vector<num_path> image_label(num_counts);
    int k = -1;
    for (int i = 0; i < num_files.size(); ++i){

        int n = num_files[i].size();
        for (int j = 0; j < n; ++j){
            vec_path_label[++k] = num_path{ i, num_files[i][j] };
			label_imgs[i][j] = vec_path_label[k];
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

bool reset_params_before_batches_forward_propagations(layers& lys){
	for (int k = 0; k < LAYERS_COUNTS; ++k){
		switch (lys.mp_layers[k].m_layer_mode){
		case FULLCONNECTION_LAYER:
		case CONVOLUTION_LAYER: lys.mp_layers[k].m_fts_diffs.reset(0.0); 
			lys.mp_layers[k].m_fts_mat_diffs.reset(0.0); 
			lys.mp_layers[k].m_kers_diffs.reset(0.0);
			lys.mp_layers[k].m_conv_mat_diffs.reset(0.0); 
			lys.mp_layers[k].m_conv_relu_mat_diffs.reset(0.0); 
			lys.mp_layers[k].m_conv_relu_mat2fts_diffs.reset(0.0);
			break;
		case POOLING_LAYER: 
			lys.mp_layers[k].m_fts_diffs.reset(0.0);
			break;
		}
	}
	return true;
}

bool show_train_probability(int* gt_10, layers& lys, int iters_count, int bacthes_count){
	if (iters_count % 7 == 0){
		if (bacthes_count % 58 == 0){
			std::cout << "\n\niterations  " << iters_count*MINI_BATCHES + bacthes_count << "   " << std::endl;
			for (int i = 0; i < LABELS_COUNTS; ++i){
				if (0 == gt_10[i]){
					for (int j = 0; j < SHOW_PROBABILITY_WIDTH; ++j){
						std::cout << " ";
					}
				}
				else{
					for (int j = 0; j < SHOW_PROBABILITY_WIDTH - 2; ++j){
						std::cout << " ";
					}
					std::cout << i << " ";
				}
			}

			std::cout << std::endl;
			for (int i = 0; i < LABELS_COUNTS; ++i){
				if (0 == gt_10[i]){
					for (int j = 0; j < SHOW_PROBABILITY_WIDTH; ++j){
						std::cout << " ";
					}
				}
				else{
					for (int j = 0; j < SHOW_PROBABILITY_WIDTH - 5; ++j){
						std::cout << " ";
					}
					std::cout << "*****";
				}
			}//end i
			std::cout << std::endl;
			for (int i = 0; i < LABELS_COUNTS; ++i){
				std::cout << setw(SHOW_PROBABILITY_WIDTH) << lys.y.mp_matrixes[i].mp_data[0];
			}
			std::cout << std::endl;
			for (int i = 0; i < LABELS_COUNTS; ++i){
				std::cout << setw(SHOW_PROBABILITY_WIDTH) << lys.t.mp_matrixes[i].mp_data[0];
			}
			std::cout << std::endl;
			for (int i = 0; i < LABELS_COUNTS; ++i){
				std::cout << setw(SHOW_PROBABILITY_WIDTH) << 100.0*lys.q.mp_matrixes[i].mp_data[0];
			}
			std::cout << std::endl;
		}
	}//end i%50==0
	return true;
}

bool add_batch_diffs(layers& lys){
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
	return true;
}

bool upadate_params_after_batches_back_propagations(layers& lys, double learning_rate){
	for (int k = 0; k < LAYERS_COUNTS; ++k){
		switch (lys.mp_layers[k].m_layer_mode){
		case FULLCONNECTION_LAYER:
		case CONVOLUTION_LAYER:
			lys.mp_layers[k].m_kers -= (learning_rate / MINI_BATCHES)*(lys.mp_layers[k].m_kers_diffs);
			break;
		case POOLING_LAYER: break;/* do nothing */
		}
	}

	return true;
}

bool calculate_accuracy(layers& lys, vector<num_path>& test_path_label, double accuracy[][LABELS_COUNTS + 1], int test_counts){
	//std::cout << "\n\niterations  " << i*MINI_BATCHES << "   " << std::endl;
	//std::cout << std::endl;
	//for (int i = 0; i < LABELS_COUNTS; ++i){
	//	std::cout << setw(SHOW_PROBABILITY_WIDTH - 1) << i;
	//	std::cout << " ";
	//}
	//std::cout << std::endl;

	//for (int i = 0; i < LABELS_COUNTS; ++i){
	//	if (0 == gt_10[i]){
	//		for (int j = 0; j < SHOW_PROBABILITY_WIDTH; ++j){
	//			std::cout << " ";
	//		}
	//	}
	//	else{
	//		for (int j = 0; j < SHOW_PROBABILITY_WIDTH - 5; ++j){
	//			std::cout << " ";
	//		}
	//		std::cout << "*****";
	//	}
	//}

	//for (int i = 0; i < LABELS_COUNTS; ++i){
	//	std::cout << setw(SHOW_PROBABILITY_WIDTH) << lys.y.mp_matrixes[i].mp_data[0];
	//}
	//std::cout << std::endl;

	//for (int i = 0; i < LABELS_COUNTS; ++i){
	//	std::cout << setw(SHOW_PROBABILITY_WIDTH) << lys.t.mp_matrixes[i].mp_data[0];
	//}
	//std::cout << std::endl;

	//for (int i = 0; i < LABELS_COUNTS; ++i){
	//	std::cout << setw(SHOW_PROBABILITY_WIDTH) << 100.0*lys.q.mp_matrixes[i].mp_data[0];
	//}
	//std::cout << std::endl;

	string  str = "*********************************************************************************************************************************************************************";
	//for (int i = 0; i < LABELS_COUNTS; ++i){
	//	std::cout << setw(SHOW_PROBABILITY_WIDTH) << i;
	//}
	std::cout << std::endl;

	int right[11] = { 0 };
	int counts[11] = { 0 };
	int n = test_path_label.size();
	for (int i = 0; i < n; ++i){
		++counts[LABELS_COUNTS];
		cv::Mat image = imread(test_path_label[i].path, 0);
		lys.mp_layers[0].m_fts = image;
		lys.forward_propagation();
		double max = lys.q.mp_matrixes[0].mp_data[0];
		int index = 0;
		for (int j = 1; j < LABELS_COUNTS; ++j){
			if (max < lys.q.mp_matrixes[j].mp_data[0]){
				max = lys.q.mp_matrixes[j].mp_data[0];
				index = j;
			}
		}
		++counts[test_path_label[i].num];
		if (index == test_path_label[i].num){
			++right[test_path_label[i].num];
		}
	}
	right[LABELS_COUNTS] = 0;
	for (int r = 0; r < LABELS_COUNTS; ++r){
		right[LABELS_COUNTS] += right[r];
	}
	for (int r = 0; r < LABELS_COUNTS + 1; ++r){
		accuracy[test_counts][r] = (0.0 + right[r]) \
			/ (0.0 + counts[r]);
	}
	std::cout << "******************************************************" << std::endl;
	std::cout << str << std::endl;
	for (int j = 0; j < LABELS_COUNTS; ++j){
		std::cout << setw(SHOW_PROBABILITY_WIDTH) << j;
	}
	std::cout << std::endl;
	for (int i = 0; i <= test_counts; ++i){
		//for (int s = 0; s < 11; ++s){
		//    std::cout << setw(LABELS_COUNTS) << right[s];
		//}
		//std::cout << std::endl;
		//for (int s = 0; s < 11; ++s){
		//    std::cout << setw(LABELS_COUNTS) << counts[s];
		//}
		//std::cout << std::endl;
		for (int j = 0; j < LABELS_COUNTS + 1; ++j){
			std::cout << setw(SHOW_PROBABILITY_WIDTH) << 100.0*accuracy[i][j];
		}
		std::cout << endl;
	}

	std::cout << std::endl << str << std::endl;
	std::cout << "******************************************************" << std::endl;
	return true;
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
	int n = 0;
	for (int i = file_name.size() - 1; i >= 0; --i){
		if ('\\' == file_name[i]){
			n = i;
			break;
		}
	}
	string full_name = file_name.substr(0, n + 1);
	//intptr_t handle = _findfirst(file_name.c_str(), &file_info);/* win7 */
	intptr_t handle = _findfirst(file_name.c_str(), &file_info);  /* win10 */
	//cout << file_name << endl;
	std::cout << full_name << std::endl;
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
	} while (0 == _findnext(handle, &file_info));

	return true;
}

bool show(Mat &image, int show_image_mode){
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
