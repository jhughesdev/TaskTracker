/**
 * @file ProjectView.cpp
 * @author Jacob Hughes
 */

#include "pch.h"
#include "ProjectView.h"
#include <wx/dcbuffer.h>
#include "ids.h"
#include "StandardEvent.h"
#include <wx/xrc/xmlres.h>
#include "ColorDlg.h"
#include "Picture.h"
#include "PictureObserver.h"
#include "EventDlg.h"
#include "DateDlg.h"

using namespace std;

/**
 * Initialize the project view class.
 * @param parent The parent window for this class
 */
void ProjectView::Initialize(wxFrame* parent)
{
    Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE);
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &ProjectView::OnPaint, this);

    //parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &ProjectView::AddEventNormal, this, IDM_ADDEVENTNORMAL);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &ProjectView::OnFileOpen, this, wxID_OPEN);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &ProjectView::OnFileSaveAs, this, wxID_SAVEAS);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &ProjectView::OnInstructions,
            this, XRCID("Instructions"));

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &ProjectView::AddEventCustom,
            this, XRCID("EventProperties"));

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,
            &ProjectView::OnEditColorPropertiesDayText, this,
            XRCID("EditColorPropertiesDayText"));

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,
            &ProjectView::OnEditColorPropertiesDayBox, this,
            XRCID("EditColorPropertiesDayBox"));

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,
            &ProjectView::OnRemoveRecent, this,
            XRCID("RemoveRecent"));

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,
            &ProjectView::OnRemoveAll, this,
            XRCID("RemoveAll"));

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,
            &ProjectView::ChangeStateDay, this,
            XRCID("DayView"));

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,
            &ProjectView::ChangeStateWeek, this,
            XRCID("WeekView"));

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,
            &ProjectView::ChangeStateMonth, this,
            XRCID("MonthView"));

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,
            &ProjectView::ChangeStateYear, this,
            XRCID("YearView"));

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,
            &ProjectView::ChangeCurrentDate, this,
            XRCID("SelectDate"));

    mTracker.Initialize();
    mTracker.SetPView(this);

}

/**
* Paint event, draws the window
 * @param event The paint event
*/
void ProjectView::OnPaint(wxPaintEvent & event)
{

    wxAutoBufferedPaintDC dc(this);
    wxBrush background(*wxWHITE);
    dc.SetBackground(background);

    auto size = GetClientSize();

    auto graphics =
            std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create( dc ));
    graphics->SetInterpolationQuality(wxINTERPOLATION_BEST);

    mTracker.OnDraw(graphics);
}


/**
 * Add a normal event to the tracker
 * @param event
 */
void ProjectView::AddEventCustom(wxCommandEvent& event)
{
    // Tracker* tracker,int year, int month, int day, std::wstring type
    auto stdEvent = make_shared<StandardEvent>(&mTracker,0,0,0,
            L"",L"",L"",L"");
    EventDlg dlg(this,this,mTracker,stdEvent);
    if (dlg.ShowModal() == wxID_OK)
    {
        // The dialog box has changed the Color settings
        GetPicture()->UpdateObservers();

        // now that the event is updated we can add it
        mTracker.AddEvent(stdEvent);
    }
}


/**
 * Handle an Edit>Color Properties... menu option
 * @param event The menu event
 */
void ProjectView::OnEditColorPropertiesDayText(wxCommandEvent& event)
{
    ColorDlg dlg(this,this,mTracker,0);
    if(dlg.ShowModal() == wxID_OK)
    {
        // The dialog box has changed the Color settings
        GetPicture()->UpdateObservers();
    }
}


/**
 * Handle an Edit>Color Properties... menu option
 * @param event The menu event
 */
void ProjectView::OnEditColorPropertiesDayBox(wxCommandEvent& event)
{
    ColorDlg dlg(this,this,mTracker,1);
    if(dlg.ShowModal() == wxID_OK)
    {
        // The dialog box has changed the Color settings
        GetPicture()->UpdateObservers();
    }
}

