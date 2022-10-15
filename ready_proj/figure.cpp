#include <QPainter>
#include <QMouseEvent>
#include <cmath>

#include "figure.h"
#include "dialog.h"

Figure::Figure(QWidget *wgt) :
    QWidget(wgt), isResized(false), isHighlighted(false),  degree(rand() % 360)
{
    mousePosX = rand() % parentWidget()->width() / 2;
    mousePosY = rand() % parentWidget()->height() / 2;
    this->move(mousePosX, mousePosY);

    w = rand() % parentWidget()->width() / 2 + 4;
    h = (rand() % parentWidget()->height() / 2) % w;
    if (h == 0) h += 3;
    isRotationChanged = false;
}

void Figure::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event)

    QPainter painter(this);

    if (isHighlighted) {
        painter.setPen(QPen(Qt::blue));
    }
    else {
        painter.setPen(QPen(Qt::black));
    }

    painter.translate((width() - 1) / 2, (height() - 1) / 2);
    painter.rotate(degree);

    painter.drawLine(0, h, w, h);
    painter.drawLine(0, 0, 0, h);
    painter.drawLine(w, h, w, 0);
    painter.drawLine(0, 0, w, 0);
}

void Figure::mousePressEvent(QMouseEvent *event) {

    if (HighlightedFigure != nullptr) {
        HighlightedFigure->dehighlight();
    }

    switch (event->button()) {
    case Qt::LeftButton:
        if (isPointOfFigure(event->pos())) {
            mousePosX = event->globalX() - this->x();
            mousePosY = event->globalY() - this->y();

            HighlightedFigure = this;
            isHighlighted = true;
            this->repaint();
        }
        break;
    case Qt::RightButton:
        if (isPointOfFigure(event->pos())) {
            HighlightedFigure = this;
            isHighlighted = true;
            this->repaint();
            Dialog d(this);
            d.setModal(true);
            d.exec();
        }
        break;
    default:
        QWidget::mousePressEvent(event);
        break;
    }
    QWidget::mousePressEvent(event);
}

void Figure::mouseMoveEvent(QMouseEvent *event) {
    if (isHighlighted) {
        if (event->globalX() < parentWidget()->x() ||
            event->globalX() > parentWidget()->x() + parentWidget()->width() ||
            event->globalY() < parentWidget()->y() ||
            event->globalY() > parentWidget()->y() + parentWidget()->height()
            ) {
            return;
        }

        if (isPointOfFigure(event->pos())) {
            this->move(event->globalX() - mousePosX,
                event->globalY() - mousePosY);
            this->repaint();
        }
    }
}

std::pair<int, int> Figure::newCoor(const std::pair<int, int>& oldCoor, bool isChanged) const {
    double radian = 3.14 / 180.0;
    if (!isChanged) {
        return { (std::cos(degree * radian)* oldCoor.first + std::sin(degree * radian)* oldCoor.second),
                 (-std::sin(degree * radian)* oldCoor.first + std::cos(degree * radian)* oldCoor.second) };
    }
    else {
        return { (std::cos(degree * radian)* oldCoor.first - std::sin(degree * radian)* oldCoor.second),
                 (std::sin(degree * radian)* oldCoor.first + std::cos(degree * radian)* oldCoor.second) };
    }
}

void Figure::dehighlight() {
    isHighlighted = false;
    HighlightedFigure = nullptr;
    this->repaint();
}
//__________________________________________________ Figure 2:
// там, где закругленые углы (4) - передается радиус, там, где квадратная не выпуклость (5) - передается p,
// там, где округлая не выпклость (6) - передается Q
Figure_2::Figure_2(QWidget *wgt) : Figure(wgt), p1(0), p2(rand() % (getHeight() / 3)),
    p3(rand() % (getHeight() / 3)), p4(rand() % (getHeight() / 3)),
    p5((rand() % (getWidth() / 4)) % getHeight()), p6((rand() % (getWidth() / 4)) % getHeight())
{
    this->resize(2 * getWidth() + 2, 2 * getHeight() + 2);

    updPerim();
    updArea();
}
//подсчет площади. из общего прямоугольника вычитаем части окружности, что не входят в фигуру и вырезы посередине
void Figure_2::updArea() {
    s = getHeight() * getWidth() - 0.75 * 3.14 * (p2 * p2 + p3 * p3 + p4 * p4) - 0.5 * p5 * p5 - 0.5 * 3.14 * p6 * p6;
}
//подсчет реиметра. + корректируем с учетом длин окружностей
void Figure_2::updPerim() {
    p = 2 * getWidth() + 2 * getHeight() - 2 * p2 - 2 * p3 - 2 * p4 - 2 * p6 + p5 + 3.14 * p6 + 0.5 * 3.14 * p2 + 0.5 * 3.14 * p3;
}

