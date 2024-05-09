#pragma once
#include "includes.h"

class Windoof : public wxApp
{
public:
	bool OnInit() override;
};

class MainGUI : public wxFrame
{
public:
	MainGUI();
	static wxListBox* lbFiles;
	static void UpdateGui();

private:
	void OnClean_Clicked(wxCommandEvent& event);
	// Elemente
	wxCheckBox* cbTemp;
	wxCheckBox* cbChromeCache;
	wxCheckBox* cbEdgeCache;
	wxCheckBox* cbCookies;
	wxCheckBox* cbRecycleBin;
	wxCheckBox* cbDeleteWindowsLogs;
	wxButton* testButton;
};
