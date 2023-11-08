
#define _CRT_SECURE_NO_WARNINGS
#include "pomodoro.h"
#include <iostream>
#include "wx/setup.h"
#include <fstream>
#include <wx/wx.h>
#include <wx/string.h>
#include <ctime>
#include <chrono>
#include "App.h"
#include <wx/sound.h>
#include "DrawingCanvas.h"
#include <chrono>
#include <thread>
#include <cstdlib>
using namespace std::chrono_literals;
using namespace std;
wxDECLARE_APP(App);

void pomodoro::startSession(int workminutes, int breakminutes, DrawingCanvas* canvas, DrawingCanvas* canvasSPT, wxButton* startButton, wxButton* stopButton, wxButton* pauseButton, wxButton* unpauseButton, wxComboBox* users) {
    int totalSeconds = workminutes * 60;
    int remainingSeconds = totalSeconds;

    isWorking = true;
    
    while (isWorking && remainingSeconds >= 0) {
        int minutes = remainingSeconds / 60;
        int seconds = remainingSeconds % 60;
        if (isPaused) {
            continue;
        }
        wxString message;
        if (minutes <= 9){
            message = wxString::Format("0%d:%02d", minutes, seconds);
            canvas->SetText(message, 163, 195);

        }
        else {
            message = wxString::Format("%d:%02d", minutes, seconds);
        }
        

        canvas->SetText(message, 163, 195);

        

        std::this_thread::sleep_for(std::chrono::seconds(1));

        remainingSeconds--;
    }

    std::unique_lock<std::mutex> lock(stopMutex);
    if (!isWorking) {
        canvas->SetText("", NULL, NULL);
        canvasSPT->SetText("Session stopped.", 130, 215);
        
        
        return;
    }
    wxString soundFile = wxT("Audio/MUSICAL.wav");
    wxSound::Play(soundFile, wxSOUND_ASYNC);

    startButton->Hide();
    stopButton->Hide();
    breakSession(workminutes,breakminutes, canvas, startButton, pauseButton, unpauseButton, users);

}


void pomodoro::endSession() {
    unPauseSession();
    std::unique_lock<std::mutex> lock(stopMutex);
    isWorking = false;
    stopCondition.notify_all();
}

void pomodoro::PauseSession() {
    std::unique_lock<std::mutex> lock(stopMutex);
    isPaused = true;
    stopCondition.notify_all();
}
void pomodoro::unPauseSession() {
    std::unique_lock<std::mutex> lock(stopMutex);
    isPaused = false;
    stopCondition.notify_all();
}
void pomodoro::breakSession(int workminutes, int breakminutes, DrawingCanvas* canvas,wxButton* startButton, wxButton* pauseButton, wxButton* unPauseButton, wxComboBox* users) {
    
    wxString selectedUser = users->GetValue();
    std::string filePath = "Statistics/" + std::string(selectedUser.mb_str()) + ".txt";
    

    std::ifstream inFile(filePath);
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            if (line.find("Sessions Completed: ") == 0) {
                sessionsCompleted = std::stoi(line.substr(20));
                sessionsCompleted++;
            }
            else if (line.find("Total work time: ") == 0) {
                totalWorkTime = std::stoi(line.substr(16));
                totalWorkTime += workminutes * 60;
            }
        }
        inFile.close();
    }

    std::ofstream outFile(filePath);
    if (outFile.is_open()) {
        outFile << "Sessions Completed: " << sessionsCompleted << std::endl;
        outFile << "Total work time: " << totalWorkTime << std::endl;
        outFile.close();
    }


    pauseButton->Hide();
    unPauseButton->Hide();
    int totalSeconds = breakminutes * 60;
    int remainingSeconds = totalSeconds;

    isWorking = true;

    while (isWorking && remainingSeconds >= 0) {
        int minutes = remainingSeconds / 60;
        int seconds = remainingSeconds % 60;
        wxString message;
        if (minutes <= 9){
            message = wxString::Format("0%d:%02d", minutes, seconds);
        }
        else {
            message = wxString::Format("%d:%02d", minutes, seconds);
        }
        
        canvas->SetText(message, 163, 195);

        std::this_thread::sleep_for(std::chrono::seconds(1));

        remainingSeconds--;
    }
    startButton->Show();
}
void pomodoro::getStatistics(wxComboBox* users) {
    wxString selectedUser = users->GetValue();

    std::string filePath = "Statistics/" + std::string(selectedUser.mb_str()) + ".txt";

    
    sessionsCompleted = 0;
    totalWorkTime = 0;

    std::ifstream inFile(filePath);
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            if (line.find("Sessions Completed: ") == 0) {
                sessionsCompleted = std::stoi(line.substr(20));
            }
            else if (line.find("Total work time: ") == 0) {
                totalWorkTime = std::stoi(line.substr(16));
            }
        }
        inFile.close();
    }
    else {
        wxString errorMessage = wxString::Format("Error reading user statistics for %s.", selectedUser);
        wxMessageBox(errorMessage, "Error", wxOK | wxICON_ERROR);
        return;
    }


    wxString message = wxString::Format(
        "%s: \nSessions Completed: %d\nTotal work time: %dh %dm %ds",
        selectedUser, sessionsCompleted,
        totalWorkTime / 3600, (totalWorkTime % 3600) / 60, totalWorkTime % 60);

    wxMessageBox(message, "Statistics", wxOK | wxICON_INFORMATION);
}
