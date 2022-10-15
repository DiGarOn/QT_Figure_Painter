#include "toolbar.h"

ToolBar::ToolBar(QMainWindow *mw) : QToolBar(mw) {
    highlighted_figure1 = false;
    highlighted_figure2 = false;

    choose_1 = new QPushButton("Figure 1", this);
    choose_2 = new QPushButton("Figure 2", this);
    add_figure = new QPushButton("Add", this);
    del_figure = new QPushButton("Delete", this);

    choose_1->setStyleSheet("background-color: black; ");
    choose_2->setStyleSheet("background-color: black; ");
    add_figure->setStyleSheet("background-color: black; ");
    del_figure->setStyleSheet("background-color: black; ");

    choose_1->setCheckable(true);
    choose_2->setCheckable(true);

    add_figure->setDisabled(true);
    del_figure->setDisabled(true);

    connect(choose_1, SIGNAL(clicked()), this, SLOT(chosen_1()));
    connect(choose_2, SIGNAL(clicked()), this, SLOT(chosen_2()));
    connect(add_figure, SIGNAL(clicked()), this, SLOT(addFigure()));
    connect(del_figure, SIGNAL(clicked()), this, SLOT(delFigure()));

    this->resize(400, 30);
    this->setMovable(false);
    this->addWidget(choose_1);
    this->addSeparator();
    this->addWidget(choose_2);
    this->addSeparator();
    this->addWidget(add_figure);
    this->addSeparator();
    this->addWidget(del_figure);

    this->show();
}

void ToolBar::chosen_1() {
    highlighted_figure2 = false;
    choose_1->setStyleSheet("background-color: red; ");
    choose_2->setStyleSheet("background-color: black; ");
    if (highlighted_figure1) {
        choose_1->setChecked(false);
        choose_1->setStyleSheet("background-color: black; ");
        highlighted_figure1 = false;
    }
    else {
        choose_2->setChecked(false);
        highlighted_figure1 = true;
    }
    //если никакая фигура не выбрана, то нельзя добавить фигуру
    if (!highlighted_figure1 && !highlighted_figure2) {
        add_figure->setDisabled(true);
    }
    else {
        add_figure->setDisabled(false);
    }
}

void ToolBar::chosen_2() {
    highlighted_figure1 = false;
    choose_2->setStyleSheet("background-color: red; ");
    choose_1->setStyleSheet("background-color: black; ");
    if (highlighted_figure2) {
        choose_2->setChecked(false);
        highlighted_figure2 = false;
        choose_2->setStyleSheet("background-color: black; ");
    }
    else {
        choose_1->setChecked(false);
        highlighted_figure2 = true;
    }
    //если никакая фигура не выбрана, то нельзя добавить фигуру
    if (!highlighted_figure1 && !highlighted_figure2) {
        add_figure->setDisabled(true);
    }
    else {
        add_figure->setDisabled(false);
    }
}

void ToolBar::addFigure() {
    if (highlighted_figure1) {
        Figure_1 *f1 = new Figure_1(parentWidget());
        f1->lower();
        f1->show();
    }
    if (highlighted_figure2) {
        Figure_2 *f2 = new Figure_2(parentWidget());
        f2->lower();
        f2->show();
    }

    return;
}

void ToolBar::delFigure() {
    delete HighlightedFigure;
    HighlightedFigure = nullptr;

    del_figure->setDisabled(true);
}
