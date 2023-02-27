/**
 * @file PictureFactory.cpp
 * @author Jacob Hughes
 */

#include "pch.h"
#include "PictureFactory.h"
#include "Picture.h"

using namespace std;

/**
 * Factory method to create a new picture.
 * @param imagesDir Directory that contains the images for this application
 * @return The created picture
 */
std::shared_ptr<Picture> PictureFactory::Create(std::wstring imagesDir)
{
    shared_ptr<Picture> picture = make_shared<Picture>();

    return picture;
}