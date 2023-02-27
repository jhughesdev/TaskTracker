/**
 * @file Year.h
 * @author Jacob Hughes
 *
 *
 */

#ifndef TESTTRACKER22_YEAR_H
#define TESTTRACKER22_YEAR_H

class Tracker;
class Month;
class StandardEvent;
#include "Month.h"


/**
 * Class that describes a year
 * A year holds a collection of months
 */
class Year {
private:

    /// The tracker
    Tracker * mTracker;

    /// The year number
    int mYearNum = 0;

    /// Collection of Months
    std::vector<std::shared_ptr<Month>> mMonths;

    /// Map with key of month number, value of string form of the month
    std::map<int,std::wstring> mMonthMap { {1,L"January"}, {2,L"February"}, {3,L"March"},
            {4,L"April"}, {5,L"May"}, {6,L"June"},{7,L"July"}, {8,L"August"},
            {9,L"September"},{10,L"October"}, {11,L"November"}, {12,L"December"}};

    /// Map with key of month number, value of int form of the month number of days
    std::map<int,int> mMonthDayMap { {1,31}, {2,28}, {3,31},
            {4,30}, {5,31}, {6,30},
            {7,31},{8,31}, {9,30},
            {10,31}, {11,30}, {12,31}};

public:

    Year(Tracker* tracker, int year);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, std::vector<int> date,std::wstring option = L"Year");

};

#endif //TESTTRACKER22_YEAR_H
