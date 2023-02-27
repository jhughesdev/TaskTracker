/**
 * @file Tracker.h
 * @author Jacob Hughes
 *
 *
 */

#ifndef TESTTRACKER22_TRACKER_H
#define TESTTRACKER22_TRACKER_H

class Item;
class Year;
class Event;
#include "Year.h"
class StandardEvent;
#include <map>
class Week;
#include <wx/xml/xml.h>



/**
 * Class that describes the tracker
 * Holds a collection of years
 */
class Tracker {
private:

    /// Custom RGB values to use for the days text
    int mRedDaysText = 1;

    /// Custom RGB values to use for the days text
    int mGreenDaysText = 150;

    /// Custom RGB values to use for the days text
    int mBlueDaysText = 1;

    /// Custom RGB values to use for the days box
    int mRedDaysBox = 1;

    /// Custom RGB values to use for the days box
    int mGreenDaysBox = 1;

    /// Custom RGB values to use for the days box
    int mBlueDaysBox = 1;

    /// The most recent event's year
    int mRecentEventYear = 2023;

    /// The most recent event's month
    int mRecentEventMonth = 1;

    /// The most recent event's day
    int mRecentEventDay = 1;

    /// All of the years in the Tracker
    std::vector<std::shared_ptr<Year>> mYears;

    std::map<std::vector<int>,std::vector<std::shared_ptr<Item>>> mItemMap;

    /// The current state
    int mState = 2;

    /// The current year
    int mCurrentYear = 2023;

    /// The default year
    int mDefaultYear = 2022;

    /// The current month
    int mCurrentMonth = 1;

    /// The current day
    int mCurrentDay = 1;

    /// The actual day
    int mActualDay = 1;

    /// The actual month
    int mActualMonth = 1;

    /// The actual year
    int mActualYear = 1;

    /// Week date map
    std::map<int,std::vector<int>> mWeekDateMap {{0,{0,0,0}}, {1,{0,0,0}}, {2,{0,0,0}},
            {3,{0,0,0}}, {4,{0,0,0}}, {5,{0,0,0}},
            {6,{0,0,0}}};

    /// Month Date Map
    std::map<int,std::vector<int>> mMonthDateMap;

    /// Map used for drawing the month
    std::map<int,int> mDrawMonthMap;

    /// Vector representing the current date
    std::vector<int> mCurrentDate{ mCurrentYear, mCurrentMonth, mCurrentDay};

    /// The text color
    wxColour mTextColor = wxColour(mRedDaysText,mGreenDaysText,mBlueDaysText);

    /// The box color
    wxColour mBoxColor = wxColour(mRedDaysBox,mGreenDaysBox,mBlueDaysBox);

    /// Map with key of month number, value of string form of the month
    std::map<int,std::wstring> mMonthMap { {1,L"January"}, {2,L"February"}, {3,L"March"},
            {4,L"April"}, {5,L"May"}, {6,L"June"},{7,L"July"}, {8,L"August"},
            {9,L"September"},{10,L"October"}, {11,L"November"}, {12,L"December"}};

    /// Map with key of month number, value of int form of the month number of days
    std::map<int,int> mMonthDayMap { {1,31}, {2,28}, {3,31},
            {4,30}, {5,31}, {6,30},
            {7,31},{8,31}, {9,30},
            {10,31}, {11,30}, {12,31}};

    /// Map with key of ints, value of days of the week
    std::map<int,std::wstring> mDayWeekMap {{1,L"Sun"},{2,L"Mon"},{3,L"Tue"},
                                {4,L"Wed"},{5,L"Thu"},{6,L"Fri"},
                                {7,L"Sat"}};

    /// Map with key of string day of the week, value of int
    std::map<std::wstring,int> mWeekDayMap {{L"Sun",1},{L"Mon",2},{L"Tue",3},
            {L"Wed",4},{L"Thu",5},{L"Fri",6},
            {L"Sat",7}};

public:

    /**
     * Get the actual month
     * @return the actual month
     */
    int GetActualMonth() {return mActualMonth;}

    /**
     * Get the actual day
     * @return the actual day
     */
    int GetActualDay() {return mActualDay;}

    /**
     * Get the actual year
     * @return the actual year
     */
    int GetActualYear() {return mActualYear;}

    /**
     * Set the month date map
     * @param map the map to set
     */
    void SetMonthDateMap(std::map<int,std::vector<int>> map) {mMonthDateMap = map;}

    /**
     * Set the draw month map
     * @param map the map to set
     */
    void SetDrawMonthMap(std::map<int,int> map) {mDrawMonthMap = map;}

    void Load(const wxString& filename);

    void XmlEvent(wxXmlNode* node);

    /**
     * Set the year of the most recent event
     * @param year the year to set
     */
    void SetRecentEventYear(int year) {mRecentEventYear = year;}

    /**
     * Set the month of the most recent event
     * @param month the year to set
     */
    void SetRecentEventMonth(int month) {mRecentEventMonth = month;}

    /**
     * Set the day of the most recent event
     * @param day the year to set
     */
    void SetRecentEventDay(int day) {mRecentEventDay = day;}

    /**
     * Get the year of the most recent event
     * @return the most recent event year
     */
    int GetRecentEventYear() {return mRecentEventYear;}

    /**
     * Get the month of the most recent event
     * @return the most recent event month
     */
    int GetRecentEventMonth() {return mRecentEventMonth;}

    /**
     * Get the day of the most recent event
     * @return the most recent event day
     */
    int GetRecentEventDay() {return mRecentEventDay;}

