#include "AnalogClockWidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow window;
    auto* clock = new AnalogClockWidget;

    window.setCentralWidget(clock);
    window.resize(400, 400);
    window.show();

    return app.exec();
}
