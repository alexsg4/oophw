#pragma once
#include "Project.h"
#include <wx/dataview.h>

#include "RamblerU.h"


class RIndexListModel : public wxDataViewVirtualListModel
{
public:
	RIndexListModel(RArray<Vehicle*> & _fleet, const unsigned initSize);
	virtual ~RIndexListModel() {};

	virtual void GetValueByRow(wxVariant & variant, unsigned row, unsigned col) const override;

	virtual bool SetValueByRow(const wxVariant & variant, unsigned int row, unsigned int col) override;

	virtual unsigned GetColumnCount() const override;

	unsigned int GetRowCount() const;
	
	virtual unsigned GetCount() const override;

	virtual wxString GetColumnType(unsigned int col) const override;


private:
	RArray<Vehicle*> * fleet = nullptr;


};