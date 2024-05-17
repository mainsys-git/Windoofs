// Windoof GUI Application
#include "includes.h"

// Static member variable to store the list box
wxListBox* MainGUI::lbFiles = nullptr;

// Constructor for MainGUI class
MainGUI::MainGUI() : wxFrame(nullptr, wxID_ANY, "Windoof") {
    // Create a panel to hold all the widgets
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    // Create a vertical box sizer to manage the layout
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    // Create a grid sizer for the checkboxes
    wxGridSizer* gridSizer = new wxGridSizer(2, 2, 10, 10); // Adjust the rows and columns as needed

    // Initialize check boxes
    cbTemp = new wxCheckBox(panel, wxID_ANY, "Delete Temp Files?");
    cbInstallFiles = new wxCheckBox(panel, wxID_ANY, "Delete Install Files?");
    cbCache = new wxCheckBox(panel, wxID_ANY, "Delete Cache?");
    cbCookies = new wxCheckBox(panel, wxID_ANY, "Delete Cookies?");
    cbRecycleBin = new wxCheckBox(panel, wxID_ANY, "Clear Recycle Bin");

    // Set default values
    cbCache->SetValue(true);
    cbTemp->SetValue(true);
    cbRecycleBin->SetValue(true);

    // Apply flat design styles to check boxes
    wxFont checkBoxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    wxColour checkBoxBgColor(236, 240, 241);
    wxColour checkBoxTextColor(52, 73, 94);

    auto checkBoxes = {cbTemp, cbInstallFiles, cbCache, cbCookies, cbRecycleBin};
    for (auto checkBox : checkBoxes) {
        checkBox->SetFont(checkBoxFont);
        checkBox->SetBackgroundColour(checkBoxBgColor);
        checkBox->SetForegroundColour(checkBoxTextColor);
    }

    // Add check boxes to the grid sizer
    gridSizer->Add(cbTemp, 0, wxEXPAND);
    gridSizer->Add(cbInstallFiles, 0, wxEXPAND);
    gridSizer->Add(cbCache, 0, wxEXPAND);
    gridSizer->Add(cbCookies, 0, wxEXPAND);
    gridSizer->Add(cbRecycleBin, 0, wxEXPAND);

    // Add the grid sizer to the vertical box sizer
    vbox->Add(gridSizer, 0, wxALL | wxEXPAND, 10);

    // Initialize list box
    lbFiles = new wxListBox(panel, wxID_ANY, wxDefaultPosition, wxSize(300, 100));
    lbFiles->SetBackgroundColour(wxColour(255, 255, 255));
    lbFiles->SetForegroundColour(checkBoxTextColor);
    vbox->Add(lbFiles, 0, wxALL | wxEXPAND, 10);

    // Initialize clear button
    clearButton = new wxButton(panel, wxID_ANY, "Clear");
    clearButton->SetBackgroundColour(wxColour(231, 76, 60));
    clearButton->SetForegroundColour(wxColour(255, 255, 255));
    clearButton->SetFont(wxFont(14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    vbox->Add(clearButton, 0, wxALL | wxALIGN_CENTER, 10);

    // Set the panel sizer
    panel->SetSizer(vbox);

    // Bind button click event handler
    clearButton->Bind(wxEVT_BUTTON, &MainGUI::OnClean_Clicked, this);

    // Fit the frame to the sizer
    vbox->Fit(panel);
    vbox->SetSizeHints(panel);

    // Apply flat design to the panel
    panel->SetBackgroundColour(wxColour(236, 240, 241));
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
	//Check if log is not open
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
		//Delete::DeleteWindowsTempFiles();
		// Uncheck temp files checkbox
		cbTemp->SetValue(false);
	}

	// Check if install files checkbox is checked
	if (cbInstallFiles->IsChecked())
	{
		// Delete install files
		Delete::DeleteWindowsInstallationFiles();
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
	MainGUI* mainFrame = new MainGUI();
	mainFrame->Show(true);
	mainFrame->SetSize(700, 300);
	mainFrame->SetMaxSize(wxSize(1920, 300));
	mainFrame->SetMinSize(wxSize(700, 300));
	return true;
}

wxIMPLEMENT_APP(Windoof);