/**
* Remove the most recent event from the tracker
 * @param event The menu event
*/
void ProjectView::OnRemoveRecent(wxCommandEvent& event)
{
    mTracker.RemoveRecent();
    Refresh();
}


/**
* Remove all of the event from the tracker for the year
 * @param event The menu event
*/
void ProjectView::OnRemoveAll(wxCommandEvent& event)
{
    mTracker.RemoveAll();
    Refresh();
}


/**
 * Change the state to day
 * @param event The menu event
 */
void ProjectView::ChangeStateDay(wxCommandEvent& event)
{
    mTracker.SetState(1);
    Refresh();
}

/**
 * Change the state to week
 * @param event The menu event
 */
void ProjectView::ChangeStateWeek(wxCommandEvent& event)
{
    mTracker.SetState(2);
    Refresh();
}

/**
 * Change the state to month
 * @param event The menu event
 */
void ProjectView::ChangeStateMonth(wxCommandEvent& event)
{
    mTracker.SetState(3);
    Refresh();
}


/**
 * Change the state to year
 * @param event The menu event
 */
void ProjectView::ChangeStateYear(wxCommandEvent& event)
{
    mTracker.SetState(4);
    Refresh();
}


/**
* Change the current date of the tracker
 * @param event The menu event
*/
void ProjectView::ChangeCurrentDate(wxCommandEvent& event)
{
    //make dialog box for the year, user can enter a validated year
    DateDlg dlg(this,this,mTracker);
    if(dlg.ShowModal() == wxID_OK)
    {
        // The dialog box has changed the date

        // avoid unnecessary refreshes
        if (dlg.GetRefresh())
        {
            GetPicture()->UpdateObservers();
        }
    }
}




/**
 * Check if the amount of days are valid depending on the month given
 * @param year the year
 * @param month the month represented as an int (1 for jan, 12 for dec)
 * @param days the amount of days for the month
 * @return true if valid, false if invalid
 */
bool ProjectView::CheckValidDate(int year,int month, int days)
{
    if (year < 2022)
    {
        return false;
    }
    if (month == 1 || month == 3 || month == 5|| month == 7
            || month == 8 || month == 10 || month == 12)
    {
        if (days <= 31)
        {
            return true;
        }
        return false;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (days <= 30)
        {
            return true;
        }
        return false;
    }
    else if (month == 2)
    {
        // check leap year
        if (mTracker.CheckLeapYear(year) && days <= 29 || !mTracker.CheckLeapYear(year) && days <= 28)
        {
            return true;
        }
        return false;
    }
    return false;
}


/**
 * File>Open menu handler
 * @param event Menu event
 */
void ProjectView::OnFileOpen(wxCommandEvent& event)
{
    wxFileDialog loadFileDialog(this, _("Load Tracker file"), "", "",
            "Tracker Files (*.tracker)|*.tracker", wxFD_OPEN);
    if (loadFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    auto filename = loadFileDialog.GetPath();
    mTracker.Load(filename);
    Refresh();
}


/**
 * File>Save As menu handler
 * @param event Menu event
 */
void ProjectView::OnFileSaveAs(wxCommandEvent& event)
{
    wxFileDialog saveFileDialog(this, _("Save Tracker file"), "", "",
            "Tracker Files (*.tracker)|*.tracker", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    auto filename = saveFileDialog.GetPath();
    mTracker.Save(filename);
}


/**
 * Instructions Menu Handler
 * @param event Menu event
 */
void ProjectView::OnInstructions(wxCommandEvent& event)
{
    wxMessageBox(L"Add events using options at the top! \n"
                 "Add events to certain dates, set the date to see desired date. \n"
                 "Choose desired view with options at top \n"
                 "You can save your Tracker by using File->Save, and load a currently Saved Tracker with File->Load \n",
            L"Task Tracker",
            wxOK,
            this);
}