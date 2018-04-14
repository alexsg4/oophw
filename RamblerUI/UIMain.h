#pragma once
#include "wx/wx.h"


class UIMain : public wxApp
{
private:
	const wxString ATitle = wxT("Rambler Garage");
	const wxString AVersion = wxT("0.1.0");

public:
	virtual bool OnInit() override;
};

