#include <iostream>

#include "camera_initializer.h"

CameraInitializer::CameraInitializer() {}

CameraInitializer::~CameraInitializer()
{
    video_flow.release();
}

template <class T>
int CameraInitializer::init(T device)
{
    video_flow.open(device);

    if (!video_flow.isOpened())
    {
        std::cerr << "Cannot open camera: " << device << std::endl;
        return -1;
    }

    return 0;
}

template int CameraInitializer::init<int>(int);
template int CameraInitializer::init<std::string>(std::string);

cv::Size CameraInitializer::get_frame_size()
{
    return cv::Size(static_cast<int>(video_flow.get(cv::CAP_PROP_FRAME_WIDTH)),
                    static_cast<int>(video_flow.get(cv::CAP_PROP_FRAME_HEIGHT)));
}

cv::Mat *CameraInitializer::get_frame()
{
    video_flow >> raw_frame;

    if (raw_frame.empty())
    {
        std::cerr << "Cannot grab frame from video flow" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    return &raw_frame;
}
