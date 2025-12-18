#include "AnalogClockWidget.h"
#include <QPainter>
#include <QTime>
#include <QtMath>

AnalogClockWidget::AnalogClockWidget(QWidget *parent)
    : QWidget(parent), timer(new QTimer(this))
{
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&AnalogClockWidget::update));
    timer->start();
    setMinimumSize(250, 250);
}

AnalogClockWidget::~AnalogClockWidget() = default;

void AnalogClockWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    const int side = qMin(width(), height());
    painter.translate(width()/2.0, height()/2.0);
    const double radius = 0.45 * side;

    QRadialGradient gradient(0, 0, radius);
    gradient.setColorAt(0.0, Qt::white);
    gradient.setColorAt(1.0, QColor(220, 220, 220));
    painter.setPen(Qt::NoPen);
    painter.setBrush(gradient);
    painter.drawEllipse(QPointF(0,0), radius, radius);

    QPen borderPen(Qt::black);
    borderPen.setWidthF(radius*0.03);
    borderPen.setCapStyle(Qt::RoundCap);
    painter.setPen(borderPen);
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(QPointF(0,0), radius, radius);

    QPen tickPen(Qt::black);
    tickPen.setWidthF(radius*0.01);
    tickPen.setCapStyle(Qt::RoundCap);
    painter.setPen(tickPen);

    for(int i=0;i<60;++i){
        painter.save();
        painter.rotate(i*6.0);
        double len = (i%5==0) ? radius*0.12 : radius*0.06;
        painter.drawLine(QPointF(0,-radius), QPointF(0,-radius+len));
        painter.restore();
    }

    QFont font = painter.font();
    font.setBold(true);
    font.setWeight(QFont::DemiBold);
    font.setPointSizeF(radius*0.18);
    painter.setFont(font);
    painter.setPen(Qt::black);

    double numRadius = radius*0.78;
    for(int i=1;i<=12;++i){
        double angleRad = qDegreesToRadians(i*30.0);
        double x = numRadius * qSin(angleRad);
        double y = -numRadius * qCos(angleRad);
        QRectF rect(x-radius*0.15, y-radius*0.15, radius*0.3, radius*0.3);
        painter.drawText(rect, Qt::AlignCenter, QString::number(i));
    }
    QTime t = QTime::currentTime();
    double s = t.second();
    double m = t.minute() + s/60.0;
    double h = (t.hour() % 12) + m/60.0;

    double hourAngle = h * 30.0;
    double minAngle  = m * 6.0;
    double secAngle  = s * 6.0;

    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    QPolygonF hourHand;
    hourHand << QPointF(0, -radius*0.5) << QPointF(radius*0.03, 0) << QPointF(0, radius*0.05) << QPointF(-radius*0.03, 0);
    painter.rotate(hourAngle);
    painter.drawPolygon(hourHand);
    painter.restore();

    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::darkBlue);
    QPolygonF minuteHand;
    minuteHand << QPointF(0, -radius*0.7) << QPointF(radius*0.02, 0) << QPointF(0, radius*0.04) << QPointF(-radius*0.02, 0);
    painter.rotate(minAngle);
    painter.drawPolygon(minuteHand);
    painter.restore();

    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::blue);
    QPolygonF secondHand;
    secondHand << QPointF(0, -radius*0.8) << QPointF(radius*0.01, 0) << QPointF(0, radius*0.03) << QPointF(-radius*0.01, 0);
    painter.rotate(secAngle);
    painter.drawPolygon(secondHand);
    painter.restore();

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    painter.drawEllipse(QPointF(0,0), radius*0.05, radius*0.05);
}
