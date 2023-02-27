/**
 * @file YearTest.cpp
 * @author Jacob Hughes
 */


#include <pch.h>
#include "gtest/gtest.h"
#include <Tracker.h>
#include <map>

using namespace std;

TEST (TrackerTest,Colors)
{
    Tracker tracker;

    // check default values for text color
    ASSERT_EQ(tracker.GetRedDaysText(),1);
    ASSERT_EQ(tracker.GetGreenDaysText(),150);
    ASSERT_EQ(tracker.GetBlueDaysText(),1);

    // change the colors different from default values
    tracker.SetRedDaysText(200);
    tracker.SetGreenDaysText(70);
    tracker.SetBlueDaysText(99);

    // check to ensure setters work
    ASSERT_EQ(tracker.GetRedDaysText(),200);
    ASSERT_EQ(tracker.GetGreenDaysText(),70);
    ASSERT_EQ(tracker.GetBlueDaysText(),99);

    // check default values for box colors
    ASSERT_EQ(tracker.GetRedDaysBox(),1);
    ASSERT_EQ(tracker.GetGreenDaysBox(),1);
    ASSERT_EQ(tracker.GetBlueDaysBox(),1);

    // change the colors different from default values
    tracker.SetRedDaysBox(250);
    tracker.SetGreenDaysBox(90);
    tracker.SetBlueDaysBox(100);


    // check to ensure setters work
    ASSERT_EQ(tracker.GetRedDaysBox(),250);
    ASSERT_EQ(tracker.GetGreenDaysBox(),90);
    ASSERT_EQ(tracker.GetBlueDaysBox(),100);

}

TEST (TrackerTest,Dates)
{
    Tracker tracker;

    // Check to ensure default state is 4
    ASSERT_EQ(tracker.GetState(),4);

    // Change the state
    tracker.SetState(3);

    // make sure the state change is reflected
    ASSERT_EQ(tracker.GetState(),3);

    // Check all default states of dates
    ASSERT_EQ(tracker.GetYear(),2023);
    ASSERT_EQ(tracker.GetMonth(),1);
    ASSERT_EQ(tracker.GetDay(),1);

    // change the date
    tracker.SetYear(2099);
    tracker.SetMonth(7);
    tracker.SetDay(24);

    // ensure setters work
    ASSERT_EQ(tracker.GetYear(),2099);
    ASSERT_EQ(tracker.GetMonth(),7);
    ASSERT_EQ(tracker.GetDay(),24);
}

TEST (TrackerTest,Leaps)
{
    Tracker tracker;

    // check if a year is a leap year

    for (int i = 2000; i <= 2100; ++i)
    {
        bool leap = tracker.CheckLeapYear(i);
        if (i == 2000 || i == 2004 || i == 2008 || i == 2012 ||
                i == 2016 || i == 2020 || i == 2024 || i == 2028 ||
                i == 2032 || i == 2036 || i == 2040 || i == 2044 ||
                i == 2048 || i == 2052 || i == 2056 || i == 2060 ||
                i == 2064 || i == 2068 || i == 2072 || i == 2076 ||
                i == 2080 || i == 2084 || i == 2088 || i == 2092 ||
                i == 2096)
        {
            ASSERT_EQ(leap,true);
        }
        else
        {
            ASSERT_EQ(leap,false);
        }
    }

    // check amount of leap years within 2022- entered year

    int leaps = tracker.GetLeapYears(2027,1);

    ASSERT_EQ(leaps,1);

    // do not want any leaps for years if month is not jan or feb
    leaps = tracker.GetLeapYears(2025,3);

    ASSERT_EQ(leaps,0);

    // more various tests
    leaps = tracker.GetLeapYears(2028,2);
    int leaps2 = tracker.GetLeapYears(2090,1);
    int leaps3 = tracker.GetLeapYears(2064,2);
    int leaps4 = tracker.GetLeapYears(2053,2);
    int leaps5 = tracker.GetLeapYears(2070,2);
    int leaps6 = tracker.GetLeapYears(2099,5);
    int leaps7 = tracker.GetLeapYears(2100,2);
    int leaps8 = tracker.GetLeapYears(2050,12);
    int leaps9 = tracker.GetLeapYears(2030,2);
    int leaps10 = tracker.GetLeapYears(2040,1);
    int leaps11 = tracker.GetLeapYears(2046,2);

    ASSERT_EQ(leaps,1);
    ASSERT_EQ(leaps2,17);
    ASSERT_EQ(leaps3,10);
    ASSERT_EQ(leaps4,8);
    ASSERT_EQ(leaps5,12);
    ASSERT_EQ(leaps6,0);
    ASSERT_EQ(leaps7,19);
    ASSERT_EQ(leaps8,0);
    ASSERT_EQ(leaps9,2);
    ASSERT_EQ(leaps10,4);
    ASSERT_EQ(leaps11,6);
}

