#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow (parent)
{
    QWidget *widget = new QWidget(this);
    QPushButton *start_game = new QPushButton("Start");
    QPushButton *help_b = new QPushButton("Help");
    QPushButton *exit_game = new QPushButton("Exit");

    QRadioButton *controller_keyboard = new QRadioButton("Keyboard controller", this);
    controller_camera = new QRadioButton("Camera controller", this);
    cam_name = new QLineEdit(widget);
    cam_name->setText("0");

    controller_keyboard->setChecked(true);

    info_message = new QLabel(widget);
    QLabel *cam_label = new QLabel(widget);
    cam_label->setText("Camera id: ");

    menu_image.load("resources/Menu.png");
    QLabel *label = new QLabel(this);
    label->setPixmap(menu_image);

    QVBoxLayout *layout = new QVBoxLayout(widget);
    QBoxLayout *layout_camid = new QBoxLayout(QBoxLayout::LeftToRight, widget);

    layout_camid->addWidget(cam_label);
    layout_camid->addWidget(cam_name);

    layout->addWidget(label);
    layout->addWidget(start_game);
    layout->addWidget(help_b);
    layout->addWidget(controller_keyboard);
    layout->addWidget(controller_camera);
    layout->addLayout(layout_camid);
    layout->addWidget(info_message);
    layout->addWidget(exit_game);

    widget->setLayout(layout);
    setCentralWidget(widget);

    connect(start_game, SIGNAL(released()), this, SLOT(run_game()));
    connect(exit_game, SIGNAL(released()), this, SLOT(exit()));
    connect(help_b, SIGNAL(released()), this, SLOT(help_info()));

    game_board = new GameBoard();
}

MainWindow::~MainWindow()
{
    delete cam_name;
    delete controller_camera;
    delete info_message;
    delete game_board;
}

void MainWindow::run_game()
{
    QPalette palette;

    palette.setColor(QPalette::Background, Qt::black);

    if (controller_camera->isChecked())
    {
        CameraInitializer *cam_check = new CameraInitializer();

        int cam_id;
        const std::string cam_sid = cam_name->text().toLocal8Bit().constData();

        try
        {
            cam_id = std::stoi(cam_sid);

            if (cam_check->init(cam_id) != 0)
            {
                info_message->setText("Cannot open the webcam");
                //delete cam_check;
                return;
            }
            game_board->set_camera(cam_check);
        }
        catch (std::invalid_argument)
        {
            if (cam_check->init(cam_sid) != 0)
            {
                info_message->setText("Cannot open the webcam");
                //delete cam_check;
                return;
            }
            game_board->set_camera(cam_check);
        }

        //delete cam_check;
        game_board->set_camera_on(true);
    }

    game_board->setFixedSize(GameSettings::GAME_WINDOW_WIDTH, GameSettings::GAME_WINDOW_HEIGHT);
    game_board->setWindowTitle("Galagacv");
    game_board->setAutoFillBackground(true);
    game_board->setPalette(palette);

    this->hide();
    game_board->show();
}

void MainWindow::exit()
{
    std::exit(0);
}

void MainWindow::help_info()
{
    info_message->setText("LEFT - Left arrow\t\tRIGHT - Right arrow\nFIRE - f\t\t\tPAUSE - p\nEXIT - ESC");
}
