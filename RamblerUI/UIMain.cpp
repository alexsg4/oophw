#include "UIMain.h"
#include "UIMainFrame.h"

IMPLEMENT_APP(UIMain)

bool UIMain::OnInit()
{
	UIMainFrame* MainFrame = new UIMainFrame(ATitle + " v" + AVersion);
	MainFrame->Show(true);


	return true;
}

