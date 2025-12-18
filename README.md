Analog Clock (Qt Widgets)

This project implements an analog clock widget using Qt Widgets and QPainter.

Features
QWidget-based analog clock
Custom drawing with QPainter
White clock face with border
12 dark, bold numbers (1–12)
60 tick marks (hours + seconds)
Sharp hour, minute, and second hands

Clockwise movement
Updates once per second
Scales correctly when resized
Uses update() (not repaint())
No heap allocation for QPainter

Timer
QTimer with 1000 ms interval
Clock updates every second

Time Calculation
Hour hand moves smoothly with minutes
Minute hand reflects seconds
Second hand moves in one-second ticks

Project Files
AnalogClockWidget.h
AnalogClockWidget.cpp
main.cpp

Usage
Set the widget as the central widget of a QMainWindow.
QMainWindow window;
window.setCentralWidget(new AnalogClockWidget);
window.resize(400, 400);
window.show();

Requirements
Qt 5 or Qt 6
Qt Widgets module
C++ compiler

Notes
The clock is fully drawn in paintEvent()
All elements are proportional to widget size
No memory leaks
