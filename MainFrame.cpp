#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/dirdlg.h>
#include <wx/filename.h>
#include <wx/bitmap.h>
#include <wx/spinctrl.h>
#include <wx/dir.h> 
#include "pomodoro.h"
#include "DrawingCanvas.h"
#include <wx/image.h>
#include <thread>
#include <wx/mimetype.h>
#include <wx/sound.h>


using namespace std;
DrawingCanvas* canvas;
DrawingCanvas* canvasSPT;
DrawingCanvas* canvasIMG;
DrawingCanvas* breakIMG;
MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
	wxPanel* panel = new wxPanel(this);
	panel->SetBackgroundColour(RGB(133,133,133));


	//Buttons
	catch2B = new wxButton(panel, wxID_ANY, "Catch2", wxPoint(910, 0), wxSize(-1, 32));
	button = new wxButton(panel, wxID_ANY, "Start a Session!", wxPoint(0, (600 / 2) - 17), wxSize(150, 35));
	buttonStop = new wxButton(panel, wxID_ANY, "End the session!", wxPoint(0, (600 / 2) - 17), wxSize(150, 35));
	buttonPause = new wxButton(panel, wxID_ANY, "Pause", wxPoint(0, 329), wxSize(-1, 32));
	buttonunPause = new wxButton(panel, wxID_ANY, "unPause", wxPoint(0, 329), wxSize(-1, 32));
	getStatistics = new wxButton(panel, wxID_ANY, "Get current Statistics", wxPoint(10, 46), wxSize(-1, -1));

	buttonPause->Hide();
	buttonunPause->Hide();
	buttonStop->Hide();

	userBox = new wxComboBox(panel, wxID_ANY, "Load Users", wxPoint(10, 15), wxSize(-1, -1));
	loadButton = new wxButton(panel, wxID_ANY, "Load", wxPoint(160, 15), wxSize(40, 25));
	createButton = new wxButton(panel, wxID_ANY, "Create", wxPoint(140, 46), wxSize(-1, -1));
	Delbutton = new wxButton(panel, wxID_ANY, "Delete", wxPoint(120, 15), wxSize(40, 25));
	inputSession = new wxSpinCtrl(panel, wxID_ANY, " ", wxPoint(150, 285), wxSize(-1, 32));
	breakSession = new wxSpinCtrl(panel, wxID_ANY, " ", wxPoint(190, 285), wxSize(-1, 32));


	//Coloring the buttons gray
	catch2B->SetForegroundColour(RGB(133, 133, 133));
	getStatistics->SetForegroundColour(RGB(133, 133, 133));
	userBox->SetForegroundColour(RGB(133, 133, 133));
	loadButton->SetForegroundColour(RGB(133, 133, 133));
	createButton->SetForegroundColour(RGB(133, 133, 133));
	Delbutton->SetForegroundColour(RGB(133, 133, 133));
	inputSession->SetForegroundColour(RGB(133, 133, 133));
	breakSession->SetForegroundColour(RGB(133, 133, 133));
	buttonPause->SetForegroundColour(RGB(133, 133, 133));
	buttonunPause->SetForegroundColour(RGB(133, 133, 133));
	buttonStop->SetForegroundColour(RGB(133, 133, 133));
	button->SetForegroundColour(RGB(133, 133, 133));

	//Coloring the button's text grey
	catch2B->SetOwnForegroundColour(RGB(0, 0, 0));
	button->SetOwnForegroundColour(RGB(0, 0, 0));
	getStatistics->SetOwnForegroundColour(RGB(0, 0, 0));
	userBox->SetOwnForegroundColour(RGB(0, 0, 0));
	loadButton->SetOwnForegroundColour(RGB(0, 0, 0));
	createButton->SetOwnForegroundColour(RGB(0, 0, 0));
	Delbutton->SetOwnForegroundColour(RGB(0, 0, 0));
	inputSession->SetOwnForegroundColour(RGB(0, 0, 0));
	breakSession->SetOwnForegroundColour(RGB(0, 0, 0));
	buttonPause->SetOwnForegroundColour(RGB(0, 0, 0));
	buttonunPause->SetOwnForegroundColour(RGB(0, 0, 0));
	buttonStop->SetOwnForegroundColour(RGB(0, 0, 0));

	//binds
	createButton->Bind(wxEVT_BUTTON, &MainFrame::OnCreateTextFile, this);
	Delbutton->Bind(wxEVT_BUTTON, &MainFrame::onDelButtonClicked, this);
	buttonStop->Bind(wxEVT_BUTTON, &MainFrame::onEndSession, this);
	catch2B->Bind(wxEVT_BUTTON, &MainFrame::OnRunTests, this);

	button->Bind(wxEVT_BUTTON, &MainFrame::OnStartSession, this);
	buttonPause->Bind(wxEVT_BUTTON, &MainFrame::onPaused, this);
	buttonunPause->Bind(wxEVT_BUTTON, &MainFrame::onUnPaused, this);
	loadButton->Bind(wxEVT_BUTTON, &MainFrame::onLoadButtonClicked, this);
	getStatistics->Bind(wxEVT_BUTTON, &MainFrame::onGetStatistics, this);


	//pomodoro settings for a default session
	inputSession->SetRange(1, 60);
	inputSession->SetValue(25);
	
	breakSession->SetRange(1, 60);
	breakSession->SetValue(5);

	
	button->SetDoubleBuffered(true);
	PopulateUserBox();

	//Images configurations
	canvas = new DrawingCanvas(panel);
	canvasSPT = new DrawingCanvas(panel);
	canvasIMG = new DrawingCanvas(panel);
	breakIMG = new DrawingCanvas(panel);

	canvas->SetSize(wxSize(450, 450));  
	canvas->SetPosition(wxPoint(438, (1000/2)-450));
	canvas->LoadImage("Resources/tomato.bmp");
	canvas->SetText("00:00", 163,195);
	
	//Size(s) configurator
	canvasSPT->SetSize(wxSize(450, 450));
	canvasSPT->SetPosition(wxPoint(438, (1000/2)-450));
	canvasSPT->SetFont(canvasSPT->GetFont().Scale(2.38f));
	canvas->SetFont(canvas->GetFont().Scale(5));

	breakIMG->SetSize(wxSize(300, 300));
	breakIMG->SetPosition(wxPoint(-300, 250));

	breakIMG->LoadImage("Resources/breaktime.bmp");

	canvasIMG->SetSize(wxSize(1,520));
	canvasIMG->SetPosition(wxPoint(300,25));
	canvasIMG->LoadImage("Resources/line.bmp");




}

