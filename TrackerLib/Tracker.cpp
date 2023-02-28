/**
 * @file Tracker.cpp
 * @author Jacob Hughes
 */

#include "pch.h"
#include "Tracker.h"
#include "Item.h"
#include "StandardEvent.h"
#include "Year.h"
#include <chrono>
#include <iostream>
#include <wx/xml/xml.h>
#include <ctime>


using namespace std::chrono;
using namespace std;


/**
 * Smaller font
 * @return smallFont the font
 */
const wxFont smallFont(wxSize(0, 14),
        wxFONTFAMILY_SWISS,
        wxFONTSTYLE_NORMAL,
        wxFONTWEIGHT_NORMAL);

/**
 * The normal sized font used for drawing
 * @return font the font
 */
const wxFont font(wxSize(0, 20),
        wxFONTFAMILY_SWISS,
        wxFONTSTYLE_NORMAL,
        wxFONTWEIGHT_NORMAL);

/**
 * bigger font used for drawing months, and year
 * @return bigFont the font
 */
const wxFont bigFont(wxSize(50, 50),
        wxFONTFAMILY_SWISS,
        wxFONTSTYLE_NORMAL,
        wxFONTWEIGHT_NORMAL);




/**
 * Initialize the Tracker
 */
void Tracker::Initialize()
{
    for (int i = 2022; i <= 2100; ++i)
    {
        auto year = make_shared<Year>(this,i);
        mYears.push_back(year);
    }
    // set date to current date
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
//    mCurrentDay = int(now->tm_mday);
//    mCurrentMonth = int(now->tm_mon + 1);
//    mCurrentYear = int(now->tm_year + 1900);
    mActualDay = int(now->tm_mday);
    mActualMonth = int(now->tm_mon + 1);
    mActualYear = int(now->tm_year + 1900);
}


/**
 * Draw the Tracker
 * @param graphics the graphics to draw on
 */
