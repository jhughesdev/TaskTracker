/**
 * @file ColorDlg.h
 * @author Jacob Hughes
 *
 *
 */

#ifndef TESTTRACKER22_COLORDLG_H
#define TESTTRACKER22_COLORDLG_H

#include "Tracker.h"

class ProjectView;

/**
 * Color dialog box class
 */
class ColorDlg : public wxDialog{
private:

    /// Red color value for text
    int mRedValue = 0;

    /// Green color value for text
    int mGreenValue = 0;

    /// Blue color value for text
    int mBlueValue = 0;

    /// The Tracker
    Tracker mTracker;

    /// The Project View
    ProjectView* mView = nullptr;

    /// Number to determine what RGB values we are changing
    int mNumber = 0;

public:

    ColorDlg(wxWindow* parent, ProjectView *view, Tracker tracker, int number);

    void OnOK(wxCommandEvent& event);

    /**
     * Set the number
     * @param number to set
     */
    void SetNumber(int number) {mNumber = number;}
};

#endif //TESTTRACKER22_COLORDLG_H
