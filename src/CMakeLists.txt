
set(SOURCE
        utils.h
        MainWindow.h
        main.cpp
        utils.cpp
        MainWindow.cpp
        ReadMePage.cpp
        ReadMePage.h
        Page.cpp
        Page.h
        ChooseTargetPage.cpp
        ChooseTargetPage.h
        OptionsPage.cpp
        OptionsPage.h
        InstallPage.cpp
        InstallPage.h
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
