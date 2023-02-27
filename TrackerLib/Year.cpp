/**
 * @file Year.cpp
 * @author Jacob Hughes
 */

#include "pch.h"
#include "Year.h"
#include "Month.h"
#include "StandardEvent.h"
#include "Tracker.h"

using namespace std;

/// normal font used for drawing days
const wxFont font(wxSize(0, 20),
        wxFONTFAMILY_SWISS,
        wxFONTSTYLE_NORMAL,
        wxFONTWEIGHT_NORMAL);

/**
 * Constructor
 * @param tracker The tracker this year is a member of
 */
Year::Year(Tracker *tracker, int year) : mTracker(tracker), mYearNum(year)
{
    for (int i = 1; i <= 12; ++i)
    {
        auto month = make_shared<Month>(tracker,mMonthDayMap[i],mMonthMap[i],this);
        if (i == 2 && mTracker->CheckLeapYear(year))
        {
            month = make_shared<Month>(tracker,mMonthDayMap[i] + 1,mMonthMap[i],this);
        }
        mMonths.push_back(month);
    }
}


/**
 * Draw the year
 * @param graphics the graphics to draw on
 * @param x the x location
 * @param y the y location
 */
void Year::Draw(std::shared_ptr<wxGraphicsContext> graphics, std::vector<int> date,std::wstring option)
{
    int month = date[1];
    int scaleX = 0;
    int scaleY = 0;
    if (option == L"Day" || option == L"Week" || option == L"Month")
    {
        mMonths[month - 1]->Draw(graphics,date,scaleX,scaleY,0,option);
        return;
    }
    else if (option == L"Year")
    {
        for (int i = 1; i < 13; ++i,++date[1])
        {
            // adjust x scaling
            if (i==1 || i==5 || i==9)
            {
                scaleX = 0;
            }
            else if (i==2 || i==6 || i==10)
            {
                scaleX = 300;
            }
            else if (i==3 || i==7 || i==11)
            {
                scaleX = 600;
            }
            else if (i==4 || i==8 || i==12)
            {
                scaleX = 900;
            }

            //adjust y scaling
            if (i==1 || i==2 || i==3 || i==4)
            {
                scaleY = 100;
            }
            else if (i==5 || i==6 || i==7 || i==8)
            {
                scaleY = 380;
            }
            else if (i==9 || i==10 || i==11 || i==12)
            {
                scaleY = 660;
            }

            graphics->DrawText(mMonthMap[i],scaleX + 100,scaleY - 25);
            mMonths[i - 1]->Draw(graphics,date,scaleX,scaleY,i);

        }
    }
}


