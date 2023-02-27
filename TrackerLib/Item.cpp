/**
 * @file Item.cpp
 * @author Jacob Hughes
 */

#include "pch.h"
#include "Item.h"
#include "Tracker.h"

/**
 * Constructor
 * @param tracker The tracker this item is a member of
 */
Item::Item(Tracker *tracker) : mTracker(tracker)
{
}


/**
 * Save this item to an XML node
 * @param node The parent node we are going to be a child of
 * @return wxXmlNode that we saved the item into
 */
wxXmlNode *Item::XmlSave(wxXmlNode *node)
{
    auto itemNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"event");
    node->AddChild(itemNode);

    itemNode->AddAttribute(L"x", wxString::FromDouble(mX));
    itemNode->AddAttribute(L"y", wxString::FromDouble(mY));

    return itemNode;
}
