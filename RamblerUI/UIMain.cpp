#include "UIMain.h"

IMPLEMENT_APP(UIMain)

bool UIMain::OnInit()
{
	UIMainFrame* MainFrame = new UIMainFrame(ALTitle);
	MainFrame->Show(true);
	
	
	//TODO testing
	UIGarageFrame* GarageFrame = new UIGarageFrame(ALTitle);
	GarageFrame->Show(true);

	return true;
}

