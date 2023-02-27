/**
 * @file StandardEvent.cpp
 * @author Jacob Hughes
 */

#include "pch.h"
#include "StandardEvent.h"
#include "Tracker.h"

using namespace std;

using namespace std::chrono;


const wxFont font(wxSize(0, 20),
        wxFONTFAMILY_SWISS,
        wxFONTSTYLE_NORMAL,
        wxFONTWEIGHT_NORMAL);


/**
 * Constructor
 * @param tracker The tracker this item is a member of
 * @param year the year of the event
 * @param month the month of the event
 * @param day the day of the event
 * @param type the type of the event
 */
StandardEvent::StandardEvent(Tracker* tracker,int year, int month, int day, std::wstring type,
        std::wstring description, std::wstring start, std::wstring end) : Item(tracker),
    mType(type), mDescription(description), mStartingTime(start), mEndingTime(end), mYear(year), mMonth(month), mDay(day)
{

}


/**
 * Draw the Standard Event
 * @param graphics the graphics to draw on
 * @param x the x location of where to draw
 * @param y the y location of where to draw
 */
void StandardEvent::Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y, std::wstring option)
{
    std::vector<int> date = {mYear,mMonth,mDay};
    wxBrush brush(mTypeColorMap[mType]);
    graphics->SetBrush(brush);


    if (option == L"Day")
    {
        graphics->DrawRectangle(x,y,1200,80);
        graphics->SetFont(font,wxColour(GetTracker()->GetRedDaysText(),GetTracker()->GetGreenDaysText(),
                GetTracker()->GetBlueDaysText()));
        graphics->DrawText(mType,x,y);
        return;
    }
    else if (option == L"Week")
    {
        std::map<std::wstring,int> xLocMap {{L"Sun",100},
                {L"Mon",255},{L"Tue",410},
                {L"Wed",565},{L"Thu",720},
                {L"Fri",875},{L"Sat",1030}};

        auto startDay = GetTracker()->FindStartingDay(date,L"Day");
        auto dateTwo = std::vector<int>{mYear,mMonth,1};
        auto startNum = GetTracker()->DistanceBetweenDates(date,dateTwo);
        int weekNum = (startNum / 7);
        if (GetTracker()->FindStartingDay(date,L"Month") == L"Sat" && mDay > 1)
        {
            weekNum += 1;
        }

        graphics->DrawRectangle(xLocMap[startDay],y,150,80);
        graphics->SetFont(font,wxColour(GetTracker()->GetRedDaysText(),GetTracker()->GetGreenDaysText(),
                GetTracker()->GetBlueDaysText()));
        graphics->DrawText(mType,xLocMap[startDay],y);
        return;
    }
    else if (option == L"Month")
    {
        std::map<std::wstring,int> xLocMap {{L"Sun",100},
                {L"Mon",255},{L"Tue",410},
                {L"Wed",565},{L"Thu",720},
                {L"Fri",875},{L"Sat",1030}};

        std::map<int,int> yLocMap {{0,150},
                {1,270},{2,390},
                {3,510},{4,630}};

        // find the day of the event
        // if monday draw most left
        // tuesday next, etc.
        auto startDay = GetTracker()->FindStartingDay(date,L"Day");
        auto dateTwo = std::vector<int>{mYear,mMonth,1};
        auto startNum = GetTracker()->DistanceBetweenDates(date,dateTwo);
        int weekNum = (startNum / 7);
        if (GetTracker()->FindStartingDay(date,L"Month") == L"Sat" && mDay > 1)
        {
            weekNum += 1;
        }

        graphics->DrawRectangle(xLocMap[startDay],yLocMap[weekNum],120,20);
        graphics->SetFont(font,wxColour(GetTracker()->GetRedDaysText(),GetTracker()->GetGreenDaysText(),
                GetTracker()->GetBlueDaysText()));
        graphics->DrawText(mType,xLocMap[startDay],yLocMap[weekNum]);

    }


    if (!mImageName.empty())
    {
        mImage = make_shared<wxImage>(mImageName);

        if(mBitmap.IsNull())
        {
            mBitmap = graphics->CreateBitmapFromImage(*mImage);
        }

        int wid = mImage->GetWidth();
        int hit = mImage->GetHeight();
        graphics->DrawBitmap(mBitmap, 220, 130, wid, hit);
    }
}


/**
 * Save this item to an XML node
 * @param node The parent node we are going to be a child of
 * @return wxXmlNode that we saved the item into
 */
wxXmlNode *StandardEvent::XmlSave(wxXmlNode *node)
{
    auto itemNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"event");
    node->AddChild(itemNode);

    itemNode->AddAttribute(L"year", wxString::FromDouble(mYear));
    itemNode->AddAttribute(L"month", wxString::FromDouble(mMonth));
    itemNode->AddAttribute(L"day", wxString::FromDouble(mDay));
    itemNode->AddAttribute(L"start", mStartingTime);
    itemNode->AddAttribute(L"end", mEndingTime);
    itemNode->AddAttribute(L"type", mType);
    itemNode->AddAttribute(L"description", mDescription);
    itemNode->AddAttribute(L"image",mImageName);

    return itemNode;
}