pomodoro* pom = new pomodoro;

//Catch2 button
void MainFrame::OnRunTests(wxCommandEvent& event) {
	
	wxString exePath = "Catch2 Tests/Catch.bat";
	wxExecute(exePath, wxEXEC_ASYNC | wxEXEC_SHOW_CONSOLE, NULL);
}

//Start Session button, plays a sound and then it proceeds on changing the visuals & starts the timer
void MainFrame::OnStartSession(wxCommandEvent& evt) {
	wxString soundFile = wxT("Audio/ding.wav");
	wxSound::Play(soundFile, wxSOUND_ASYNC);
	button->HideWithEffect(wxSHOW_EFFECT_SLIDE_TO_LEFT);
	buttonStop->ShowWithEffect(wxSHOW_EFFECT_SLIDE_TO_RIGHT);
	buttonPause->ShowWithEffect(wxSHOW_EFFECT_SLIDE_TO_RIGHT);
	std::thread timerThread(&pomodoro::startSession, pom, inputSession->GetValue(), breakSession->GetValue(),inputSession, breakSession, breakIMG, canvas, canvasSPT, button, buttonStop, buttonPause, buttonunPause, userBox);
	timerThread.detach();
}

//End Session button, ends the session
void MainFrame::onEndSession(wxCommandEvent& evt) {
	pom->endSession(); 
	inputSession->ShowWithEffect(wxSHOW_EFFECT_SLIDE_TO_LEFT); inputSession->Hide();inputSession->Show();
	breakSession->ShowWithEffect(wxSHOW_EFFECT_SLIDE_TO_LEFT); breakSession->Hide();breakSession->Show();
	buttonStop->HideWithEffect(wxSHOW_EFFECT_SLIDE_TO_LEFT);
	button->ShowWithEffect(wxSHOW_EFFECT_SLIDE_TO_RIGHT);
	buttonPause->HideWithEffect(wxSHOW_EFFECT_SLIDE_TO_LEFT);
	buttonunPause->HideWithEffect(wxSHOW_EFFECT_SLIDE_TO_LEFT);
}
//Pause button, pauses the timer
void MainFrame::onPaused(wxCommandEvent& evt) {
	buttonPause->HideWithEffect(wxSHOW_EFFECT_SLIDE_TO_LEFT);
	buttonunPause->ShowWithEffect(wxSHOW_EFFECT_SLIDE_TO_RIGHT);
	pom->PauseSession();
}
//Unpause button, unpauses the timer
void MainFrame::onUnPaused(wxCommandEvent& evt) {
	buttonunPause->HideWithEffect(wxSHOW_EFFECT_SLIDE_TO_LEFT);
	buttonPause->ShowWithEffect(wxSHOW_EFFECT_SLIDE_TO_RIGHT);
	
	pom->unPauseSession();
}
//User profile delete button, With the user's intended name for the profile, it creates a profile with 0 stats
void MainFrame::onDelButtonClicked(wxCommandEvent& evt) {
	int selectedIndex = userBox->GetSelection();

	if (selectedIndex != wxNOT_FOUND) {
		wxString selectedUser = userBox->GetString(selectedIndex);
		wxString folderPath = wxGetCwd() + wxFILE_SEP_PATH + "Statistics";
		wxString filePath = folderPath + wxFILE_SEP_PATH + selectedUser + ".txt";

		if (wxFile::Exists(filePath)) {
			if (wxRemoveFile(filePath)) {
				wxMessageBox("Profile deleted!", "Success", wxOK | wxICON_INFORMATION);
				
			}
			else {
				wxMessageBox("Failed to delete the file.", "Error", wxOK | wxICON_ERROR);
			}
			userBox->SetSelection(1);
		}
		else {
			wxMessageBox("File not found.", "Error", wxOK | wxICON_ERROR);
		}

		userBox->Delete(selectedIndex);
	}
	userBox->SetSelection(wxNOT_FOUND);
}
void MainFrame::SelectLatestTextFile() {
	wxString folderPath = wxGetCwd() + wxFILE_SEP_PATH + "Statistics";
	wxArrayString fileNames;

	wxDir dir(folderPath);
	if (dir.IsOpened()) {
		wxString filename;
		bool cont = dir.GetFirst(&filename, wxEmptyString, wxDIR_FILES);

		while (cont) {
			fileNames.Add(filename);
			cont = dir.GetNext(&filename);
		}
	}

	wxString latestFile;
	wxFileName latestFileDate;

	for (const wxString& fileName : fileNames) {
		wxFileName fileDate(folderPath + wxFILE_SEP_PATH + fileName);

		if (!latestFileDate.IsOk() || fileDate.GetModificationTime() > latestFileDate.GetModificationTime()) {
			latestFile = fileName;
			latestFileDate = fileDate;
		}
	}

	if (!latestFile.IsEmpty()) {
		int index = userBox->FindString(latestFile);
		if (index != wxNOT_FOUND) {
			userBox->SetSelection(index);
		}
	}
}

