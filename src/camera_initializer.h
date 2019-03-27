#ifndef CAMERA_INITIALIZER_H
#define CAMERA_INITIALIZER_H

#include <string>

#include "opencv2/opencv.hpp"

class CameraInitializer
{
    cv::VideoCapture video_flow;
    cv::Mat raw_frame;

public:
    CameraInitializer();
    ~CameraInitializer();

    template<class T> int init(T);

    cv::Mat *get_frame();
    cv::Size get_frame_size();
};

#endif // CAMERA_INITIALIZER_H
