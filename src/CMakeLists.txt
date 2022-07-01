
set(SOURCE
        utils.h
        MainWindow.h
        main.cpp
        utils.cpp
        MainWindow.cpp
        pages/ReadMePage.cpp
        pages/ReadMePage.h
        pages/Page.cpp
        pages/Page.h
        pages/ChooseTargetPage.cpp
        pages/ChooseTargetPage.h
        pages/OptionsPage.cpp
        pages/OptionsPage.h
        pages/InstallPage.cpp
        pages/InstallPage.h
        Task.cpp
        Task.h)

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
