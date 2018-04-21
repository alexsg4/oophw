#include "RIndexListModel.h"

RIndexListModel::RIndexListModel(RArray<Vehicle*> & _fleet, const unsigned initSize) 
	: wxDataViewVirtualListModel(initSize)
{
	fleet = &_fleet;

}

void RIndexListModel::GetValueByRow(wxVariant & variant, unsigned row, unsigned col) const
{
}

bool RIndexListModel::SetValueByRow(const wxVariant & variant, unsigned int row, unsigned int col)
{
	return false;
}

unsigned int RIndexListModel::GetColumnCount() const
{
	return 6;
}

unsigned int RIndexListModel::GetRowCount() const
{
	return fleet->size();
}

unsigned RIndexListModel::GetCount() const
{
	return fleet->size();
}

wxString RIndexListModel::GetColumnType(unsigned int col) const
{
	return wxString();
}