void Tracker::OnDraw(std::shared_ptr<wxGraphicsContext> graphics)
{

    graphics->SetFont(font,wxColour(0,64,0));

    wxBrush brush(mBoxColor);

    graphics->SetBrush(brush);

    if (mState == 1) // day
    {
        wstring dateStr = mMonthMap[mCurrentMonth] + L" " +
                to_wstring(mCurrentDay) + L", " + to_wstring(mCurrentYear);

        graphics->SetFont(bigFont, mTextColor);

        graphics->DrawText(dateStr ,550, 0);

        graphics->SetFont(font, mTextColor);

        graphics->DrawRectangle(100, 125, 1250, 900);

        std::wstring dayStr = FindStartingDay(mCurrentDate,L"Day");

        mYears[mCurrentYear-mDefaultYear]->Draw(graphics,mCurrentDate,L"Day");

        // code to draw the time of events, not currently used in v1
//        graphics->SetFont(smallFont, mTextColor);
//        int time = 0;
//        std::wstring amPM;
//        int startInterval = 4;
//        for (int i = startInterval; i < 24; ++i)
//        {
//            time = i % 12;
//            if (time == 0)
//            {
//                time = 12;
//            }
//            if (i >= 12)
//            {
//                amPM = L"PM";
//            }
//            else
//            {
//                amPM = L"AM";
//            }
//            graphics->DrawText(to_wstring(time) + L":00" + amPM,40,i * 30 + 130);
//        }

        for (int i = 0; i<7; ++i)
        {
            // for the current day, just draw the number as the current day
            if (dayStr==mDayWeekMap[i+1])
            {
                graphics->SetFont(bigFont,mTextColor);
                graphics->DrawText(mDayWeekMap[i+1], 200, 75);
            }
        }

        wxBrush brush2(wxColour(255,255,255));
        graphics->SetBrush(brush2);

        for (int i = 0; i < static_cast<int>(mItemMap[mCurrentDate].size()); ++i)
        {
            graphics->DrawRectangle(125,150 + i * 85,1200,80);
            graphics->SetFont(font,wxColour(mRedDaysText,mGreenDaysText,
                    mBlueDaysText));
            graphics->DrawText(mItemMap[mCurrentDate][i]->GetEventDescription(),125,150 + i * 85);


            std::wstring imageName = mItemMap[mCurrentDate][i]->GetImageName();

            if (!mItemMap[mCurrentDate][i]->GetImageName().empty())
            {

                if (imageName == L"Reminder" || imageName == L"Workout")
                {
                    imageName += L".png";
                }
                else
                {
                    imageName += L".jpeg";
                }

                auto image = make_shared<wxImage>(L"Resources/" + imageName);


                auto bitmap = graphics->CreateBitmapFromImage(*image);

                int wid = 45;
                int hit = 40;
                graphics->DrawBitmap(bitmap, 125 + 1200 - wid, 150 + 85 * i, wid, hit);

            }

        }

    }

    else if (mState == 2) // week
    {

        std::wstring dayStr = FindStartingDay(mCurrentDate,L"Week");

        DrawDaysText(graphics,font,dayStr,L"Week");

        for (int i = 0; i<7; ++i)
        {
            graphics->DrawRectangle(100+155*i, 125, 150, 900);
        }

        graphics->SetFont(bigFont, mTextColor);

        graphics->DrawText(to_wstring(mWeekDateMap[0][1])
                + L" " + to_wstring(mWeekDateMap[0][2])
                + L" " + to_wstring(mWeekDateMap[0][0])
                + L" --- " + to_wstring(mWeekDateMap[6][1])
                + L" " + to_wstring(mWeekDateMap[6][2])
                + L" " + to_wstring(mWeekDateMap[6][0])
                , 500, 0);

        // draw the items within the week

        wxBrush brush2(wxColour(255,255,255));
        graphics->SetBrush(brush2);

        // Used to draw times, not currently used in v1
//        graphics->SetFont(smallFont, mTextColor);
//        int time = 0;
//        std::wstring amPM;
//        for (int i = 0; i < 24; ++i)
//        {
//            time = i % 12;
//            if (time == 0)
//            {
//                time = 12;
//            }
//            if (i >= 12)
//            {
//                amPM = L"PM";
//            }
//            else
//            {
//               amPM = L"AM";
//            }
//            graphics->DrawText(to_wstring(time) + L":00" + amPM,40,i * 30 + 130);
//        }

        for (int i = 0; i < static_cast<int>(mWeekDateMap.size()); ++i)
        {

            for (int j = 0; j < mItemMap[mWeekDateMap[i]].size(); ++j) // mItems size should be size for part. day
            {

                std::map<std::wstring,int> xLocMap {{L"Sun",100},
                        {L"Mon",255},{L"Tue",410},
                        {L"Wed",565},{L"Thu",720},
                        {L"Fri",875},{L"Sat",1030}};

                auto startDay = FindStartingDay(mWeekDateMap[i],L"Day");
                auto dateTwo = std::vector<int>{mItemMap[mWeekDateMap[i]][j]->GetEventYear(),
                        mItemMap[mWeekDateMap[i]][j]->GetEventMonth(),1};
                auto startNum = DistanceBetweenDates(mWeekDateMap[i],dateTwo);
                int weekNum = (startNum / 7);
                if (FindStartingDay(mWeekDateMap[i],L"Month") == L"Sat" &&
                    mItemMap[mWeekDateMap[i]][j]->GetEventDay() > 1)
                {
                    weekNum += 1;
                }

                graphics->DrawRectangle(xLocMap[startDay],140 + j * 36,150,35);
                graphics->SetFont(font,wxColour(mRedDaysText,mGreenDaysText,mBlueDaysText));
                graphics->DrawText(mItemMap[mWeekDateMap[i]][j]->GetEventDescription(),xLocMap[startDay]
                        ,140 + j * 36);

                std::wstring imageName = mItemMap[mWeekDateMap[i]][j]->GetImageName();

                if (!mItemMap[mWeekDateMap[i]][j]->GetImageName().empty())
                {
                    if (imageName == L"Reminder" || imageName == L"Workout")
                    {
                        imageName += L".png";
                    }
                    else
                    {
                        imageName += L".jpeg";
                    }

                    auto image = make_shared<wxImage>(L"Resources/" + imageName);


                    auto bitmap = graphics->CreateBitmapFromImage(*image);

                    int wid = 25;
                    int hit = 20;
                    graphics->DrawBitmap(bitmap, xLocMap[startDay] + 125, 140 + 41 * j, wid, hit);

                }

            }

        }

    }

    else if (mState == 3) // month
    {
        DrawDaysText(graphics,font);

        graphics->SetFont(bigFont, mTextColor);

        graphics->DrawText(mMonthMap[mCurrentMonth] + L" " + to_wstring(mCurrentYear), 575, 0);

        graphics->SetFont(font, mTextColor);

        mMonthDateMap.clear();

        mYears[mCurrentYear - mDefaultYear]->Draw(graphics,mCurrentDate,L"Month");

        // draw items for the month

        wxBrush brush2(wxColour(255,255,255));
        graphics->SetBrush(brush2);

//        for (int i = 0; i <= 31; ++i)
//        {
////            Tracker* tracker,int year, int month, int day, std::wstring type,
////                    std::wstring description, std::wstring start, std::wstring end
//            auto event = make_shared<StandardEvent>(this,2023,1,i,L"",
//                    L"TEST" +to_wstring(i),L"",L"");
//            AddEvent(event);
//        }

        std::wstring xLoc = L"";
        auto yLoc = 0;
        for (int i = 0; i < 42; ++i)
        {
            xLoc = FindStartingDay(mMonthDateMap[i],L"Day");
            for (int j = 0; j < mItemMap[mMonthDateMap[i]].size(); ++j) // mItems size should be size for part. day
            {

                std::map<std::wstring,int> xLocMap {{L"Sun",100},
                        {L"Mon",255},{L"Tue",410},
                        {L"Wed",565},{L"Thu",720},
                        {L"Fri",875},{L"Sat",1030}};

                std::map<int,int> yLocMap {{1,150},
                        {2,270},{3,390},
                        {4,510},{5,630},
                        {6,750}};

                if (j >= 4)
                {
                    if (j == 4)
                    {
                        graphics->SetFont(smallFont,wxColour(mRedDaysText,mGreenDaysText,mBlueDaysText));
                        graphics->DrawText(L"Switch views for more",
                                xLocMap[xLoc] + 10,yLocMap[mDrawMonthMap[i]] - 20);
                    }
                    break;
                }

                graphics->DrawRectangle(xLocMap[xLoc],yLocMap[mDrawMonthMap[i]] + 21 * j,150,20);
                graphics->SetFont(smallFont,wxColour(mRedDaysText,mGreenDaysText,mBlueDaysText));
                graphics->DrawText(mItemMap[mMonthDateMap[i]][j]->GetEventDescription(),
                        xLocMap[xLoc],yLocMap[mDrawMonthMap[i]] + 21 * j);

                std::wstring imageName = mItemMap[mMonthDateMap[i]][j]->GetImageName();

                if (!mItemMap[mMonthDateMap[i]][j]->GetImageName().empty())
                {
                    if (imageName == L"Reminder" || imageName == L"Workout")
                    {
                        imageName += L".png";
                    }
                    else
                    {
                        imageName += L".jpeg";
                    }

                    auto image = make_shared<wxImage>(L"Resources/" + imageName);


                    auto bitmap = graphics->CreateBitmapFromImage(*image);

                    int wid = 25;
                    int hit = 20;
                    graphics->DrawBitmap(bitmap, xLocMap[xLoc] + 120, yLocMap[mDrawMonthMap[i]] + 21 * j, wid, hit);

                }

            }
        }

    }

    else if (mState == 4) // year
    {
        graphics->SetFont(bigFont, mTextColor);

        graphics->DrawText(to_wstring(mCurrentYear), 50, 0);

        graphics->SetFont(font, mTextColor);

        mYears[mCurrentYear - mDefaultYear]->Draw(graphics,mCurrentDate);
    }

}


