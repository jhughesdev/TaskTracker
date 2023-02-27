/**
 * @file PictureFactory.h
 * @author Jacob Hughes
 *
 *
 */

#ifndef TESTTRACKER22_PICTUREFACTORY_H
#define TESTTRACKER22_PICTUREFACTORY_H

class Picture;

/**
 * Class that describes the picture factory, used to create a picture
 */
class PictureFactory {
private:

public:

    std::shared_ptr<Picture> Create(std::wstring imagesDir);
};

#endif //TESTTRACKER22_PICTUREFACTORY_H
