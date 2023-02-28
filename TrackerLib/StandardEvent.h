/**
 * @file StandardEvent.h
 * @author Jacob Hughes
 *
 *
 */

#ifndef TESTTRACKER22_STANDARDEVENT_H
#define TESTTRACKER22_STANDARDEVENT_H

#include "Item.h"
#include <map>

/**
 * Class that describes standard events, which are stored in the Tracker
 */
class StandardEvent : public Item{
private:

    /// The image name
    std::wstring mImageName =L"";

    /// The image
    std::shared_ptr<wxImage> mImage;

    /// The bitmap
    wxGraphicsBitmap mBitmap;

    /// Bitmap image for the event
    std::unique_ptr<wxImage> mEventImage;

    /// Graphics bitmap to display
    wxGraphicsBitmap mEventBitmap;

    /// Starting time of the event
    std::wstring mStartingTime;

    /// Ending time of the event
    std::wstring mEndingTime;

    /// The year of the event
    int mYear = 2022;

    /// The month of the event
    int mMonth = 1;

    /// The day of the event
    int mDay = 1;

    /// The type of the event
    std::wstring mType;

    /// The description of the event
    std::wstring mDescription;

    /// standard colors for types
    wxColour mReminderColor = wxColour(255,255,0);

    /// workout color
    wxColour mWorkoutColor = wxColour(0,0,255);

    /// class color
    wxColour mClassColor = wxColour(0,255,0);

    /// homework color
    wxColour mHomeworkColor = wxColour(255,160,0);

    /// other color
    wxColour mOtherColor = wxColour(255,0,255);

    /// map the type of the event to it's according color
    std::map<std::wstring,wxColour> mTypeColorMap {{L"Reminder",mReminderColor},{L"Workout",mWorkoutColor},
            {L"Class",mClassColor},{L"Homework",mHomeworkColor},{L"Other",mOtherColor}};


public:

    /**
     * Set the image name
     * @param imageName the name to set
     */
    void SetImageName(std::wstring imageName) override {mImageName = imageName;}

    /**
     * Get the image name
     * @return the image name
     */
    std::wstring GetImageName() override {return mImageName;}

    StandardEvent(Tracker* tracker,int year, int month, int day, std::wstring type,
            std::wstring description, std::wstring start, std::wstring end);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y, std::wstring option) override;

    /**
     * Set the event day
     * @param day the day to set
     */
    void SetEventDay(int day) {mDay = day;}

    /**
     * Set the event month
     * @param month the month to set
     */
    void SetEventMonth(int month) {mMonth = month;}

    /**
     * Set the event year
     * @param year the year to set
     */
    void SetEventYear(int year) {mYear = year;}

    /**
     * Set the event description
     * @param description the description to set
     */
    void SetEventDescription(std::wstring description) {mDescription = description;}

    /**
     * Get the event day
     * @return the event day
     */
    virtual int GetEventDay() override {return mDay;}

    /**
     * Get the event month
     * @return the event month
     */
    virtual int GetEventMonth() override {return mMonth;}

    /**
     * Get the event year
     * @return the event year
     */
    virtual int GetEventYear() override {return mYear;}

    /**
     * Get the event color
     * @return the event color
     */
    virtual wxColour GetColor() override {return mTypeColorMap[mType];}

    /**
     * Set the type of the event
     * @param type the type to set
     */
    void SetType(std::wstring type) {mType = type;}

    /**
     * Set the start of the event
     * @param start the start time to set
     */
    void SetStart(std::wstring start) {mStartingTime = start;}

    /**
     * Set the end time of the event
     * @param end the end time to set
     */
    void SetEnd(std::wstring end) {mEndingTime = end;}


    /**
     * Get the event type
     * @return the event type
     */
    virtual std::wstring GetEventType() override {return mType;}

    /**
     * Get the event description
     * @return the event description
     */
    virtual std::wstring GetEventDescription() override {return mDescription;}

    virtual wxXmlNode *XmlSave(wxXmlNode *node) override;


};

#endif //TESTTRACKER22_STANDARDEVENT_H
