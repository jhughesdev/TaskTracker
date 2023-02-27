/**
 * @file ColorDlg.cpp
 * @author Jacob Hughes
 */

#include "pch.h"
#include "ColorDlg.h"
#include <wx/xrc/xmlres.h>
#include <wx/valnum.h>
#include "ProjectView.h"

#include <utility>

/**
 * Constructor
 * @param parent The parent window we will center in
 * @param view the Project View
 * @param Tracker the Tracker
 * @param number the number of the dialog box
 */
ColorDlg::ColorDlg(wxWindow* parent,ProjectView *view, Tracker tracker, int number) : mTracker(tracker), mView(view),
    mNumber(number)
{
    wxXmlResource::Get()->LoadDialog(this, parent, L"ColorDlg");

    if (mNumber == 0)
    {
        mRedValue = mTracker.GetRedDaysText();
        mGreenValue = mTracker.GetGreenDaysText();
        mBlueValue = mTracker.GetBlueDaysText();
    }
    else if (mNumber == 1)
    {
        mRedValue = mTracker.GetRedDaysBox();
        mGreenValue = mTracker.GetGreenDaysBox();
        mBlueValue = mTracker.GetBlueDaysBox();
    }
    auto redCtrl = XRCCTRL(*this, "ColorDlgRed", wxTextCtrl);
    wxIntegerValidator<int> redValidator(&mRedValue);
    redValidator.SetRange(0, 255);
    redCtrl->SetValidator(redValidator);

    auto greenCtrl = XRCCTRL(*this, "ColorDlgGreen", wxTextCtrl);
    wxIntegerValidator<int> greenValidator(&mGreenValue);
    greenValidator.SetRange(0, 255);
    greenCtrl->SetValidator(greenValidator);

    auto blueCtrl = XRCCTRL(*this, "ColorDlgBlue", wxTextCtrl);
    wxIntegerValidator<int> blueValidator(&mBlueValue);
    blueValidator.SetRange(0, 255);
    blueCtrl->SetValidator(blueValidator);

    Bind(wxEVT_BUTTON, &ColorDlg::OnOK, this, wxID_OK);


}

/**
 * Handle an OK button press
 * @param event Button event
 */
void ColorDlg::OnOK(wxCommandEvent& event)
{
    if ( Validate() && TransferDataFromWindow() )
    {
        // Success! Set values in the class
        if (mNumber == 0)
        {
            mTracker.SetRedDaysText(mRedValue);
            mTracker.SetGreenDaysText(mGreenValue);
            mTracker.SetBlueDaysText(mBlueValue);
        }

        else if (mNumber == 1)
        {
            mTracker.SetRedDaysBox(mRedValue);
            mTracker.SetGreenDaysBox(mGreenValue);
            mTracker.SetBlueDaysBox(mBlueValue);
        }

        mView->SetTracker(mTracker);
        EndModal(wxID_OK);
    }
}

