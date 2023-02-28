/**
 * @file Day.cpp
 * @author Jacob Hughes
 */

#include "pch.h"
#include "Day.h"
#include "StandardEvent.h"
#include "Month.h"

using namespace std;


/**
 * Constructor
 * @param tracker The tracker this day is a member of
 * @param month the month the day is in
 */
Day::Day(Tracker *tracker,Month* month) : mTracker(tracker), mMonth(month)
{
}

/**
 * Draw the day
 * @param graphics the graphics to draw on
 * @param option allows events to be drawn according to view selected
 */
void Day::Draw(std::shared_ptr<wxGraphicsContext> graphics, std::wstring option)
{


}