#ifndef FIGURE_H
#define FIGURE_H

#include <QWidget>
#include <utility>

class Figure;
extern Figure* HighlightedFigure;

class Figure : public QWidget {
    Q_OBJECT

public:
    bool isResized;
    bool isHighlighted;
    bool isRotationChanged;

    explicit Figure(QWidget* wgt);
    void dehighlight();

    std::pair<int, int> newCoor(const std::pair<int, int>& oldCoor, bool isChanged) const;

    int getWidth() const { return w; }
    int getHeight() const { return h; }
    int getDegree() const { return degree; }
    double getPerimeter() const { return p; }
    double getArea() const { return s; }

    virtual bool isPointOfFigure(QPoint point) const = 0;
    virtual void updPerim() = 0;
    virtual void updArea() = 0;

    virtual int getP1() const = 0;
    virtual int getP2() const = 0;
    virtual int getP3() const = 0;
    virtual int getP4() const = 0;
    virtual int getP5() const = 0;
    virtual int getP6() const = 0;

public slots:
    void setWidth(int w_) {
        w = w_;
        h = h % w;
        if (h == 0) h += 3;
        updPerim();
        updArea();
        isResized = false;
        repaint();
    }
    void setHeight(int h_) {
        h = h_;
        if (h == 0) h += 3;
        updPerim();
        updArea();
        isResized = false;
        repaint();
    }
    void setDegree(int deg_) {
        degree = deg_;
        isResized = false;
        repaint();
    }
    void setRotation(bool is) {
        isRotationChanged = is;
        isResized = false;
        repaint();
    }

    virtual void setP1(int p1_) = 0;
    virtual void setP2(int p2_) = 0;
    virtual void setP3(int p3_) = 0;
    virtual void setP4(int p4_) = 0;
    virtual void setP5(int p5_) = 0;
    virtual void setP6(int p6_) = 0;

protected:
    void paintEvent (QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    double s, p;

private:
    int w;
    int h;
    int degree;
    int mousePosX;
    int mousePosY;
};

class Figure_1 : public Figure {
    Q_OBJECT

public:
    explicit Figure_1(QWidget *wgt);

    void updArea() override;
    void updPerim() override;
    bool isPointOfFigure(QPoint point) const override;

    int getP1() const override { return p1; }
    int getP2() const override { return p2; }
    int getP3() const override { return p3; }
    int getP4() const override { return p4; }
    int getP5() const override { return p5; }
    int getP6() const override { return p6; }

public slots:
    void setP1(int p1_) override {
        p1 = p1_;
        updPerim();
        updArea();
        isResized = false;
        repaint();
    }
    void setP2(int p2_) override {
        p2 = p2_;
        updPerim();
        updArea();
        isResized = false;
        repaint();
    }
    void setP3(int p3_) override {
        p3 = p3_;
        updPerim();
        updArea();
        isResized = false;
        repaint();
    }
    void setP4(int p4_) override {
        p4 = p4_;
        updPerim();
        updArea();
        isResized = false;
        repaint();
    }
    void setP5(int p5_) override {
        p5 = p5_;
        updPerim();
        updArea();
        isResized = false;
        repaint();
    }
    void setP6(int p6_) override {
        p6 = p6_;
        updPerim();
        updArea();
        isResized = false;
        repaint();
    }

protected:
    void paintEvent(QPaintEvent *event);

private:
    int p1, p2, p3, p4, p5, p6;
};

class Figure_2 : public Figure {
    Q_OBJECT

public:
    explicit Figure_2(QWidget *wgt);

    void updArea() override;
    void updPerim() override;
    bool isPointOfFigure(QPoint point) const override;

    int getP1() const override { return p1; }
    int getP2() const override { return p2; }
    int getP3() const override { return p3; }
    int getP4() const override { return p4; }
    int getP5() const override { return p5; }
    int getP6() const override { return p6; }

public slots:
    void setP1(int p1_) override {
        p1 = p1_;
        updPerim();
        updArea();
        isResized = false;
        repaint();
    }
    void setP2(int p2_) override {
        p2 = p2_;
        updPerim();
        updArea();
        isResized = false;
        repaint();
    }
    void setP3(int p3_) override {
        p3 = p3_;
        updPerim();
        updArea();
        isResized = false;
        repaint();
    }
    void setP4(int p4_) override {
        p4 = p4_;
        updPerim();
        updArea();
        isResized = false;
        repaint();
    }
    void setP5(int p5_) override {
        p5 = p5_;
        updPerim();
        updArea();
        isResized = false;
        repaint();
    }
    void setP6(int p6_) override {
        p6 = p6_;
        updPerim();
        updArea();
        isResized = false;
        repaint();
    }

protected:
    void paintEvent(QPaintEvent *event);

private:
    int p1, p2, p3, p4, p5, p6;
};



#endif // FIGURE_H