void Figure_2::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event)

    if (!isResized) {
        updArea();
        updPerim();

        int newW =  std::max(std::abs(newCoor({ 0, 0 }, isRotationChanged).first -
                    newCoor({ getWidth(), getHeight() }, isRotationChanged).first),
                    std::abs(newCoor({ 0, getHeight() }, isRotationChanged).first -
                    newCoor({ getWidth(), 0 }, isRotationChanged).first));
        int newH =  std::max(std::abs(newCoor({ 0, 0 }, isRotationChanged).second -
                    newCoor({ getWidth(), getHeight() }, isRotationChanged).second),
                    std::abs(newCoor({ 0, getHeight() }, isRotationChanged).second -
                    newCoor({ getWidth(), 0 }, isRotationChanged).second));

        isResized = true;
        this->resize(newW + 4, newH + 4);
    }

    QPainter painter(this);

    if (isHighlighted) {
        painter.setPen(QPen(Qt::blue));
    }
    else {
        painter.setPen(QPen(Qt::black));
    }

    painter.translate((width() - 1) / 2, (height() - 1) / 2);
    if (isRotationChanged) {
        painter.rotate(getDegree());
    }
    else {
        painter.rotate(360 - getDegree());
    }
    //(x_start, y_start, x_end, y_end)
    painter.drawLine(p4 - getWidth() / 2, -getHeight() / 2, -p5 / 2, -getHeight() / 2);
    painter.drawLine(-p5 / 2, -getHeight() / 2, -p5 / 2, p5 / 2 - getHeight() / 2);
    painter.drawLine(-p5 / 2, p5 / 2 - getHeight() / 2, p5 / 2, p5 / 2 - getHeight() / 2);
    painter.drawLine(p5 / 2, p5 / 2 - getHeight() / 2, p5 / 2, -getHeight() / 2);
    painter.drawLine(p5 / 2, -getHeight() / 2, getWidth() / 2, -getHeight() / 2);
    painter.drawLine(getWidth() / 2, -getHeight() / 2, getWidth() / 2, getHeight() / 2 - p2);
    painter.drawLine(getWidth() / 2 - p2, getHeight() / 2, p6, getHeight() / 2);
    painter.drawLine(-p6, getHeight() / 2, p3 - getWidth() / 2, getHeight() / 2);
    painter.drawLine( -getWidth() / 2, getHeight() / 2 - p3, -getWidth() / 2, p4 - getHeight() / 2);


    painter.drawArc(-getWidth() / 2, -getHeight() / 2, p4 * 2, p4 * 2, 90 * 16, 90 * 16);
    painter.drawArc(getWidth() / 2 - 2 * p2, getHeight() / 2 - 2 * p2, 2 * p2, 2 * p2, 0, -90 * 16);
    painter.drawArc(-p6, getHeight() / 2 - p6, 2 * p6, 2 * p6, 0, 180 * 16);
    painter.drawArc(-getWidth() / 2, getHeight() / 2 - 2 * p3, 2 * p3, 2 * p3, 180 * 16, 90 * 16);
}

bool Figure_2::isPointOfFigure(QPoint point) const {

    point.rx() -= (width() - 1) / 2;
    point.ry() -= (height() - 1) / 2;

    auto newPoint = newCoor({ point.x(), point.y() }, isRotationChanged);
    point.rx() = newPoint.first;
    point.ry() = newPoint.second;

    if (std::abs(point.x()) > getWidth() / 2 || std::abs(point.y()) > getHeight() / 2) {
        return false;
    }

    if (point.x() >= (getWidth() / 2 - p2) && point.y() >= (getHeight() / 2 - p2)) {
        point.rx() -= (getWidth() / 2 - p2);
        point.ry() -= (getHeight() / 2 - p2);
        if ((point.rx() * point.rx() + point.ry() * point.ry()) <= (p2 * p2)) {
            return true;
        }
        else {
            return false;
        }
    }

    if (point.x() <= (-getWidth() / 2 + p3) && point.y() >= (getHeight() / 2 - p3)) {
        point.rx() += (getWidth() / 2 - p3);
        point.ry() -= (getHeight() / 2 - p3);
        if ((point.rx() * point.rx() + point.ry() * point.ry()) <= (p3 * p3)) {
            return true;
        }
        else {
            return false;
        }
    }

    if (point.x() <= (-getWidth() / 2 + p4) && point.y() <= (-getHeight() / 2 + p4)) {
        point.rx() += (getWidth() / 2 - p4);
        point.ry() += (getHeight() / 2 - p4);
        if ((point.rx() * point.rx() + point.ry() * point.ry()) <= (p4 * p4)) {
            return true;
        }
        else {
            return false;
        }
    }

    if (std::abs(point.x()) < p5 / 2 && point.y() < (-getHeight() / 2 + p5 / 2)) {
        return false;
    }

    if (std::abs(point.x()) <= p6 / 2 && point.y() >= (getHeight() / 2 - p6 / 2)) {
        point.ry() -= getHeight() / 2;
        if ((point.x() * point.x() + point.y() * point.y()) >= ((p6 / 2) * (p6 / 2))) {
            return true;
        }
        else {
            return false;
        }
    }
    return true;
}
//__________________________________________________ Figure 1: (код аналогичный Figure 2, за исключением замены самой фигуры)
Figure_1::Figure_1(QWidget *wgt) : Figure(wgt), p1(rand() % (getHeight() / 3)), p2(rand() % (getHeight() / 3)),
        p3(rand() % (getHeight() / 3)), p4(0),
        p5(0), p6((rand() % (getWidth() / 4)) % getHeight())
{
    this->resize(2 * getWidth() + 2, 2 * getHeight() + 2);

    updPerim();
    updArea();
}

