#include "UIMain.h"
#include "UIMainFrame.h"

IMPLEMENT_APP(UIMain)

bool UIMain::OnInit()
{
	UIMainFrame* MainFrame = new UIMainFrame(wxT("Rambler Garage"));
	MainFrame->Show(true);


	return true;
}

