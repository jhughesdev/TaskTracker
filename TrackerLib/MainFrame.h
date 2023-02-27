/**
 * @file MainFrame.h
 * @author Jacob Hughes
 *
 *
 */

#ifndef TESTTRACKER22_MAINFRAME_H
#define TESTTRACKER22_MAINFRAME_H

#include "ProjectView.h"

class MainFrame : public wxFrame{
private:

    /// The Project View
    ProjectView mProjectView;

    /// The picture object we are viewing/editing
    std::shared_ptr<Picture> mPicture;


public:

    void Initialize();

    void OnExit(wxCommandEvent& event);

    void OnAbout(wxCommandEvent& event);
};

#endif //TESTTRACKER22_MAINFRAME_H
