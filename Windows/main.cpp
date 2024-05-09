#include "includes.h"

// Definition des statischen Elements
wxListBox* MainGUI::lbFiles = nullptr;

MainGUI::MainGUI() : wxFrame(nullptr, wxID_ANY, "Windoof")
{
	// CheckBoxes
	int checkBoxX = 10;
	int checkBoxY = 10;
	int checkBoxSpacing = 30;
	cbTemp = new wxCheckBox(this, wxID_ANY, "Delete Temp Files?", wxPoint(checkBoxX, checkBoxY));
	cbChromeCache = new wxCheckBox(this, wxID_ANY, "Delete Chrome Cache?",
	                               wxPoint(checkBoxX, checkBoxY + checkBoxSpacing));
	cbEdgeCache = new wxCheckBox(this, wxID_ANY, "Delete Edge Cache?",
	                             wxPoint(checkBoxX, checkBoxY + 2 * checkBoxSpacing));
	cbCookies = new wxCheckBox(this, wxID_ANY, "Delete Cookies?", wxPoint(checkBoxX, checkBoxY + 3 * checkBoxSpacing));

	// Delete Windows Logs Checkbox
	cbDeleteWindowsLogs = new wxCheckBox(this, wxID_ANY, "Delete Windows Logs?",
	                                     wxPoint(checkBoxX + 200, checkBoxY + checkBoxSpacing));

	// Recycle Bin Checkbox
	cbRecycleBin = new wxCheckBox(this, wxID_ANY, "Clear Recycle Bin", wxPoint(checkBoxX + 200, checkBoxY));

	// ListBox
	int listBoxX = 10;
	int listBoxY = 150;
	int listBoxWidth = 300;
	int listBoxHeight = 100;
	lbFiles = new wxListBox(this, wxID_ANY, wxPoint(listBoxX, listBoxY), wxSize(listBoxWidth, listBoxHeight));

	// Button
	testButton = new wxButton(this, wxID_ANY, "Clear", wxPoint(listBoxX, listBoxY + listBoxHeight + 10),
	                          wxSize(50, 20));

	// Bind Button Click Handler
	testButton->Bind(wxEVT_BUTTON, &MainGUI::OnClean_Clicked, this);
}


void MainGUI::UpdateGui()
{
	if (lbFiles == nullptr)
		return;;

	lbFiles->Update();
	lbFiles->SetSelection(lbFiles->GetCount() - 1);
}

void MainGUI::OnClean_Clicked(wxCommandEvent& event)
{
	if (!Log::IsOpen)
	{
		Log::OpenConsole();
		Log::IsOpen = true;
	}
		

	if (cbTemp->IsChecked())
	{
		Delete::DeleteTempFiles();
		Delete::DeleteWindowsTempFiles();
		cbTemp->SetValue(false);
	}

	if (cbChromeCache->IsChecked())
	{
		Delete::DeleteChromeCache();
		cbChromeCache->SetValue(false);
	}

	if (cbEdgeCache->IsChecked())
	{
		Delete::DeleteEdgeCache();
		cbEdgeCache->SetValue(false);
	}

	if (cbCookies->IsChecked())
	{
		ProcessManagement::ForceClose("msedge.exe");
		ProcessManagement::ForceClose("chrome.exe");
		ProcessManagement::ForceClose("opera.exe");
		ProcessManagement::ForceClose("firefox.exe");


		Delete::DeleteCookies();

		cbCookies->SetValue(false);
	}

	if (cbDeleteWindowsLogs->IsChecked())
	{
		Delete::DeleteWindowsTempFiles();
		cbDeleteWindowsLogs->SetValue(false);
	}


	if (cbRecycleBin->IsChecked())
	{
		Delete::DeleteRecycleBin();
		cbRecycleBin->SetValue(false);
	}

	lbFiles->AppendString(L"------------------------------");
	lbFiles->AppendString(L"Finished!");

	UpdateGui();
}

bool Windoof::OnInit()
{
	auto frame = new MainGUI();
	frame->SetSize(400, 330);
	frame->SetMinSize(wxSize(400, 330));
	frame->SetMaxSize(wxSize(400, 330));
	frame->SetBackgroundColour(wxColour(225, 225, 225));
	frame->Show(true);
	return true;
}

wxIMPLEMENT_APP(Windoof);
