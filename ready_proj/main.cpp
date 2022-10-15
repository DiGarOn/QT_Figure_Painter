#include <QApplication>

#include "mainwindow.h"
#include "dialog.h"

Figure* HighlightedFigure;

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    MainWindow w;
    w.resize(800, 800);
    w.show();

    return app.exec();
}