//Loads up the userbox combobox
void MainFrame::PopulateUserBox()
{
	userBox->Clear();
	wxString currentDir = wxGetCwd();
	wxString statisticsDir = wxFileName::DirName(currentDir).GetPath() + wxFILE_SEP_PATH + "Statistics";

	wxDir dir(wxT("Statistics"));
	if (dir.IsOpened())
	{
		wxString filename;
		bool cont = dir.GetFirst(&filename, wxEmptyString, wxDIR_FILES);

		while (cont)
		{
			wxString nameWithoutExtension = filename.BeforeLast('.');
			userBox->Append(nameWithoutExtension);
			cont = dir.GetNext(&filename);
		}
	}

	userBox->SetSelection(0); 
	SelectLatestTextFile();
}

//Create a profile button
void MainFrame::OnCreateTextFile(wxCommandEvent& event) {
	wxString userText = userBox->GetValue();

	if (!userText.IsEmpty()) {
		wxString currentDir = wxGetCwd();
		wxString folderPath = currentDir + wxFILE_SEP_PATH + "Statistics";
		wxString filePath = folderPath + wxFILE_SEP_PATH + userText + ".txt";

		if (wxFileName::DirExists(folderPath) || wxMkdir(folderPath, 0777)) {
			wxFile file(filePath, wxFile::write);
			if (file.IsOpened()) {
				wxString fileContent = "Sessions Completed: 0\nTotal work time: 0\n";
				file.Write(fileContent);
				file.Close();
				wxMessageBox("Profile created!", "Success", wxOK | wxICON_INFORMATION);
				PopulateUserBox();
			}
		}
	}
}


//Statistics button
void MainFrame::onGetStatistics(wxCommandEvent& evt) {
	pom->getStatistics(userBox);

}

//Load button
void MainFrame::onLoadButtonClicked(wxCommandEvent& evt)
{
	PopulateUserBox();
	
}