/**
 * Given two years, get the amount of leap years that occur between 2022-year entered
 * @param year the ending year
 * @param month the month
 * @return the number of leap years
 */
int Tracker::GetLeapYears(int year, int month)
{
    int leapCount = 0;
    if (month == 0)
    {
        month = mCurrentDate[1];
    }
    if (month==1 || month==2)
    {
        for (int i = 2022; i < year; ++i)
        {
            if (CheckLeapYear(i))
            {
                leapCount++;
            }
        }
    }
    return leapCount;
}


/**
 * Draw the text for the days of the week
 * This is used for the month and the week view
 * @param graphics the graphics to draw on
 * @param font the font to use
 * @param dayStr the first three letters of the day
 * @param option the option to use week, so the numbers appear, default does not show numbers
 */
void Tracker::DrawDaysText(std::shared_ptr<wxGraphicsContext> graphics, wxFont font, std::wstring dayStr,
                            std::wstring option)
{
    graphics->SetFont(font, mTextColor);

    // draw the text for each of the days
    if (option == L"Default")
    {
        for (int i = 0; i<7; ++i)
        {
            graphics->DrawText(mDayWeekMap[i+1], 160+(155*i), 100);
        }
        return;
    }
    else if (option == L"Week")
    {

        bool leap = CheckLeapYear(mCurrentYear);

        int dist = 0;
        vector<int> dateOne = {0,0,0};
        vector<int> dateTwo = {0,0,0};

        for (int i = 0; i<7; ++i)
        {
            // for the current day, just draw the number as the current day
            if (dayStr == mDayWeekMap[i+1])
            {
                mWeekDateMap[i] = mCurrentDate;
                graphics->DrawText(mDayWeekMap[i+1] + L" " + to_wstring(mCurrentDate[2]), 160+(155*i), 100);
            }
            else
            {
                // the difference is the value associated with the day1 - value ass. with day2
                int diff = mWeekDayMap[dayStr] - mWeekDayMap[mDayWeekMap[i+1]];

                if (diff < 0) // we are drawing to the right of the current date
                {
                    // we are in range of the current months allotted days
                    if ((mCurrentDay - diff) <= mMonthDayMap[mCurrentMonth] ||
                    ((mCurrentDay - diff) <= mMonthDayMap[mCurrentMonth] + 1 && leap && mCurrentMonth == 2))
                    {
                        mWeekDateMap[i][0] = mCurrentYear;
                        mWeekDateMap[i][1] = mCurrentMonth;
                        mWeekDateMap[i][2] = mCurrentDay - diff;

                        graphics->DrawText(mDayWeekMap[i+1] + L" " + to_wstring(mCurrentDay - diff),
                                160+(155*i), 100);
                    }
                    else // we are in a new month
                    {

                        // make the text light grey before drawing since new month
                        graphics->SetFont(font, wxColour(211, 211, 211));

                        // find the distance to the end of the current month
                        dateOne = {mCurrentYear,mCurrentMonth,mCurrentDay - diff};
                        dateTwo = {mCurrentYear,mCurrentMonth,mMonthDayMap[mCurrentMonth]};

                        dist = DistanceBetweenDates(dateOne,dateTwo);

                        if (leap && mCurrentMonth == 2)
                        {
                            dist--;
                        }

                        graphics->DrawText(mDayWeekMap[i+1] + L" " + to_wstring(dist), 160+(155*i), 100);

                        mWeekDateMap[i][0] = mCurrentYear;
                        mWeekDateMap[i][1] = mCurrentMonth + 1;
                        if (mCurrentMonth == 12)
                        {
                            mWeekDateMap[i][0] += 1;
                            mWeekDateMap[i][1] = 1;
                        }
                        mWeekDateMap[i][2] = dist;


                        // set font back to normal coloring
                        graphics->SetFont(font, mTextColor);
                    }
                }
                else // drawing to the left of the current date
                {

                    // we are in range of the current months allotted days
                    if ((mCurrentDay - diff) <= mMonthDayMap[mCurrentMonth]  && (mCurrentDay - diff) > 0||
                    (mCurrentDay - diff <= mMonthDayMap[mCurrentMonth] + 1 && (mCurrentDay - diff) > 0
                        && leap && mCurrentMonth == 2))
                    {
                        graphics->DrawText(mDayWeekMap[i+1] + L" " + to_wstring(mCurrentDay - diff),
                                160+(155*i), 100);

                        mWeekDateMap[i][0] = mCurrentYear;
                        mWeekDateMap[i][1] = mCurrentMonth;
                        mWeekDateMap[i][2] = mCurrentDay - diff;
                    }
                    else // we are in the prev month
                    {
                        // make the text light grey before drawing since prev month
                        graphics->SetFont(font, wxColour(211, 211, 211));

                        // find the distance from first day of prev month to current day
                        if (mCurrentMonth != 1)
                        {
                            dateOne = {mCurrentYear,mCurrentMonth - 1,1};
                            dateTwo = {mCurrentYear,mCurrentMonth,mCurrentDay};

                        }
                        else
                        {
                            dateOne = {mCurrentYear - 1,12,1};
                            dateTwo = {mCurrentYear,mCurrentMonth,mCurrentDay};

                        }

                        dist = DistanceBetweenDates(dateOne,dateTwo);


                        if (leap && mCurrentMonth > 2)
                        {
                            dist++;
                        }

                        dist -= diff;
                        dist++;

                        if (leap && mCurrentMonth == 3)
                        {
                            dist--;
                        }
                        else if (leap && mCurrentMonth == 2)
                        {
                            dist -= 0;
                        }
                        else if (leap && mCurrentMonth != 1 && mCurrentMonth != 3)
                        {
                            dist --;
                        }

                        graphics->DrawText(mDayWeekMap[i+1] + L" " + to_wstring(dist), 160+(155*i), 100);

                        mWeekDateMap[i][0] = mCurrentYear;
                        mWeekDateMap[i][1] = mCurrentMonth - 1;
                        if (mCurrentMonth == 1)
                        {
                            mWeekDateMap[i][0] -= 1;
                            mWeekDateMap[i][1] = 12;
                        }
                        mWeekDateMap[i][2] = dist;

                        // set font back to normal coloring
                        graphics->SetFont(font, mTextColor);

                    }
                }
            }
        }
    }
}


