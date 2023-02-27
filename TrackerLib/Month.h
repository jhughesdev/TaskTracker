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

//    std::map<int,std::vector<int>> mMonthDateMap {{0,{0,0,0,0}}, {1,{0,0,0,0}}, {2,{0,0,0,0}},
//            {3,{0,0,0,0}}, {4,{0,0,0,0}}, {5,{0,0,0,0}},
//            {6,{0,0,0,0}}, {7,{0,0,0,0}}, {8,{0,0,0,0}},
//            {9,{0,0,0,0}},{10,{0,0,0,0}}, {11,{0,0,0,0}},
//            {12,{0,0,0,0}},{13,{0,0,0,0}}, {14,{0,0,0,0}},
//            {15,{0,0,0,0}},{16,{0,0,0,0}}, {17,{0,0,0,0}},
//            {18,{0,0,0,0}},{19,{0,0,0,0}}, {20,{0,0,0,0}},
//            {21,{0,0,0,0}},{22,{0,0,0,0}}, {23,{0,0,0,0}},
//            {24,{0,0,0,0}},{25,{0,0,0,0}}, {26,{0,0,0,0}},
//            {27,{0,0,0,0}},{28,{0,0,0,0}}, {29,{0,0,0,0}},
//            {30,{0,0,0,0}},{31,{0,0,0,0}}, {32,{0,0,0,0}},
//            {33,{0,0,0,0}},{34,{0,0,0,0}}, {35,{0,0,0,0}},
//            {36,{0,0,0,0}},{37,{0,0,0,0}}, {38,{0,0,0,0}},
//            {39,{0,0,0,0}},{40,{0,0,0,0}}, {41,{0,0,0,0}},
//    };

    std::map<int,std::vector<int>> mMonthDateMap;

    std::map<int,int> mDrawMonthMap;

public:

    Month(Tracker* tracker, int days, std::wstring name,Year* year);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, std::vector<int> date,
            double scaleX,double scaleY,int yearMonth=0,std::wstring option = L"None");


};

#endif //TESTTRACKER22_MONTH_H
