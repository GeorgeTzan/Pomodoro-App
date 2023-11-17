#pragma once
#include "App.h"
#include <condition_variable>
#include <mutex>
#include <iostream>
#include "MainFrame.h"
#include <thread>
class DrawingCanvas;
class pomodoro {
public:
    void startSession(int workminutes, int breakminutes, wxSpinCtrl* inputSession, wxSpinCtrl* breakInput, DrawingCanvas* breakIMG, DrawingCanvas* canvas, DrawingCanvas* canvasSPT, wxButton* startButton, wxButton* stopButton, wxButton* pauseButton, wxButton* unpauseButton, wxComboBox* users);
    void endSession();
    void breakSession(int workminutes,int breakminutes, wxSpinCtrl* inputSession, wxSpinCtrl* breakInput, DrawingCanvas* breakIMG, DrawingCanvas* canvas, wxButton* startButton, wxButton* pauseButton, wxButton* unPauseButton, wxComboBox* users);
    void getStatistics(wxComboBox* users);
    void PauseSession();
    void unPauseSession();
    void pushRight(DrawingCanvas* canvas);
    void pushLeft(DrawingCanvas* canvas);
    bool isPaused = false;

private:
    DrawingCanvas* canvas;
    DrawingCanvas* canvasSPT;
    int workDuration;
    int breakDuration;
    int sessionsCompleted = 0;
    int totalWorkTime = 0;
    std::condition_variable stopCondition;
    std::mutex stopMutex;
    bool isWorking;
};

