## **Pomodoro University Assignment**

Code written by Giorgos Tzanopoulos & Konstandinos Zenullari
<br>Art designed by Konstandinos Zenullari

![](https://github.com/GeorgeTzan/Pomodoro-App/blob/master/Resources/gui.png)

## Features
- Set customizable work sessions and break durations.
- Pause, resume, and stop timer functionality.
- Load and save user profiles.
- Track session statistics.

## Prerequisites
-C++ Compiler (e.g., GCC)
<br>-wxWidgets Library installed

## Creating a profile

In order to create a profile, you write in the box the name of the profile and you simply press the 'Create' button.
![](https://github.com/GeorgeTzan/Pomodoro-App/blob/master/gif.gif)

## Installation

To compile and run the application, use the following command:

```bash
  g++ app.cpp mainframe.cpp pomodoro.cpp drawingcanvas.cpp `wx-config --libs --cxxflags` -pthread -o Pomodoro
```
## Caution

Runs mainly in Windows. In order to run it in a different OS like linux, the code must be slightly changed like:
- RGB -> wxColour
- file names are case sensitive (drawingcanvas.cpp != DrawingCanvas.cpp)
