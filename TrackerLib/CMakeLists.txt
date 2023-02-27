project(TrackerLib)

set(SOURCE_FILES MainFrame.cpp MainFrame.h pch.h ProjectView.cpp ProjectView.h Tracker.cpp Tracker.h Item.cpp Item.h ids.h StandardEvent.cpp StandardEvent.h Picture.cpp Picture.h PictureObserver.cpp PictureObserver.h ColorDlg.cpp ColorDlg.h PictureFactory.cpp PictureFactory.h Day.cpp Day.h Month.cpp Month.h Year.cpp Year.h EventDlg.cpp EventDlg.h DateDlg.cpp DateDlg.h)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})