/**
 * Find the starting day of the month given the month and the year
 * @param date the date
 * @param option allows use for finding the week, or the month, defaults to month
 * @return a wstring representing the starting day
*/
std::wstring Tracker::FindStartingDay(std::vector<int> date, const std::wstring& option)
{
    // jan 2022 starts on sat
    // knowing this we can find the distance between this day and the first of the given month
    // this will give us the starting day of the month desired

    int year = date[0];
    int month = date[1];
    int day = date[2];
    std::vector<int> dateOne = {2022,1,1};
    std::vector<int> dateTwo = {0,0,0};

    int numDays = 0;
    if (option == L"Month")
    {
        dateTwo = {year,month,1};
    }
    else if (option == L"Week" || option == L"Day")
    {
        dateTwo = {year,month,day};
    }

    numDays = DistanceBetweenDates(dateOne, dateTwo);

    numDays = numDays % 7;

    // adjust for saturday so map lines up
    if (numDays == 0)
    {
        numDays = 7;
    }

    return mDayWeekMap[numDays];
}


/**
 * Given two dates, find the the distance between the dates in days
 * @param dateOne the first date
 * @param dateTwo the second date
 * @return the number of days between the dates
 */
int Tracker::DistanceBetweenDates(std::vector<int> dateOne, std::vector<int> dateTwo)
{
    int yearOne = dateOne[0];
    int monthOne = dateOne[1];
    int dayOne = dateOne[2];

    int yearTwo = dateTwo[0];
    int monthTwo = dateTwo[1];
    int dayTwo = dateTwo[2];

    auto daysOne = year{yearOne}/monthOne/dayOne;
    auto daysTwo = year{yearTwo}/monthTwo/dayTwo;
    return abs(sys_days{daysOne} - sys_days{daysTwo}).count();
}

