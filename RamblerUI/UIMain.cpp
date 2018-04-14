#include "UIMain.h"
#include "UIMainFrame.h"

IMPLEMENT_APP(UIMain)

bool UIMain::OnInit()
{
	UIMainFrame* MainFrame = new UIMainFrame(ALTitle);
	MainFrame->Show(true);


	return true;
}

