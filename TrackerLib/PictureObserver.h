/**
 * @file PictureObserver.h
 * @author Jacob Hughes
 *
 *
 */

#ifndef TESTTRACKER22_PICTUREOBSERVER_H
#define TESTTRACKER22_PICTUREOBSERVER_H

class Picture;

/**
 * Class that describes a picture observer
 * The observer pattern is used to update multiple views
 */
class PictureObserver {
private:
    /// Picture we are observing
    std::shared_ptr<Picture> mPicture;

protected:
    /// Constructor (protected)
    PictureObserver() {}

public:
    /// Copy constructor (disabled)
    PictureObserver(const PictureObserver &) = delete;

    ~PictureObserver();

    /// Assignment operator
    void operator=(const PictureObserver &) = delete;

    /// This function is called to update any observers
    virtual void UpdateObserver() = 0;

    virtual void SetPicture(std::shared_ptr<Picture> picture);

    /**
     * Get the picture we are observing
     * @return Pointer to picture we are observing
     */
    std::shared_ptr<Picture> GetPicture() {return mPicture;}

};

#endif //TESTTRACKER22_PICTUREOBSERVER_H
