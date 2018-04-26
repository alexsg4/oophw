#include "UIMain.h"

bool UIMain::OnInit()
{
	wxInitAllImageHandlers();
	UIMainFrame* MainFrame = new UIMainFrame(ALTitle);
	MainFrame->Show(true);

	return true;
}

IMPLEMENT_APP(UIMain)
