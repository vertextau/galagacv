#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <QLayout>
#include <QRadioButton>
#include <QPixmap>
#include <QLabel>
#include <QLineEdit>

#include "game_board.h"
#include "settings.h"
#include "camera_initializer.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QRadioButton *controller_camera;
    GameBoard *game_board;
    QPixmap menu_image;
    QLabel *info_message;
    QLineEdit *cam_name;

private slots:
    void run_game();
    void help_info();
    void exit();

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};

#endif // MAIN_WINDOW_H
