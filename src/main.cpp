#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow main_window;

    main_window.setFixedSize(500, 500);
    main_window.setWindowTitle("Galagacv menu");

    main_window.show();

    return app.exec();
}
