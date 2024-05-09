// Windoof GUI Application
#include "includes.h"

// Static member variable to store the list box
wxListBox* MainGUI::lbFiles = nullptr;

// Constructor for MainGUI class
MainGUI::MainGUI() : wxFrame(nullptr, wxID_ANY, "Windoof")
{
	// Initialize check boxes
	int checkBoxX = 10;
	int checkBoxY = 10;
	int checkBoxSpacing = 30;

	// Check box to delete temp files
	cbTemp = new wxCheckBox(this, wxID_ANY, "Delete Temp Files?", wxPoint(checkBoxX, checkBoxY));

	// Check box to delete install files
	cbInstallFiles = new wxCheckBox(this, wxID_ANY, "Delete Install Files?",
	                                wxPoint(checkBoxX, checkBoxY + checkBoxSpacing));

	// Check box to delete Chrome cache
	cbCache = new wxCheckBox(this, wxID_ANY, "Delete Cache?",
	                         wxPoint(checkBoxX, checkBoxY + 2 * checkBoxSpacing));

	// Check box to delete cookies
	cbCookies = new wxCheckBox(this, wxID_ANY, "Delete Cookies?", wxPoint(checkBoxX, checkBoxY + 3 * checkBoxSpacing));

	// Check box to clear Recycle Bin
	cbRecycleBin = new wxCheckBox(this, wxID_ANY, "Clear Recycle Bin",
	                              wxPoint(checkBoxX + 200, checkBoxY + 3 * checkBoxSpacing));

	// Initialize list box
	int listBoxX = 10;
	int listBoxY = 150;
	int listBoxWidth = 300;
	int listBoxHeight = 100;
	lbFiles = new wxListBox(this, wxID_ANY, wxPoint(listBoxX, listBoxY), wxSize(listBoxWidth, listBoxHeight));

	// Initialize clear button
	clearButton = new wxButton(this, wxID_ANY, "Clear", wxPoint(listBoxX, listBoxY + listBoxHeight + 10),
	                           wxSize(50, 20));

	// Bind button click event handler
	clearButton->Bind(wxEVT_BUTTON, &MainGUI::OnClean_Clicked, this);
}

// Update GUI method
void MainGUI::UpdateGui()
{
	// Check if list box is null
	if (lbFiles == nullptr)
		return;

	// Update list box
	lbFiles->Update();
	// Set selection to the last item in the list box
	lbFiles->SetSelection(lbFiles->GetCount() - 1);
}

// Event handler for clear button click
void MainGUI::OnClean_Clicked(wxCommandEvent& event)
{
	// Check if log is not open
	//if (!Log::IsOpen)
	//{
		// Open console log
	//	Log::OpenConsole();
	//	Log::IsOpen = true;
	//}

	// Check if temp files checkbox is checked
	if (cbTemp->IsChecked())
	{
		// Delete temp files
		Delete::DeleteTempFiles();
		Delete::DeleteWindowsTempFiles();
		// Uncheck temp files checkbox
		cbTemp->SetValue(false);
	}

	// Check if install files checkbox is checked
	if (cbInstallFiles->IsChecked())
	{
		// Delete install files
		Delete::DeleteWindowsInstallFiles();
		// Uncheck install files checkbox
		cbInstallFiles->SetValue(false);
	}

	// Check if Cache checkbox is checked
	if (cbCache->IsChecked())
	{
		// Close all browsers
		if (ProcessManagement::IsProcessRunning("msedge.exe"))
		{
			ProcessManagement::ForceClose("msedge.exe");
		}

		if (ProcessManagement::IsProcessRunning("chrome.exe"))
		{
			ProcessManagement::ForceClose("chrome.exe");
		}

		if (ProcessManagement::IsProcessRunning("opera.exe"))
		{
			ProcessManagement::ForceClose("opera.exe");
		}

		if (ProcessManagement::IsProcessRunning("firefox.exe"))
		{
			ProcessManagement::ForceClose("firefox.exe");
		}

		if (ProcessManagement::IsProcessRunning("brave.exe"))
		{
			ProcessManagement::ForceClose("brave.exe");
		}


		// Delete cache
		Delete::DeleteBrowserCaches();
		// Uncheck Cache checkbox
		cbCache->SetValue(false);
	}

	// Check if cookies checkbox is checked
	if (cbCookies->IsChecked())
	{
		// Force close browsers
		ProcessManagement::ForceClose("msedge.exe");
		ProcessManagement::ForceClose("chrome.exe");
		ProcessManagement::ForceClose("opera.exe");
		ProcessManagement::ForceClose("firefox.exe");

		// Delete cookies
		Delete::DeleteCookies();

		// Uncheck cookies checkbox
		cbCookies->SetValue(false);
	}


	// Check if Recycle Bin checkbox is checked
	if (cbRecycleBin->IsChecked())
	{
		// Clear Recycle Bin
		Delete::DeleteRecycleBin();
		// Uncheck Recycle Bin checkbox
		cbRecycleBin->SetValue(false);
	}

	// Append separator and "Finished!" message to list box
	lbFiles->AppendString(L"------------------------------");
	lbFiles->AppendString(L"Finished!");

	// Update GUI
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