TEST (TrackerTest,DistanceBetweenDates)
{
    Tracker tracker;

    std::vector<int> date1 = {2022,1,1};
    std::vector<int> date2 = {2022,1,1};
    int dist = tracker.DistanceBetweenDates(date1,date2);

    date1 = {2023,5,7};
    date2 = {2023,5,7};
    int dist2 = tracker.DistanceBetweenDates(date1,date2);

    date1 = {2096,2,27};
    date2 = {2096,2,27};
    int dist3 = tracker.DistanceBetweenDates(date1,date2);

    date1 = {2040,1,18};
    date2 = {2040,1,18};
    int dist4 = tracker.DistanceBetweenDates(date1,date2);

    date1 = {2088,12,13};
    date2 = {2088,12,13};
    int dist5 = tracker.DistanceBetweenDates(date1,date2);


    // all dates that are the same are 0 days apart from each other
    ASSERT_EQ(dist,0);
    ASSERT_EQ(dist2,0);
    ASSERT_EQ(dist3,0);
    ASSERT_EQ(dist4,0);
    ASSERT_EQ(dist5,0);

    // some smaller tests
    date1 = {2023,5,7};
    date2 = {2023,5,14};
    dist = tracker.DistanceBetweenDates(date1,date2);

    date1 = {2023,9,7};
    date2 = {2023,9,8};
    dist2 = tracker.DistanceBetweenDates(date1,date2);

    date1 = {2095,2,27};
    date2 = {2096,2,27};
    dist3 = tracker.DistanceBetweenDates(date1,date2);

    date1 = {2040,1,18};
    date2 = {2040,9,18};
    dist4 = tracker.DistanceBetweenDates(date1,date2);

    date1 = {2088,11,13};
    date2 = {2088,12,13};
    dist5 = tracker.DistanceBetweenDates(date1,date2);

    ASSERT_EQ(dist,7);
    ASSERT_EQ(dist2,1);
    ASSERT_EQ(dist3,365);
    ASSERT_EQ(dist4,244);
    ASSERT_EQ(dist5,30);

    // some larger tests
    date1 = {2022,11,13};
    date2 = {2093,5,14};
    dist = tracker.DistanceBetweenDates(date1,date2);

    date1 = {2038,9,7};
    date2 = {2088,1,12};
    dist2 = tracker.DistanceBetweenDates(date1,date2);

    date1 = {2022,3,1};
    date2 = {2099,6,15};
    dist3 = tracker.DistanceBetweenDates(date1,date2);

    date1 = {2039,7,13};
    date2 = {2060,1,29};
    dist4 = tracker.DistanceBetweenDates(date1,date2);

    date1 = {2043,5,20};
    date2 = {2073,8,5};
    dist5 = tracker.DistanceBetweenDates(date1,date2);

    ASSERT_EQ(dist,25750);
    ASSERT_EQ(dist2,18024);
    ASSERT_EQ(dist3,28230);
    ASSERT_EQ(dist4,7505);
    ASSERT_EQ(dist5,11035);
}

TEST (TrackerTest,FindStartingDay)
{
    Tracker tracker;

    // test random days verified by a key to ensure numbers match

    std::map<int,std::wstring> key {{1,L"Fri"},{2,L"Mon"},{3,L"Thu"},
            {4,L"Tue"},{5,L"Fri"},{6,L"Tue"},{7,L"Sun"},
            {8,L"Mon"},{9,L"Sat"},{10,L"Wed"},
            {11,L"Wed"},{12,L"Mon"},{13,L"Sat"},
            {14,L"Mon"},{15,L"Thu"},{16,L"Mon"},
            {17,L"Wed"},{18,L"Tue"},{19,L"Fri"},{20,L"Sat"}};


    std::map<int,vector<int>> dates {{1,{2023,3,3}},{2,{2023,6,26}},{3,{2039,2,24}},
            {4,{2035,7,31}},{5,{2028,8,4}},{6,{2032,9,21}},{7,{2042,2,2}},
            {8,{2047,4,15}},{9,{2054,3,7}},{10,{2047,11,13}},
            {11,{2052,12,4}},{12,{2056,1,3}},{13,{2069,5,25}},
            {14,{2072,2,29}},{15,{2072,4,21}},{16,{2093,5,11}},
            {17,{2088,7,14}},{18,{2023,6,20}},{19,{2025,2,21}},{20,{2029,8,18}}};;


    for (int i = 1; i <= static_cast<int>(key.size()); ++i)
    {
        ASSERT_EQ(tracker.FindStartingDay(dates[i],L"Day"),key[i]);
    }
}