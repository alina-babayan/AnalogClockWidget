#ifndef ANALOGCLOCKWIDGET_H
#define ANALOGCLOCKWIDGET_H

#include <QMainWindow>
#include <QTimer>
#include <QPainter>

class AnalogClockWidget : public QWidget
{
    Q_OBJECT

public:
    AnalogClockWidget(QWidget *parent = nullptr);
    ~AnalogClockWidget();

protected:
    void paintEvent(QPaintEvent* event) override;
private:
    QTimer* timer;

    // void drawClockFace(QPainter& painter);
    // void drawHands(QPainter& painter);
};
#endif // ANALOGCLOCKWIDGET_H
