/**
 * @file Month.cpp
 * @author Jacob Hughes
 */

#include "pch.h"
#include "Month.h"
#include "Day.h"
#include "Tracker.h"
#include "Year.h"

using namespace std;


/// normal font used for drawing days
const wxFont font(wxSize(0, 20),
        wxFONTFAMILY_SWISS,
        wxFONTSTYLE_NORMAL,
        wxFONTWEIGHT_NORMAL);

/**
 * Constructor
 * @param tracker The tracker this month is a member of
 */
 Month::Month(Tracker *tracker, int days, std::wstring name,Year* year) : mTracker(tracker), mName(name), mYear(year)
{
    for (int i = 0; i < days; i++)
    {
        auto day = make_shared<Day>(tracker,this);
        mDays.push_back(day);
    }
}


/**
 * Draw the month view
 * @param graphics the graphics to draw on
 * @param date the date that we are drawing
 * @param scaleX optional param used for drawing all months in a year
 * @param scaleY optional param used for drawing all months in a year
 * @param yearMonth optional param used for drawing the year
 */
void Month::Draw(std::shared_ptr<wxGraphicsContext> graphics, std::vector<int> date,
        double scaleX,double scaleY, int yearMonth,std::wstring option)
{
    int year = date[0];
    int month = date[1];
    int day = date[2];

    if (option == L"Day" || option == L"Week")
    {
        mDays[day-1]->Draw(graphics, option);
        return;
    }

    // ensures that the drawing of the year is not dependent on current month
    else if (yearMonth != 0)
    {
        date[1] = yearMonth;
        month = yearMonth;
    }

    bool leap = mTracker->CheckLeapYear(year);

    int count = mStartDayMap[mTracker->FindStartingDay(date,L"Month")];

    map <int,wstring> weekMap = {{1,L"S"},{2,L"M"},{3,L"T"},
            {4,L"W"},{5,L"T"},{6,L"F"},{7,L"S"}};

    wxColour color = mTracker->GetTextColor();

    int newCount = 1;
    int index = 0;
    mMonthDateMap.clear();

    for (int i = 1; i < 7; ++ i)
    {
        // add i to the map to tell week num of event
        for (int j = 0; j < 7; ++j)
        {
            auto xLoc = (100 + (155*j) * .25) + scaleX;
            auto yLoc = ((120 * i) * .25) + scaleY;

            if (mTracker->GetState() == 3) // we only draw boxes for month state
            {
                xLoc = (100 + (155*j));
                yLoc = (120 * i);
                auto w = 150;
                auto h = 110;
                graphics->DrawRectangle(xLoc, yLoc, w, h);
            }
            else if (mTracker->GetState() == 4 && i == 1) // year state
            {
                // make the text light grey before drawing to differentiate days
                graphics->SetFont(font, wxColour(211, 211, 211));
                graphics->DrawText(weekMap[j+1], xLoc, yLoc - ((120 * i) * .25));
                // set font back to normal coloring
                graphics->SetFont(font, color);
            }

            if (count > 0 && count <= mMonthDayMap[month] ||
                    (count > 0 && count <= mMonthDayMap[month] + 1 && leap && month == 2))
            {
                if (count == mTracker->GetActualDay() && month == mTracker->GetActualMonth())
                {
                    graphics->SetFont(font,wxColour(255,0,0));
                    graphics->DrawText(to_wstring(count), xLoc, yLoc);
                    graphics->SetFont(font,mTracker->GetTextColor());
                }
                else
                {
                    graphics->DrawText(to_wstring(count), xLoc, yLoc);
                }

                mMonthDateMap[index] = {year,month,count};
                mDrawMonthMap[index] = i;


            }
            else if (count <= 0)
            {
                // make the text light grey before drawing since new month
                graphics->SetFont(font, wxColour(211, 211, 211));

                if(month == 3 && leap)
                {
                    graphics->DrawText(to_wstring(count + mMonthDayMap[month - 1] + 1),
                            xLoc, yLoc);
                    mMonthDateMap[index] = {year,month - 1,count + mMonthDayMap[month - 1] + 1};
                    mDrawMonthMap[index] = i;
                }
                else if (month != 1)
                {
                    graphics->DrawText(to_wstring(count + mMonthDayMap[month - 1]),
                            xLoc, yLoc);
                    mMonthDateMap[index] = {year,month - 1,count + mMonthDayMap[month - 1]};
                    mDrawMonthMap[index] = i;
                }
                else
                {
                    graphics->DrawText(to_wstring(count + mMonthDayMap[12]),
                            xLoc, yLoc);
                    mMonthDateMap[index] = {year,12,count + mMonthDayMap[12]};
                    mDrawMonthMap[index] = i;
                }

                // set font back to normal coloring
                graphics->SetFont(font, color);
            }
            else if (count > mMonthDayMap[month])
            {
                // make the text light grey before drawing since new month
                graphics->SetFont(font, wxColour(211, 211, 211));

                graphics->DrawText(to_wstring(newCount),
                        xLoc, yLoc);

                if (month == 12)
                {
                    mMonthDateMap[index] = {year + 1,1,newCount};
                    mDrawMonthMap[index] = i;
                }
                else
                {
                    mMonthDateMap[index] = {year,month + 1,newCount};
                    mDrawMonthMap[index] = i;
                }


                // set font back to normal coloring
                graphics->SetFont(font, color);

                newCount++;
            }
            count++;
            index++;
        }
    }

    mTracker->SetMonthDateMap(mMonthDateMap);
    mTracker->SetDrawMonthMap(mDrawMonthMap);


}

