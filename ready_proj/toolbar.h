#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QMainWindow>
#include <QToolBar>
#include <QPushButton>

#include "figure.h"

class ToolBar : public QToolBar {
    Q_OBJECT

public:
    explicit ToolBar(QMainWindow *mw);
    void setDisabledOfButtonDelete(bool isDisabled) {
        del_figure->setDisabled(isDisabled);
    }

    bool highlighted_figure1;
    bool highlighted_figure2;

private:
    QPushButton *choose_1;
    QPushButton *choose_2;
    QPushButton *add_figure;
    QPushButton *del_figure;

public slots:
    void chosen_1();
    void chosen_2();
    void addFigure();
    void delFigure();
};

#endif // TOOLBAR_H
