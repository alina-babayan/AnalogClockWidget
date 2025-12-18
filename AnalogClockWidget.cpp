#include "AnalogClockWidget.h"
#include <QTime>
#include <QtMath>

AnalogClockWidget::AnalogClockWidget(QWidget *parent)
    : QWidget(parent), timer(new QTimer(this))
{
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&AnalogClockWidget::update));
    timer->start();
    setMinimumSize(250,250);
}
void AnalogClockWidget::paintEvent(QPaintEvent* )
{
    QPainter painter(this);
    int side = qMin(width(), height());
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 200.0, side / 200.0);

    drawClockFace(painter);
    drawHands(painter);
}

void AnalogClockWidget::drawClockFace(QPainter& painter)
{
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawEllipse(QPoint(0, 0), 100, 100);

    painter.setPen(Qt::black);
    for (int i = 0; i < 60; ++i) {
        painter.save();
        painter.rotate(6.0 * i);

        if (i % 5 == 0) painter.drawLine(0, -90, 0, -75);
        else painter.drawLine(0, -90, 0, -85);

        painter.restore();
    }
}

void AnalogClockWidget::drawHands(QPainter& painter)
{
    QTime time = QTime::currentTime();

    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    painter.rotate(30.0 * (time.hour() % 12 + time.minute() / 60.0));
    painter.drawRect(-4, -50, 8, 50);
    painter.restore();

    painter.save();
    painter.setBrush(Qt::darkGreen);
    painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
    painter.drawRect(-3, -70, 6, 70);
    painter.restore();

    painter.save();
    painter.setBrush(Qt::green);
    painter.rotate(6.0 * time.second());
    painter.drawRect(-1, -80, 2, 80);
    painter.restore();

}
AnalogClockWidget::~AnalogClockWidget() {}
