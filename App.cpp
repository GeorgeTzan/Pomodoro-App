
#include "App.h"
#include "MainFrame.h"
#include "pomodoro.h"

#include <wx/wx.h>


wxIMPLEMENT_APP(App);


bool App::OnInit() {
	wxInitAllImageHandlers();

	wxIcon icon("tomato.ico", wxBITMAP_TYPE_ICO);	

	MainFrame* mainFrame = new MainFrame("Pomodoro by Zenullari Konstandinos & Tzanopoulos Georgios");
	mainFrame->SetIcons(icon);
	wxSetEnv("QT_QPA_PLATFORM", "minimal");

	mainFrame->SetClientSize(1000, 600);
	mainFrame->SetMinSize(wxSize(1000, 600));
	mainFrame->SetMaxSize(wxSize(1000, 600));
	mainFrame->Center();
	mainFrame->Show();
	return true;
}