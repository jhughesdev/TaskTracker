/**
 * @file Picture.h
 * @author Jacob Hughes
 *
 *
 */

#ifndef TESTTRACKER22_PICTURE_H
#define TESTTRACKER22_PICTURE_H

#include <wx/gdicmn.h>

class PictureObserver;

/**
 * Class that describes the animation picture
 *
 */
class Picture {
private:
    /// The picture size
    wxSize mSize = wxSize(1500, 800);

    /// The observers of this picture
    std::vector<PictureObserver *> mObservers;

public:
    Picture();

    /// Copy Constructor (Disabled)
    Picture(const Picture &) = delete;

    /// Assignment Operator (Disabled)
    void operator=(const Picture &) = delete;

    /**
     * Destructor
    */
    virtual ~Picture() = default;

    /**
     * Get the picture size
     * @return Picture size in pixels
     */
    wxSize GetSize() {return mSize;}

    /**
     * Set the picture size
     * @param size Picture size in pixels
     */
    void SetSize(wxSize size) {mSize = size;}

    void AddObserver(PictureObserver *observer);
    void RemoveObserver(PictureObserver *observer);
    void UpdateObservers();

//    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

};

#endif //TESTTRACKER22_PICTURE_H
