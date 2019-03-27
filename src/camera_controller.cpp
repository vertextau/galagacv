#include <math.h>

#include "camera_controller.h"

CameraController::CameraController(CameraInitializer *camera, QObject *parent) : QObject(parent)
{
    this->camera = camera;
    position = GameSettings::SPACESHIP_POSITION;
}

CameraController::~CameraController() {}


void CameraController::run()
{
    finish_thread_flag = false;

    frame1 = *camera->get_frame();
    frame2 = *camera->get_frame();

    for(;;)
    {
        if(finish_thread_flag)
        {
            emit finished();
            return;
        }
        update();
    }
}

void CameraController::exit()
{
    finish_thread_flag = true;
}

void CameraController::update()
{
    cv::Mat frame1_copy = frame1.clone();
    cv::Mat frame2_copy = frame2.clone();

    filter_frame(&frame1_copy);
    filter_frame(&frame2_copy);

    cv::Mat frame_diff;
    cv::absdiff(frame1_copy, frame2_copy, frame_diff);

    // https://docs.opencv.org/4.0.1/d3/dc1/tutorial_basic_linear_transform.html
    change_bright_contrs(&frame_diff, 2.2, 50);

    cv::Mat threshold;
    cv::threshold(frame_diff, threshold, 90, 255.0, cv::THRESH_BINARY);

    cv::Mat str_elem_rect = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(20, 40));
    //cv::Mat str_elem_ellipse = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(20, 40));

    cv::dilate(threshold, threshold, str_elem_rect);
    cv::dilate(threshold, threshold, str_elem_rect);
    //cv::morphologyEx(threshold, threshold, cv::MORPH_CLOSE, structuringElement);

    std::vector<std::vector<cv::Point> > contours;

    cv::findContours(threshold, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

    std::sort(contours.begin(), contours.end(), compare_contours);

    if (contours.size() >= 2)
    {
        contours.erase(contours.begin()+1, contours.end());
    }

    std::vector<std::vector<cv::Point> > convex_hulls(contours.size());

    for (unsigned int i = 0; i < contours.size(); ++i)
    {
        cv::convexHull(contours[i], convex_hulls[i]);
    }

    for (unsigned int i = 0; i < convex_hulls.size(); ++i)
    {
        cv::Rect r = cv::boundingRect(convex_hulls[i]);
        x_coord = r.x;

        if (std::abs(position - x_coord) < 100)
        {
            position = x_coord;
        }
    }

    frame1 = frame2.clone();

    frame2 = *camera->get_frame();
}

void CameraController::filter_frame(cv::Mat *frame)
{
    cv::cvtColor(*frame, *frame, cv::COLOR_BGR2GRAY);

    cv::GaussianBlur(*frame, *frame, cv::Size(5, 5), 0);
}

void CameraController::change_bright_contrs(cv::Mat *frame, double a, int b)
{
    for(int x = 0; x < frame->rows; ++x)
    {
        for(int y = 0; y < frame->cols; ++y)
        {
            frame->at<uchar>(x, y) = cv::saturate_cast<uchar>(frame->at<uchar>(x, y)*a + b);
        }
    }
}

bool CameraController::compare_contours(const std::vector<cv::Point> &c1, const std::vector<cv::Point> &c2)
{
    return cv::contourArea(c1) > cv::contourArea(c2);
}

int CameraController::get_position()
{
    return GameSettings::GAME_WINDOW_WIDTH - position;
}
