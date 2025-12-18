#include "AnalogClockWidget.h"
#include <QTime>
#include <QTimer>
#include <QtMath>
#include <QPainter>

AnalogClockWidget::AnalogClockWidget(QWidget *parent)
    : QWidget(parent), timer(new QTimer(this))
{
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&AnalogClockWidget::update));
    timer->start();

    setMinimumSize(200, 200);
}

void AnalogClockWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);

    const int side = qMin(width(), height());
    painter.translate(width() / 2.0, height() / 2.0);

    const double radius = 0.45 * side;

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawEllipse(QPointF(0, 0), radius, radius);

    QPen borderPen(Qt::black);
    borderPen.setWidthF(radius * 0.03);
    painter.setPen(borderPen);
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(QPointF(0, 0), radius, radius);

    QPen smallTickPen(Qt::black);
    smallTickPen.setWidthF(radius * 0.01);
    painter.setPen(smallTickPen);
    for (int i = 0; i < 60; ++i) {
        painter.save();
        painter.rotate(i * 6.0);
        double tickLength = (i % 5 == 0) ? radius * 0.12 : radius * 0.06;
        painter.drawLine(QPointF(0, -radius), QPointF(0, -radius + tickLength));
        painter.restore();
    }

    QFont font = painter.font();
    font.setBold(true);
    font.setPointSizeF(radius * 0.15);
    painter.setFont(font);
    painter.setPen(Qt::black);

    const double numberRadius = radius * 0.78;
    for (int i = 1; i <= 12; ++i) {
        double angleRad = qDegreesToRadians(i * 30.0);
        double x = numberRadius * qSin(angleRad);
        double y = -numberRadius * qCos(angleRad);
        QRectF rect(x - radius * 0.15, y - radius * 0.15, radius * 0.3, radius * 0.3);
        painter.drawText(rect, Qt::AlignCenter, QString::number(i));
    }

    QTime time = QTime::currentTime();

    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    double hourLength = radius * 0.5;
    double hourWidth = radius * 0.04;
    painter.rotate(30.0 * (time.hour() % 12 + time.minute() / 60.0));
    painter.drawRect(-hourWidth, -hourLength, 2 * hourWidth, hourLength);
    painter.restore();

    painter.save();
    painter.setBrush(Qt::darkGreen);
    double minLength = radius * 0.7;
    double minWidth = radius * 0.03;
    painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
    painter.drawRect(-minWidth, -minLength, 2 * minWidth, minLength);
    painter.restore();

    painter.save();
    painter.setBrush(Qt::green);
    double secLength = radius * 0.8;
    double secWidth = radius * 0.01;
    painter.rotate(6.0 * time.second());
    painter.drawRect(-secWidth, -secLength, 2 * secWidth, secLength);
    painter.restore();

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    painter.drawEllipse(QPointF(0, 0), radius * 0.05, radius * 0.05);
}

AnalogClockWidget::~AnalogClockWidget()
{

}

