Code written by Giorgos Tzanopoulos & Konstandinos Zenullari
Art designed by Konstandinos Zenullari

## **Pomodoro University Assignment**

## Features
- Set customizable work sessions and break durations.
- Pause, resume, and stop timer functionality.
- Load and save user profiles.
- Track session statistics.

## Prerequisites
-C++ Compiler
-wxWidgets installed

## Installation

To compile and run the application, use the following command:

```bash
g++ app.cpp mainframe.cpp pomodoro.cpp drawingcanvas.cpp `wx-config --libs --cxxflags` -pthread -o Pomodoro