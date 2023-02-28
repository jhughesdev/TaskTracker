/**
 * @file Month.h
 * @author Jacob Hughes
 *
 *
 */

#ifndef TESTTRACKER22_MONTH_H
#define TESTTRACKER22_MONTH_H

class Tracker;
#include "Day.h"
#include "StandardEvent.h"
#include <map>
class Year;


/**
 * Class that describes a month
 * A month holds a collection of days
 */
class Month {
private:

    /// The tracker the month is a part of
    Tracker* mTracker;

    /// The year the month is in
    Year* mYear = nullptr;

    /// Collection of Days
    std::vector<std::shared_ptr<Day>> mDays;

    /// The name of the month
    std::wstring mName;

    /// Map with key of day of the week, value is a counter used to draw months accordingly
    std::map<std::wstring,int> mStartDayMap { {L"Sun",1},{L"Mon",0}, {L"Tue",-1},
            {L"Wed",-2},{L"Thu",-3}, {L"Fri",-4}, {L"Sat",-5}};

    /// Map with key of month number, value of int form of the month number of days
    std::map<int,int> mMonthDayMap { {1,31}, {2,28}, {3,31},
            {4,30}, {5,31}, {6,30},
            {7,31},{8,31}, {9,30},
            {10,31}, {11,30}, {12,31}};

    /// Month date map with key as int representing month, value as vector representing the date
    std::map<int,std::vector<int>> mMonthDateMap;

    /// Map used to help with drawing the months
    std::map<int,int> mDrawMonthMap;

public:

    Month(Tracker* tracker, int days, std::wstring name,Year* year);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, std::vector<int> date,
            double scaleX,double scaleY,int yearMonth=0,std::wstring option = L"None");


};

#endif //TESTTRACKER22_MONTH_H
