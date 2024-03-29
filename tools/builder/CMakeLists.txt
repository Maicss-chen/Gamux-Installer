set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCE
        main.cpp
        MainWindow.h
        MainWindow.cpp
        Task.cpp
        Task.h
        MainWindow.ui
        ${CMAKE_SOURCE_DIR}/utils/utils.cpp
        ${CMAKE_SOURCE_DIR}/utils/utils.h
        ${CMAKE_SOURCE_DIR}/utils/TarFile.cpp
        ${CMAKE_SOURCE_DIR}/utils/TarFile.h
        ${CMAKE_SOURCE_DIR}/utils/tar.h
        ${CMAKE_SOURCE_DIR}/utils/Buffer.h
        ${CMAKE_SOURCE_DIR}/utils/Buffer.cpp
        CheckFileDialog.cpp
        CheckFileDialog.h
        ChooseSourceDialog.ui
        ChooseSourceDialog.cpp
        ChooseSourceDialog.h)

include_directories(${CMAKE_SOURCE_DIR}/utils)
find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Network
        REQUIRED
        )
find_package(Qt5 REQUIRED COMPONENTS Widgets)
add_executable(gamux-builder
        ${SOURCE}
        )
target_link_libraries(gamux-builder PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Network
        ${CURL_LIBRARIES}
        )