void Figure_1::updArea() {
    s = getWidth() * getHeight() - p1 * p1 - 0.25 * 3.14 * p3 * p3 - 0.5 * 3.14 * p6 * p6 - 0.5 * p2 * p2;
}

void Figure_1::updPerim() {
    p = 2 * getWidth() + 2 * getHeight() - 2 * p2 - 2 * p6 - 2 * p3 + std::sqrt(2 * p2 * p2) + 3.14 * p6 + 0.5 * 3.14 * p3;
}

void Figure_1::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event)

    if (!isResized) {
        int newW =  std::max(std::abs(newCoor({ 0, 0 }, isRotationChanged).first -
                    newCoor({ getWidth(), getHeight() }, isRotationChanged).first),
                    std::abs(newCoor({ 0, getHeight() }, isRotationChanged).first -
                    newCoor({ getWidth(), 0 }, isRotationChanged).first));

        int newH =  std::max(std::abs(newCoor({ 0, 0 }, isRotationChanged).second -
                    newCoor({ getWidth(), getHeight() }, isRotationChanged).second),
                    std::abs(newCoor({ 0, getHeight() }, isRotationChanged).second -
                    newCoor({ getWidth(), 0 }, isRotationChanged).second));

        isResized = true;
        this->resize(newW + 4, newH + 4);
    }

    QPainter painter(this);

    if (isHighlighted) {
        painter.setPen(QPen(Qt::blue));
    }
    else {
        painter.setPen(QPen(Qt::black));
    }

    painter.translate((width() - 1) / 2, (height() - 1) / 2);
    if (isRotationChanged) {
        painter.rotate(getDegree());
    }
    else {
        painter.rotate(360 - getDegree());
    }

    painter.drawLine(p4 - getWidth() / 2, -getHeight() / 2, getWidth() / 2 - p1, -getHeight() / 2);
    painter.drawLine(getWidth() / 2 - p1, -getHeight() / 2, getWidth() / 2 - p1, p1 - getHeight() / 2);
    painter.drawLine(getWidth() / 2 - p1, p1 - getHeight() / 2, getWidth() / 2, p1 - getHeight() / 2);
    painter.drawLine(getWidth() / 2, p1 - getHeight() / 2, getWidth() / 2, getHeight() / 2 - p2);
    painter.drawLine(getWidth() / 2, getHeight() / 2 - p2, getWidth() / 2 - p2, getHeight() / 2);
    painter.drawLine(getWidth() / 2 - p2, getHeight() / 2, p6, getHeight() / 2);
    painter.drawLine(-p6, getHeight() / 2, p3 - getWidth() / 2, getHeight() / 2);
    painter.drawLine(-getWidth() / 2, getHeight() / 2 - p3, -getWidth() / 2, -getHeight() / 2);

    painter.drawArc(-p6, getHeight() / 2 - p6, 2 * p6, 2 * p6, 0, 180 * 16);
    painter.drawArc(-p3 - getWidth() / 2, getHeight() / 2 - p3, 2 * p3, 2 * p3, 0, 90 * 16);
}

bool Figure_1::isPointOfFigure(QPoint point) const {

    point.rx() -= (width() - 1) / 2;
    point.ry() -= (height() - 1) / 2;

    auto newPoint = newCoor({ point.x(), point.y() }, isRotationChanged);
    point.rx() = newPoint.first;
    point.ry() = newPoint.second;

    if (std::abs(point.x()) > getWidth() / 2 || std::abs(point.y()) > getHeight() / 2) {
        return false;
    }

    if (point.x() > (getWidth() / 2 - p1) && point.y() < (-getHeight() / 2 + p1)) {
        return false;
    }

    if (point.x() >= (getWidth() / 2 - p2) && point.y() >= (getHeight() / 2 - p2)) {
        if (std::abs(point.x() + point.y()) <=
            std::abs(getWidth() / 2 + (getHeight() / 2 - p2))) {
            return true;
        }
        else {
            return false;
        }
    }

    if (point.x() <= (-getWidth() / 2 + p3) && point.y() >= (getHeight() / 2 - p3)) {
        point.rx() += getWidth() / 2;
        point.ry() -= getHeight() / 2;
        if ((point.rx() * point.rx() + point.ry() * point.ry()) >= (p3 * p3)) {
            return true;
        }
        else {
            return false;
        }
    }

    if (std::abs(point.x()) <= p6 / 2 && point.y() >= (getHeight() / 2 - p6 / 2)) {
        point.ry() -= getHeight() / 2;
        if ((point.x() * point.x() + point.y() * point.y()) >= ((p6 / 2) * (p6 / 2))) {
            return true;
        }
        else {
            return false;
        }
    }
    return true;
}
