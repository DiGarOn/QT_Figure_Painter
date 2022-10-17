#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    this->setStyleSheet("background-color:white;");

    std::srand(time(NULL));

    this->resize(400, 400);
    tb = new ToolBar(this);
    //addToolBar(Qt::TopToolBarArea, tb);

}

MainWindow::~MainWindow() {}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->spontaneous() && HighlightedFigure != nullptr) {
        HighlightedFigure->dehighlight();
    }

    if (HighlightedFigure == nullptr) {
        tb->setDisabledOfButtonDelete(true);
    }
    else {
        tb->setDisabledOfButtonDelete(false);
    }
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event)
    tb->resize(this->width(), 30);
    tb->repaint();
}
