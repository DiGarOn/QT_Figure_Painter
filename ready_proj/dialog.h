#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QGridLayout>
#include <QSpinBox>
#include <QRadioButton>

#include "figure.h"

class Dialog : public QDialog {
    Q_OBJECT

public:
    explicit Dialog(Figure *parent = 0) : QDialog(parent) {
        parent_ = parent;

        w_  = new QSpinBox(this);
        h_  = new QSpinBox(this);
        p_a = new QSpinBox(this);
        p_b = new QSpinBox(this);
        p_c = new QSpinBox(this);
        p_d = new QSpinBox(this);
        p_e = new QSpinBox(this);
        p_f = new QSpinBox(this);
        r_v = new QSpinBox(this);

        w_->setStyleSheet("color: black; ");
        h_->setStyleSheet("color: black; ");
        p_a->setStyleSheet("color: black; ");
        p_b->setStyleSheet("color: black; ");
        p_c->setStyleSheet("color: black; ");
        p_d->setStyleSheet("color: black; ");
        p_e->setStyleSheet("color: black; ");
        p_f->setStyleSheet("color: black; ");
        r_v->setStyleSheet("color: black; ");

         w_->setRange(parent->getHeight() / 2 + 1, parent->parentWidget()->width());
         h_->setRange(8, parent->parentWidget()->height() / 2);
        p_a->setRange(0, parent->parentWidget()->height() / 6);
        p_b->setRange(0, parent->parentWidget()->height() / 6);
        p_c->setRange(0, parent->parentWidget()->height() / 6);
        p_d->setRange(0, parent->parentWidget()->height() / 6);
        p_e->setRange(0, parent->parentWidget()->width()  / (8 * parent->parentWidget()->height()));
        p_f->setRange(0, parent->parentWidget()->width()  / (8 * parent->parentWidget()->height()));		r_v->setRange(0, 360);

         w_->setValue(parent->getWidth());
         h_->setValue(parent->getHeight());
        p_a->setValue(parent->getP1());
        p_b->setValue(parent->getP2());
        p_c->setValue(parent->getP3());
        p_d->setValue(parent->getP4());
        p_e->setValue(parent->getP5());
        p_f->setValue(parent->getP6());
        r_v->setValue(parent->getDegree());

        QLabel *l_w = new QLabel("width", this);
        QLabel *l_h = new QLabel("height", this);
        QLabel *l_a = new QLabel("parameter for A", this);
        QLabel *l_b = new QLabel("parameter for B", this);
        QLabel *l_c = new QLabel("parameter for C", this);
        QLabel *l_d = new QLabel("parameter for D", this);
        QLabel *l_e = new QLabel("parameter for E", this);
        QLabel *l_f = new QLabel("parameter for F", this);
        QLabel *l_r = new QLabel("rotation value", this);

        l_w->setStyleSheet("color: black; ");
        l_h->setStyleSheet("color: black; ");
        l_a->setStyleSheet("color: black; ");
        l_b->setStyleSheet("color: black; ");
        l_c->setStyleSheet("color: black; ");
        l_d->setStyleSheet("color: black; ");
        l_e->setStyleSheet("color: black; ");
        l_f->setStyleSheet("color: black; ");
        l_r->setStyleSheet("color: black; ");

        per  = new QLabel("Perimeter = " + QString::number(parent->getPerimeter()), this);
        area = new QLabel("Area = " + QString::number(parent->getArea()), this);

        per->setStyleSheet("color: black; ");
        area->setStyleSheet("color: black; ");

        rotR = new QRadioButton("clockwise");
        rotL = new QRadioButton("counterclockwise");

        rotR->setStyleSheet("color: black; ");
        rotL->setStyleSheet("color: black; ");

        if (parent->isRotationChanged) {
            rotR->setChecked(true);
        }
        else {
            rotL->setChecked(true);
        }


        QGridLayout *grid = new QGridLayout(this);

        grid->addWidget(l_w, 0, 0, Qt::AlignRight);
        grid->addWidget(w_, 0, 1);
        grid->addWidget(l_h, 1, 0, Qt::AlignRight);
        grid->addWidget(h_, 1, 1);
        int counter = 2;
        if (p_a->value() != 0) {
            grid->addWidget(l_a, counter, 0, Qt::AlignRight);
            grid->addWidget(p_a, counter, 1);
            counter++;
            connect(p_a, SIGNAL(editingFinished()), this, SLOT(setP1()));
        }
        else {
            delete p_a;
            delete l_a;
        }
        if (p_b->value() != 0) {
            grid->addWidget(l_b, counter, 0, Qt::AlignRight);
            grid->addWidget(p_b, counter, 1);
            counter++;
            connect(p_b, SIGNAL(editingFinished()), this, SLOT(setP2()));
        }
        else {
            delete p_b;
            delete l_b;
        }
        if (p_c->value() != 0) {
            grid->addWidget(l_c, counter, 0, Qt::AlignRight);
            grid->addWidget(p_c, counter, 1);
            counter++;
            connect(p_c, SIGNAL(editingFinished()), this, SLOT(setP3()));
        }
        else {
            delete p_c;
            delete l_c;
        }
        if (p_d->value() != 0) {
            grid->addWidget(l_d, counter, 0, Qt::AlignRight);
            grid->addWidget(p_d, counter, 1);
            counter++;
            connect(p_d, SIGNAL(editingFinished()), this, SLOT(setP4()));
        }
        else {
            delete p_d;
            delete l_d;
        }
        if (p_e->value() != 0) {
            grid->addWidget(l_e, counter, 0, Qt::AlignRight);
            grid->addWidget(p_e, counter, 1);
            counter++;
            connect(p_e, SIGNAL(editingFinished()), this, SLOT(setP5()));
        }
        else {
            delete p_e;
            delete l_e;
        }
        if (p_f->value() != 0) {
            grid->addWidget(l_f, counter, 0, Qt::AlignRight);
            grid->addWidget(p_f, counter, 1);
            counter++;
            connect(p_f, SIGNAL(editingFinished()), this, SLOT(setP6()));
        }
        else {
            delete p_f;
            delete l_f;
        }
        grid->addWidget(l_r, counter, 0, Qt::AlignRight);
        grid->addWidget(r_v, counter, 1);
        counter++;

        grid->addWidget(rotR, counter, 0);
        grid->addWidget(rotL, counter, 1);
        counter++;

        grid->addWidget(per, counter, 0);
        grid->addWidget(area, counter, 1);

        setLayout(grid);

        connect(w_, SIGNAL(editingFinished()), this, SLOT(setWidth()));
        connect(h_, SIGNAL(editingFinished()), this, SLOT(setHeight()));
        connect(r_v, SIGNAL(editingFinished()), this, SLOT(setDegree()));
        connect(rotR, SIGNAL(clicked()), this, SLOT(setRotation()));
        connect(rotL, SIGNAL(clicked()), this, SLOT(setRotation()));
    }

private:
    Figure *parent_;
    QSpinBox *w_;
    QSpinBox *h_;
    QSpinBox *p_a;
    QSpinBox *p_b;
    QSpinBox *p_c;
    QSpinBox *p_d;
    QSpinBox *p_e;
    QSpinBox *p_f;
    QSpinBox *r_v;
    QRadioButton *rotR;
    QRadioButton *rotL;
    QLabel *per;
    QLabel *area;

public slots:
    void setRotation() {
        parent_->setRotation(rotR->isChecked());
    }
    void setWidth() {
        parent_->setWidth(w_->value());
        per->setText("Perimeter = " + QString::number(parent_->getPerimeter()));
        area->setText("Area = " + QString::number(parent_->getArea()));
    }
    void setHeight() {
        parent_->setHeight(h_->value());
        per->setText("Perimeter = " + QString::number(parent_->getPerimeter()));
        area->setText("Area = " + QString::number(parent_->getArea()));
    }
    void setP1() {
        parent_->setP1(p_a->value());
        per->setText("Perimeter = " + QString::number(parent_->getPerimeter()));
        area->setText("Area = " + QString::number(parent_->getArea()));
    }
    void setP2() {
        parent_->setP2(p_b->value());
        per->setText("Perimeter = " + QString::number(parent_->getPerimeter()));
        area->setText("Area = " + QString::number(parent_->getArea()));
    }
    void setP3() {
        parent_->setP3(p_c->value());
        per->setText("Perimeter = " + QString::number(parent_->getPerimeter()));
        area->setText("Area = " + QString::number(parent_->getArea()));
    }
    void setP4() {
        parent_->setP4(p_d->value());
        per->setText("Perimeter = " + QString::number(parent_->getPerimeter()));
        area->setText("Area = " + QString::number(parent_->getArea()));
    }
    void setP5() {
        parent_->setP5(p_e->value());
        per->setText("Perimeter = " + QString::number(parent_->getPerimeter()));
        area->setText("Area = " + QString::number(parent_->getArea()));
    }
    void setP6() {
        parent_->setP6(p_f->value());
        per->setText("Perimeter = " + QString::number(parent_->getPerimeter()));
        area->setText("Area = " + QString::number(parent_->getArea()));
    }
    void setDegree() {
        parent_->setDegree(r_v->value());
        per->setText("Perimeter = " + QString::number(parent_->getPerimeter()));
        area->setText("Area = " + QString::number(parent_->getArea()));
    }
};

#endif
