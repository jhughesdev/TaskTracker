/**
 * @file DateDlg.cpp
 * @author Jacob Hughes
 */

#include "pch.h"
#include "DateDlg.h"
#include <wx/xrc/xmlres.h>
#include <wx/valnum.h>
#include <wx/validate.h>
#include "ProjectView.h"
#include <utility>

/**
 * Constructor
 * @param parent the parent window
 * @param view the project view
 * @param tracker the tracker
 */
DateDlg::DateDlg(wxWindow* parent, ProjectView* view, Tracker tracker) :mTracker(tracker), mView(view)
{
    wxXmlResource::Get()->LoadDialog(this, parent, L"DateDlg");

    mDay = mTracker.GetDay();
    mMonth = mTracker.GetMonth();
    mYear = mTracker.GetYear();

    auto yearCtrl = XRCCTRL(*this, "DateDlgYear", wxControl);
    wxIntegerValidator<int> yearValidator(&mYear);
    yearValidator.SetRange(0, 2100);
    yearCtrl->SetValidator(yearValidator);

    auto monthCtrl = XRCCTRL(*this, "DateDlgMonth", wxControl);
    wxIntegerValidator<int> monthValidator(&mMonth);
    monthValidator.SetRange(0, 12);
    monthCtrl->SetValidator(monthValidator);

    auto dayCtrl = XRCCTRL(*this, "DateDlgDay", wxControl);
    wxIntegerValidator<int> dayValidator(&mDay);
    dayValidator.SetRange(0, 31);
    dayCtrl->SetValidator(dayValidator);

    Bind(wxEVT_BUTTON, &DateDlg::OnOK, this, wxID_OK);
}


/**
 * Handle the ok click of the dialog box
 * @param event the command event
 */
void DateDlg::OnOK(wxCommandEvent& event)
{
    // && TransferDataFromWindow()
    if ( Validate() && TransferDataFromWindow() &&
        mView->CheckValidDate(mYear,mMonth,mDay))
    {
        // Success! Set values in the class
        mTracker.SetDay(mDay);

        bool changedRefresh = false;

        // do not need to refresh month view if month and year do not change
        if (mTracker.GetMonth() == mMonth && mTracker.GetState() == 3
                && mTracker.GetYear() == mYear)
        {
            mRefresh = false;
            changedRefresh = true;
        }
        else
        {
            mTracker.SetMonth(mMonth);
        }

        // do not need to refresh year view if year does not change
        if ((mTracker.GetYear() == mYear && mTracker.GetState() == 4))
        {
            mRefresh = false;
        }
        else
        {
            mTracker.SetYear(mYear);
            if (!changedRefresh)
            {
                mRefresh = true;
            }
        }

        mView->SetTracker(mTracker);
        EndModal(wxID_OK);
    }
    else
    {
        // raise exception that the date entered is incorrect
        wxDialog dialog(wxTheApp->GetTopWindow(), wxID_ANY, L"Invalid User Entry");

        dialog.SetSizeHints(wxDefaultSize, wxDefaultSize);

        auto sizer = new wxBoxSizer(wxVERTICAL);

        auto m_staticText1 = new wxStaticText(&dialog, wxID_ANY, L"Enter a valid date",
                wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL);
        m_staticText1->Wrap(300);
        sizer->Add(m_staticText1, 0, wxALL | wxEXPAND, 15);

        auto m_button1 = new wxButton(&dialog, wxID_OK, wxT("Ok"), wxDefaultPosition, wxDefaultSize, 0);
        sizer->Add(m_button1, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

        dialog.SetSizer(sizer);
        dialog.Layout();
        sizer->Fit(&dialog);

        dialog.Centre(wxBOTH);
        dialog.ShowModal();
    }

}



