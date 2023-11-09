#pragma once
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include "pomodoro.h"

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title);



private:
    wxSpinCtrl* inputSession;   
    wxButton* button;
    wxButton* catch2B;
    wxButton* buttonStop;
    wxButton* text; 
    wxButton* buttonPause;
    wxButton* buttonunPause;
    wxButton* getStatistics;
    wxCheckBox* soundBox;
    wxStaticText* pomodoroText;
    wxButton* createButton;
    wxString textFromCanvas;
    wxButton* Delbutton;
    wxSpinCtrl* breakSession;  
    void OnRunTests(wxCommandEvent& evt);
    void onGetStatistics(wxCommandEvent& evt);
    void onDelButtonClicked(wxCommandEvent& evt);
    void onLoadButtonClicked(wxCommandEvent& evt);
    void PopulateUserBox();
    void OnStartSession(wxCommandEvent& evt);
    void onEndSession(wxCommandEvent& evt);
    void onPaused(wxCommandEvent& evt);
    void onUnPaused(wxCommandEvent& evt);
    void OnCreateTextFile(wxCommandEvent& event);
    void SelectLatestTextFile();
    wxComboBox* userBox;
    wxButton* loadButton;
};
