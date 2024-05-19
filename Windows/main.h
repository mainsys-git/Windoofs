#pragma once

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
    wxCheckBox* cbTemp;
    wxCheckBox* cbInstallFiles;
    wxCheckBox* cbCache;
    wxCheckBox* cbCookies;
    wxCheckBox* cbRecycleBin;

    wxButton* clearButton;

    void OnClean_Clicked(wxCommandEvent& event);
};
