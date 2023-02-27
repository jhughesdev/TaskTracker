/**
 * @file TrackerApp.cpp
 * @author Jacob Hughes
 */


#include "pch.h"
#include "TrackerApp.h"
#include <MainFrame.h>
#include <wx/xrc/xmlres.h>
#include <wx/stdpaths.h>

/**
* Initialize our app
 * @return true
*/
bool TrackerApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    // Add image type handlers
    wxInitAllImageHandlers();

    // Do not remove this line...
    wxSetWorkingDirectory(L"..");

    // Get pointer to XML resource system
    auto xmlResource = wxXmlResource::Get();

    // Initialize XRC handlers
    xmlResource->InitAllHandlers();

    // Load all XRC resources from the program resources
    auto& standardPaths = wxStandardPaths::Get();
    if (!wxXmlResource::Get()->LoadAllFiles(standardPaths.GetResourcesDir()))
    {
        return false;
    }

    auto frame = new MainFrame();
    frame->Initialize();
    frame->Show(true);

    return true;

}