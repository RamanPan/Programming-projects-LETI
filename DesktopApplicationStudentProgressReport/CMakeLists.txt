cmake_minimum_required(VERSION 3.5)



project(DesktopApplicationStudentProgressReport VERSION 0.1 LANGUAGES CXX)



set(CMAKE_AUTOUIC ON)

set(CMAKE_AUTOMOC ON)

set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH D:/Qt/6.5.0/mingw_64)



find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS AxContainer REQUIRED)



set(PROJECT_SOURCES

        main.cpp

        mainwindow.cpp

        mainwindow.h

        mainwindow.ui

        findwidget.cpp findwidget.h findwidget.ui showresultwidget.cpp showresultwidget.h showresultwidget.ui calendarwidget.cpp calendarwidget.h calendarwidget.ui models/Student.cpp models/Student.h models/Subject.cpp models/Subject.h)



if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)

    qt_add_executable(DesktopApplicationStudentProgressReport

        MANUAL_FINALIZATION

        ${PROJECT_SOURCES}

    )

# Define target properties for Android with Qt 6 as:

#    set_property(TARGET DesktopApplicationStudentProgressReport APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR

#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)

# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

else()

    if(ANDROID)

        add_library(DesktopApplicationStudentProgressReport SHARED

            ${PROJECT_SOURCES}

        )

# Define properties for Android with Qt 5 after find_package() calls as:

#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")

    else()

        add_executable(DesktopApplicationStudentProgressReport

            ${PROJECT_SOURCES}

        )

    endif()

endif()



target_link_libraries(DesktopApplicationStudentProgressReport PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

target_link_libraries(DesktopApplicationStudentProgressReport PRIVATE Qt${QT_VERSION_MAJOR}::AxContainer)



set_target_properties(DesktopApplicationStudentProgressReport PROPERTIES

    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com

    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}

    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}

    MACOSX_BUNDLE TRUE

    WIN32_EXECUTABLE TRUE

)



install(TARGETS DesktopApplicationStudentProgressReport

    BUNDLE DESTINATION .

    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})



if(QT_VERSION_MAJOR EQUAL 6)

    qt_finalize_executable(DesktopApplicationStudentProgressReport)

endif()