/**
 * Check if a year is a leap year
 * @param year the year to check
 * @return true if year is a leap year, else false
 */
bool Tracker::CheckLeapYear(int year)
{
    if (year % 4 == 0)
    {
        // end of century
        if (year % 100 == 0)
        {
            return year % 400 == 0;
        }
    }
    return year % 4 == 0;
}


/**
 * Load the tracker from a .tracker XML file.
 *
 * Opens the XML file and reads the nodes, creating items as appropriate.
 *
 * @param filename The filename of the file to load the tracker from.
 */
void Tracker::Load(const wxString &filename)
{
    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load Tracker file");
        return;
    }

    mItemMap.clear();

    // Get the XML document root node
    auto root = xmlDoc.GetRoot();

    //
    // Traverse the children of the root
    // node of the XML document in memory
    //
    auto child = root->GetChildren();
    for( ; child; child=child->GetNext())
    {
        auto name = child->GetName();
        if(name == L"event")
        {
            XmlEvent(child);
        }
    }
}


/**
 * Handle a node of type item.
 * @param node XML node
 */
void Tracker::XmlEvent(wxXmlNode *node)
{
    // A pointer for the item we are loading
    shared_ptr<Item> event;

    int yearInt = 0;
    int monthInt = 0;
    int dayInt = 0;

    auto year = node->GetAttribute(L"year").ToInt(&yearInt);
    auto month = node->GetAttribute(L"month").ToInt(&monthInt);
    auto day = node->GetAttribute(L"day").ToInt(&dayInt);
    auto start = node->GetAttribute(L"start").ToStdWstring();
    auto end = node->GetAttribute(L"end").ToStdWstring();
    auto type = node->GetAttribute(L"type").ToStdWstring();
    auto description = node->GetAttribute(L"description").ToStdWstring();
    auto image= node->GetAttribute(L"image").ToStdWstring();

    event = make_shared<StandardEvent>(this,yearInt,monthInt,dayInt,type,
            description,start,end);

    event->SetImageName(image);

    if (event != nullptr)
    {
        auto date = std::vector<int>{yearInt,monthInt,dayInt};
        mItemMap[date].push_back(event);
    }

}


/**
 * Save the tracker as a .tracker XML file.
 *
 * Open an XML file and stream the aquarium data to it.
 *
 * @param filename The filename of the file to save the aquarium to
 */
void Tracker::Save(const wxString &filename)
{
    wxXmlDocument xmlDoc;

    auto root = new wxXmlNode(wxXML_ELEMENT_NODE, L"tracker");
    xmlDoc.SetRoot(root);

    // Iterate over all items and save them
    for (auto const& [key, val] : mItemMap)
    {
        for (const auto& item : val)
        {
            item->XmlSave(root);
        }
    }


    if(!xmlDoc.Save(filename, wxXML_NO_INDENTATION))
    {
        wxMessageBox(L"Write to XML failed");
        return;
    }
}
