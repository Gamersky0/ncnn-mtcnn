//
// Created by Lonqi on 2017/11/18.
//
#pragma once

#ifndef __MTCNN_NCNN_H__
#define __MTCNN_NCNN_H__
#include "net.h"
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <sys/time.h>
using namespace std;
using namespace cv;
struct Bbox
{
    float score;
    int x1;
    int y1;
    int x2;
    int y2;
    float area;
    float ppoint[10];
    float regreCoord[4];
};
class MTCNN {

public:
    MTCNN(const std::vector<std::string> param_files, const std::vector<std::string> bin_files);
    ~MTCNN();
    void detect(ncnn::Mat& img_, std::vector<Bbox>& finalBbox);
    void detection(const cv::Mat& img, std::vector<cv::Rect>& rectangles);
private:
    void generateBbox(ncnn::Mat score, ncnn::Mat location, vector<Bbox>& boundingBox_, float scale);
    void nms(vector<Bbox> &boundingBox_, const float overlap_threshold, string modelname="Union");
    void refine(vector<Bbox> &vecBbox, const int &height, const int &width, bool square);
    void PNet();
    void RNet();
    void ONet();
    ncnn::Net Pnet, Rnet, Onet;
    ncnn::Mat img;
    const float nms_threshold[3] = {0.5, 0.7, 0.7};
    const float threshold[3] = {0.8, 0.8, 0.6};
    const float mean_vals[3] = {127.5, 127.5, 127.5};
    const float norm_vals[3] = {0.0078125, 0.0078125, 0.0078125};
    const int MIN_DET_SIZE = 12;
    const int minsize = 90;
    std::vector<Bbox> firstBbox_, secondBbox_,thirdBbox_;
    int img_w, img_h;
};


#endif //__MTCNN_NCNN_H__
