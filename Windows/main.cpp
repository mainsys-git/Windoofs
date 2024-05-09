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
    cbTemp = new wxCheckBox(this, wxID_ANY, "Delete Temp Files?", wxPoint(checkBoxX, checkBoxY));
    // Check box to delete Chrome cache
    cbChromeCache = new wxCheckBox(this, wxID_ANY, "Delete Chrome Cache?",
        wxPoint(checkBoxX, checkBoxY + checkBoxSpacing));
    // Check box to delete Edge cache
    cbEdgeCache = new wxCheckBox(this, wxID_ANY, "Delete Edge Cache?",
        wxPoint(checkBoxX, checkBoxY + 2 * checkBoxSpacing));
    // Check box to delete cookies
    cbCookies = new wxCheckBox(this, wxID_ANY, "Delete Cookies?", wxPoint(checkBoxX, checkBoxY + 3 * checkBoxSpacing));

    // Check box to delete Windows logs
    cbDeleteWindowsLogs = new wxCheckBox(this, wxID_ANY, "Delete Windows Logs?",
        wxPoint(checkBoxX + 200, checkBoxY + checkBoxSpacing));

    // Check box to clear Recycle Bin
    cbRecycleBin = new wxCheckBox(this, wxID_ANY, "Clear Recycle Bin", wxPoint(checkBoxX + 200, checkBoxY));

    // Initialize list box
    int listBoxX = 10;
    int listBoxY = 150;
    int listBoxWidth = 300;
    int listBoxHeight = 100;
    lbFiles = new wxListBox(this, wxID_ANY, wxPoint(listBoxX, listBoxY), wxSize(listBoxWidth, listBoxHeight));

    // Initialize clear button
    testButton = new wxButton(this, wxID_ANY, "Clear", wxPoint(listBoxX, listBoxY + listBoxHeight + 10),
        wxSize(50, 20));

    // Bind button click event handler
    testButton->Bind(wxEVT_BUTTON, &MainGUI::OnClean_Clicked, this);
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
    if (!Log::IsOpen)
    {
        // Open console log
        Log::OpenConsole();
        Log::IsOpen = true;
    }

    // Check if temp files checkbox is checked
    if (cbTemp->IsChecked())
    {
        // Delete temp files
        Delete::DeleteTempFiles();
        Delete::DeleteWindowsTempFiles();
        // Uncheck temp files checkbox
        cbTemp->SetValue(false);
    }

    // Check if Chrome cache checkbox is checked
    if (cbChromeCache->IsChecked())
    {
        // Delete Chrome cache
        Delete::DeleteChromeCache();
        // Uncheck Chrome cache checkbox
        cbChromeCache->SetValue(false);
    }

    // Check if Edge cache checkbox is checked
    if (cbEdgeCache->IsChecked())
    {
        // Delete Edge cache
        Delete::DeleteEdgeCache();
        // Uncheck Edge cache checkbox
        cbEdgeCache->SetValue(false);
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

    // Check if Windows logs checkbox is checked
    if (cbDeleteWindowsLogs->IsChecked())
    {
        // Delete Windows temp files
        Delete::DeleteWindowsTempFiles();
        // Uncheck Windows logs checkbox
        cbDeleteWindowsLogs->SetValue(false);
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
