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
MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
	wxPanel* panel = new wxPanel(this);
	panel->SetBackgroundColour(RGB(133,133,133));


	//Buttons

	button = new wxButton(panel, wxID_ANY, "Ξεκίνα νεα συνεδρίαση", wxPoint(0, (600 / 2) - 17), wxSize(150, 35));
	buttonStop = new wxButton(panel, wxID_ANY, "Σταμάτα τη συνεδρίαση", wxPoint(0, (600 / 2) - 17), wxSize(150, 35));
	buttonPause = new wxButton(panel, wxID_ANY, "Pause", wxPoint(0, 329), wxSize(-1, 32));
	buttonunPause = new wxButton(panel, wxID_ANY, "unPause", wxPoint(0, 329), wxSize(-1, 32));
	getStatistics = new wxButton(panel, wxID_ANY, "Get current Statistics", wxPoint(10, 46), wxSize(-1, -1));

	buttonPause->Hide();
	buttonunPause->Hide();

	buttonStop->Hide();
	//wxColour backgroundColor(255, 255, 255, 128);

	userBox = new wxComboBox(panel, wxID_ANY, "Load Users", wxPoint(10, 15), wxSize(-1, -1));
	loadButton = new wxButton(panel, wxID_ANY, "Load", wxPoint(190, 15), wxSize(60, 25));
	createButton = new wxButton(panel, wxID_ANY, "Create", wxPoint(200, 100), wxSize(100, 30));
	Delbutton = new wxButton(panel, wxID_ANY, "Delete", wxPoint(120, 15), wxSize(40, 25));
	inputSession = new wxSpinCtrl(panel, wxID_ANY, " ", wxPoint(150, 285), wxSize(-1, 32));
	breakSession = new wxSpinCtrl(panel, wxID_ANY, " ", wxPoint(190, 285), wxSize(-1, 32));

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
	button->Bind(wxEVT_BUTTON, &MainFrame::OnStartSession, this);
	buttonPause->Bind(wxEVT_BUTTON, &MainFrame::onPaused, this);
	buttonunPause->Bind(wxEVT_BUTTON, &MainFrame::onUnPaused, this);
	loadButton->Bind(wxEVT_BUTTON, &MainFrame::onLoadButtonClicked, this);
	getStatistics->Bind(wxEVT_BUTTON, &MainFrame::onGetStatistics, this);


	
	inputSession->SetRange(1, 60);
	inputSession->SetValue(25);
	
	breakSession->SetRange(1, 60);
	breakSession->SetValue(5);

	
	button->SetDoubleBuffered(true);
	PopulateUserBox();

	canvas = new DrawingCanvas(panel);
	canvasSPT = new DrawingCanvas(panel);
	canvasIMG = new DrawingCanvas(panel);

	canvas->SetSize(wxSize(450, 450));  
	canvas->SetPosition(wxPoint(438, (1000/2)-450));
	canvas->LoadImage("tomato.bmp");
	canvas->SetText("00:00", 163,195);
	

	canvasSPT->SetSize(wxSize(450, 450));
	canvasSPT->SetPosition(wxPoint(438, (1000/2)-450));
	// size changer
	canvasSPT->SetFont(canvasSPT->GetFont().Scale(2.38f));
	canvas->SetFont(canvas->GetFont().Scale(5));

	canvasIMG->SetSize(wxSize(1,520));
	canvasIMG->SetPosition(wxPoint(300,25));
	canvasIMG->LoadImage("line.bmp");


}

pomodoro* pom = new pomodoro;


void MainFrame::OnStartSession(wxCommandEvent& evt) {
	button->Hide();
	buttonStop->Show();
	buttonPause->Show();
	
	std::thread timerThread(&pomodoro::startSession, pom, inputSession->GetValue(), breakSession->GetValue(), canvas, canvasSPT, button, buttonStop, buttonPause, buttonunPause, userBox);
	timerThread.detach();
}
void MainFrame::onEndSession(wxCommandEvent& evt) {
	pom->endSession(); 
	button->Show();
	buttonStop->Hide();
	buttonPause->Hide();
	buttonunPause->Hide();
}
void MainFrame::onPaused(wxCommandEvent& evt) {
	buttonPause->Hide();
	buttonunPause->Show();
	pom->PauseSession();
}
void MainFrame::onUnPaused(wxCommandEvent& evt) {
	buttonPause->Show();
	buttonunPause->Hide();
	pom->unPauseSession();
}
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

void MainFrame::onGetStatistics(wxCommandEvent& evt) {
	pom->getStatistics(userBox);

}
void MainFrame::onLoadButtonClicked(wxCommandEvent& evt)
{
	PopulateUserBox();
	//userBox->SetSelection(2);
}


