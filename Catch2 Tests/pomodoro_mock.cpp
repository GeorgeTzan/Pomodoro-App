// pomodoro_mock.cpp
#include "pomodoro_mock.h"

bool PomodoroMock::PauseSession() {
    pause = true;
}
bool PomodoroMock::unPauseSession() {
    pause = false;
}