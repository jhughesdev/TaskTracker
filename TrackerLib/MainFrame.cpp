/**
 * @file MainFrame.cpp
 * @author Jacob Hughes
 */

#include "pch.h"
#include "MainFrame.h"
#include "ids.h"
#include <wx/xrc/xmlres.h>
#include <wx/stdpaths.h>
#include "PictureFactory.h"


/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    wxXmlResource::Get()->LoadFrame(this, nullptr, L"MainFrame");

#ifdef WIN32
    // This sets the frame icon on Windows systems
    SetIcon(wxIcon(L"mainframe", wxBITMAP_TYPE_ICO_RESOURCE));
#endif

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);

    auto standardPaths = wxStandardPaths::Get();
    auto imagesDir = standardPaths.GetResourcesDir().ToStdWstring() + L"Resources";
    // Create our picture
    PictureFactory factory;
    mPicture = factory.Create(imagesDir);

    // Tell the views about the picture
    mProjectView.SetPicture(mPicture);

    mProjectView.Initialize(this);

}

/**
 * Exit menu option handlers
 * @param event the event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}


/**
 * About menu option handler
 * @param event the event
 */
void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(L"Welcome to the Tracker! \n"
                 "Developed by Jacob Hughes 2023 \n"
                 "Check out my LinkedIn below! \n"
                 "https://www.linkedin.com/in/jacob-hughes-0735a723a",
            L"Task Tracker",
            wxOK,
            this);
}
