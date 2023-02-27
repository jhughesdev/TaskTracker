/**
 * @file EventDlg.h
 * @author Jacob Hughes
 *
 *
 */

#ifndef TESTTRACKER22_EVENTDLG_H
#define TESTTRACKER22_EVENTDLG_H

class ProjectView;
#include "Tracker.h"
#include "StandardEvent.h"


/**
 * Class for the event dialog box
 */
class EventDlg : public wxDialog {
private:

    /// The year of the event
    int mYearValue = 2023;

    /// The month of the event
    int mMonthValue = 1;

    /// The day of the event
    int mDayValue = 1;

    /// The type of event
    std::wstring mTypeValue;

    /// type value as a wxStr
    wxString mWxTypeStr = L"Reminder";

    /// description value as a wxStr
    wxString mWxDescriptionStr = L"None";

    /// start time value as a wxStr
    wxString mWxStartStr = L"9:00 AM";

    /// end time value as a wxStr
    wxString mWxEndStr = L"1";

    /// description value
    std::wstring mDescriptionValue;

    /// start time value
    std::wstring mStartValue;

    /// end time value
    std::wstring mEndValue;

    /// The Tracker
    Tracker mTracker;

    /// The Project View
    ProjectView* mView = nullptr;

    /// The event
    std::shared_ptr<StandardEvent> mEvent;

public:

    void OnOK(wxCommandEvent& event);

    EventDlg(wxWindow* parent,ProjectView *view, Tracker tracker, std::shared_ptr<StandardEvent> event);

};

#endif //TESTTRACKER22_EVENTDLG_H
