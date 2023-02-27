/**
 * @file Day.h
 * @author Jacob Hughes
 *
 *
 */

#ifndef TESTTRACKER22_DAY_H
#define TESTTRACKER22_DAY_H

class Tracker;
class Item;
#include "StandardEvent.h"
class Month;



/**
 * Class that describes a day
 * The day holds all the given Events in a day
 */
class Day {
private:

    /// The tracker the day is a part of
    Tracker *mTracker;

    /// The year the day is in
    Month* mMonth;

public:

    Day(Tracker* tracker, Month* month =nullptr);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics,std::wstring option = L"None");

};

#endif //TESTTRACKER22_DAY_H
