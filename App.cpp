
#include "App.h"
#include "MainFrame.h"
#include "pomodoro.h"

#include <wx/wx.h>


wxIMPLEMENT_APP(App);


bool App::OnInit() {
	wxInitAllImageHandlers();

	MainFrame* mainFrame = new MainFrame("Pomodoro");
	wxSetEnv("QT_QPA_PLATFORM", "minimal");

	mainFrame->SetClientSize(1000, 600);
	mainFrame->SetMinSize(wxSize(1000, 600));
	mainFrame->SetMaxSize(wxSize(1000, 600));
	mainFrame->Center();
	mainFrame->Show();
	return true;
}