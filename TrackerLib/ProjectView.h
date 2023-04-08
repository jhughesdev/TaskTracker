/**
 * @file ProjectView.h
 * @author Jacob Hughes
 *
 *
 */

#ifndef TESTTRACKER22_PROJECTVIEW_H
#define TESTTRACKER22_PROJECTVIEW_H

#include "Tracker.h"
#include "PictureObserver.h"


/**
 * View class for the project
 */
class ProjectView : public wxWindow, public PictureObserver {
private:

    /// An object that describes our Tracker
    Tracker mTracker;

    void OnPaint(wxPaintEvent & event);

public:

    void OnFileOpen(wxCommandEvent& event);

    void OnFileSaveAs(wxCommandEvent& event);

    void Initialize(wxFrame* parent);

    void AddEventCustom(wxCommandEvent& event);

    void OnEditColorPropertiesDayText(wxCommandEvent& event);

    void OnEditColorPropertiesDayBox(wxCommandEvent& event);

    void OnWinterTheme(wxCommandEvent& event);

    void OnSpringTheme(wxCommandEvent& event);

    void OnSummerTheme(wxCommandEvent& event);

    void OnFallTheme(wxCommandEvent& event);

    void OnDarkTheme(wxCommandEvent& event);

    /**
     * Redraw the window, used now to support more views if wanted
     */
    void UpdateObserver() override {Refresh();}

    /**
     * Set the tracker
     * @param tracker the tracker to set
     */
    void SetTracker(Tracker tracker) {mTracker = tracker;}

    void OnRemoveRecent(wxCommandEvent& event);

    void OnRemoveAll(wxCommandEvent& event);

    void ChangeStateDay(wxCommandEvent& event);

    void ChangeStateWeek(wxCommandEvent& event);

    void ChangeStateMonth(wxCommandEvent& event);

    void ChangeStateYear(wxCommandEvent& event);

    void ChangeCurrentDate(wxCommandEvent& event);

    bool CheckValidDate(int year,int month, int days);

    void OnInstructions(wxCommandEvent& event);

};

#endif //TESTTRACKER22_PROJECTVIEW_H
