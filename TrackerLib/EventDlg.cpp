/**
 * @file EventDlg.cpp
 * @author Jacob Hughes
 */

#include "pch.h"
#include "EventDlg.h"
#include <wx/xrc/xmlres.h>
#include <wx/valnum.h>
#include <utility>
#include "ProjectView.h"
#include <codecvt>


/**
 * Constructor
 * @param parent The parent window we will center in
 * @param view the Project View
 * @param tracker the Tracker
 * @param event the event
 */
EventDlg::EventDlg(wxWindow* parent,ProjectView *view, Tracker tracker, std::shared_ptr<StandardEvent> event) :
    mTracker(tracker),mView(view), mEvent(event)
{
    wxXmlResource::Get()->LoadDialog(this, parent, L"EventDlg");

    mYearValue = mTracker.GetRecentEventYear();
    mMonthValue = mTracker.GetRecentEventMonth();
    mDayValue = mTracker.GetRecentEventDay();

    auto yearCtrl = XRCCTRL(*this, "EventDlgYear", wxControl);
    wxIntegerValidator<int> yearValidator(&mYearValue);
    yearValidator.SetRange(0, 2100);
    yearCtrl->SetValidator(yearValidator);

    auto monthCtrl = XRCCTRL(*this, "EventDlgMonth", wxControl);
    wxIntegerValidator<int> monthValidator(&mMonthValue);
    monthValidator.SetRange(0, 12);
    monthCtrl->SetValidator(monthValidator);

    auto dayCtrl = XRCCTRL(*this, "EventDlgDay", wxControl);
    wxIntegerValidator<int> dayValidator(&mDayValue);
    dayValidator.SetRange(0, 31);
    dayCtrl->SetValidator(dayValidator);

    auto typeCtrl = XRCCTRL(*this,"EventDlgType",wxControl);
    wxTextValidator typeValidator(1,&mWxTypeStr);
    typeCtrl->SetValidator(typeValidator);

    auto descriptionCtrl = XRCCTRL(*this,"EventDlgDescription",wxControl);
    wxTextValidator descriptionValidator(1,&mWxDescriptionStr);
    descriptionCtrl->SetValidator(descriptionValidator);

    auto startCtrl = XRCCTRL(*this,"EventDlgStart",wxControl);
    wxTextValidator startValidator(1,&mWxStartStr);
    startCtrl->SetValidator(startValidator);

    auto endCtrl = XRCCTRL(*this,"EventDlgEnd",wxControl);
    wxTextValidator endValidator(1,&mWxEndStr);
    endCtrl->SetValidator(endValidator);

    Bind(wxEVT_BUTTON, &EventDlg::OnOK, this, wxID_OK);
}


/**
 * Handle an OK button press
 * @param event Button event
 */
void EventDlg::OnOK(wxCommandEvent& event)
{
    if (mView->CheckValidDate(mYearValue,mMonthValue,mDayValue)
    && Validate() && TransferDataFromWindow())
    {
        // Success! Set values in the class
        mEvent->SetEventYear(mYearValue);
        mEvent->SetEventMonth(mMonthValue);
        mEvent->SetEventDay(mDayValue);

        // convert wx string to string, then to wstring
        std::string typeString = std::string(mWxTypeStr.mb_str());
        mTypeValue = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(typeString);

        if (mTypeValue != L"Reminder" && mTypeValue != L"Workout" &&
                mTypeValue != L"Class" && mTypeValue != L"Homework")
        {
            mTypeValue = L"Other";
        }

        mEvent->SetType(mTypeValue);
        mEvent->SetImageName(mTypeValue);

        // convert wx string to string, then to wstring
        std::string descriptionString = std::string(mWxDescriptionStr.mb_str());
        mDescriptionValue = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(descriptionString);

        if (mDescriptionValue == L"None")
        {
            mDescriptionValue = L"";
        }

        mEvent->SetEventDescription(mDescriptionValue);

        std::string startString = std::string(mWxStartStr.mb_str());
        mStartValue = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(startString);

        mEvent->SetStart(mStartValue);

        std::string endString = std::string(mWxEndStr.mb_str());
        mEndValue = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(endString);

        mEvent->SetEnd(mEndValue);

        mTracker.SetRecentEventYear(mYearValue);
        mTracker.SetRecentEventMonth(mMonthValue);
        mTracker.SetRecentEventDay(mDayValue);

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
