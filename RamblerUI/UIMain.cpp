#include "UIMain.h"

IMPLEMENT_APP(UIMain)

bool UIMain::OnInit()
{
	UIMainFrame* MainFrame = new UIMainFrame(ALTitle);
	MainFrame->Show(true);
	
	//TODO ensure success before returning true

	return true;
}

