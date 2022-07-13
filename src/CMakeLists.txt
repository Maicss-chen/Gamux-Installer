
set(SOURCE
        ${CMAKE_SOURCE_DIR}/utils/utils.h
        ${CMAKE_SOURCE_DIR}/utils/utils.cpp
        ${CMAKE_SOURCE_DIR}/utils/TarFile.cpp
        ${CMAKE_SOURCE_DIR}/utils/TarFile.h
        MainWindow.h
        main.cpp
        MainWindow.cpp
        pages/InstallPage.cpp
        pages/InstallPage.h
        Task.cpp
        Task.h
        ../utils/tar.h widgets/GWidget.cpp widgets/GWidget.h widgets/GTitleBar.cpp widgets/GTitleBar.h widgets/GButton.cpp widgets/GButton.h pages/MainPage.cpp pages/MainPage.h widgets/GProgressBar.cpp widgets/GProgressBar.h widgets/GHeader.cpp widgets/GHeader.h)
include_directories(${CMAKE_SOURCE_DIR}/utils)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED
        )
        


add_executable(gamux-installer
        ${SOURCE})

target_link_libraries(gamux-installer
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )
