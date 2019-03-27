#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include <algorithm>

#include <QObject>

#include "opencv2/opencv.hpp"
#include "camera_initializer.h"
#include "settings.h"


class CameraController : public QObject
{

    Q_OBJECT

public slots:
    void run();
    void exit();
signals:
    void finished();

public:
    explicit CameraController(CameraInitializer *, QObject *parent = nullptr);
    virtual ~CameraController();

    int get_position();

protected:
    void update();
    void filter_frame(cv::Mat *);
    void change_bright_contrs(cv::Mat *, double, int);
    static bool compare_contours(const std::vector<cv::Point> &, const std::vector<cv::Point> &);

    CameraInitializer *camera;

    bool finish_thread_flag;

    cv::Mat frame1, frame2;
    int position, x_coord;

};

#endif // CAMERA_CONTROLLER_H