    /**
     * Get the text color
     * @return the text color
     */
    wxColour GetTextColor() {return mTextColor;}

    /**
     * Set the year of the current date
     * @param year the year to set
     */
    void SetDateYear(int year) {mCurrentDate[0] = year;}

    /**
     * Set the month of the current date
     * @param month the month to set
     */
    void SetDateMonth(int month) {mCurrentDate[1] = month;}

    /**
     * Set the day of the current date
     * @param day the day to set
     */
    void SetDateDay(int day) {mCurrentDate[2] = day;}

    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics);

    void DrawDaysText(std::shared_ptr<wxGraphicsContext> graphics, wxFont font,
                            std::wstring dayStr = L"None",std::wstring option = L"Default");

    bool CheckLeapYear(int year);

    /**
     * Set the current year of the tracker
     * @param year the year to set
     */
     void SetYear(int year)
     {
         mCurrentYear = year;
         mCurrentDate[0] = year;
     }

    /**
    * Set the current month of the tracker
    * @param month the month to set
    */
    void SetMonth(int month)
    {
        mCurrentMonth = month;
        mCurrentDate[1] = month;
    }

    /**
     * Set the current day of the tracker
     * @param day the day to set
     */
    void SetDay(int day)
    {
        mCurrentDay = day;
        mCurrentDate[2] = day;
    }

    /**
     * Get the current year of the tracker
     * @return the current year
     */
    int GetYear() {return mCurrentYear;}

    /**
    * Get the current month of the tracker
    * @return the current month in the form of an integer
    */
    int GetMonth() {return mCurrentMonth;}

    /**
     * Get the current day of the tracker
     * @return the current day
     */
    int GetDay() {return mCurrentDay;}

    /**
     * Set the r of the rgb value for the days text color
     * @param value the r value to set
     */
    void SetRedDaysText(int value)
    {
        mRedDaysText = value;
        mTextColor = wxColour(mRedDaysText,mGreenDaysText,mBlueDaysText);
    }

    /**
     * Set the g of the rgb value for the days text color
     * @param value the g value to set
     */
    void SetGreenDaysText(int value)
    {
        mGreenDaysText = value;
        mTextColor = wxColour(mRedDaysText,mGreenDaysText,mBlueDaysText);
    }

    /**
     * Set the b of the rgb value for the days text color
     * @param value the b value to set
     */
    void SetBlueDaysText(int value)
    {
        mBlueDaysText = value;
        mTextColor = wxColour(mRedDaysText,mGreenDaysText,mBlueDaysText);
    }

    /**
     * Get the r of the rgb value for the days text color
     * @return the r value
     */
    int GetRedDaysText() {return mRedDaysText;}

    /**
     * Get the g of the rgb value for the days text color
     * @return the g value
     */
    int GetGreenDaysText() {return mGreenDaysText;}

    /**
     * Get the b of the rgb value for the days text color
     * @return the b value
     */
    int GetBlueDaysText() {return mBlueDaysText;}

    /**
     * Set the r of the rgb value for the day box color
     * @param value the r value to set
     */
    void SetRedDaysBox(int value)
    {
        mRedDaysBox = value;
        mBoxColor = wxColour(mRedDaysBox,mGreenDaysBox,mBlueDaysBox);
    }

    /**
     * Set the g of the rgb value for the day box color
     * @param value the g value to set
     */
    void SetGreenDaysBox(int value)
    {
        mGreenDaysBox = value;
        mBoxColor = wxColour(mRedDaysBox,mGreenDaysBox,mBlueDaysBox);
    }

    /**
     * Set the b value of the rgb value for the day box color
     * @param value the b value to set
     */
    void SetBlueDaysBox(int value)
    {
        mBlueDaysBox = value;
        mBoxColor = wxColour(mRedDaysBox,mGreenDaysBox,mBlueDaysBox);
    }

    /**
     * Get the r value of the rgb value for the day box color
     * @return the r value of the day box color
     */
    int GetRedDaysBox() {return mRedDaysBox;}

    /**
     * Get the g value of the rgb value for the day box color
     * @return the g value of the day box color
     */
    int GetGreenDaysBox() {return mGreenDaysBox;}

    /**
     * Get the b value of the rgb value for the day box color
     * @return the b value of the day box color
     */
    int GetBlueDaysBox() {return mBlueDaysBox;}

    /**
    * Add an event to the tracker
    */
    void AddEvent(std::shared_ptr<StandardEvent> event)
    {
        auto y = event->GetEventYear();
        auto m = event->GetEventMonth();
        auto d = event->GetEventDay();
        std::vector<int> date = {y,m,d};
        mItemMap[date].push_back(event);
    }

    /**
     * Remove the most recent event
     */
    void RemoveRecent()
    {
        // fix so that the most recent event added is actually removed, this takes the current year and removes it
        //mYears[mCurrentYear - mDefaultYear]->RemoveRecent(mCurrentMonth,mCurrentDay);
    }

    /**
     * Remove all of the events for the given year
     */
    void RemoveAll()
    {
        mItemMap.clear();
    }

    void Initialize();

    /**
     * Set the state
     * @param state the state to set
     */
    void SetState(int state) {mState = state;}

    /**
     * Get the state
     * @return the state
     */
    int GetState() {return mState;}

    std::wstring FindStartingDay(std::vector<int> date, const std::wstring& option = L"Month");

    int DistanceBetweenDates(std::vector<int> dateOne, std::vector<int> dateTwo);

    int GetLeapYears(int year, int month = 0);

    void Save(const wxString &filename);

};

#endif //TESTTRACKER22_TRACKER_H
