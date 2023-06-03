cmake_minimum_required(VERSION 3.5)

project(qt6-new-demo-qgraphicsview VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(Qt6_DIR "C:/Qt/6.6.0/mingw_64/lib/cmake/Qt6")

set(LIBREOFFICE_LIBS
    libuno_cppu libuno_cppuhelpergcc3 libuno_sal libuno_salhelpergcc3
    libosl libpspell libhyphen ${LIBREOFFICE_EXTRA_LIBS} ${CMAKE_DL_LIBS})

include_directories(${Python_INCLUDE_DIRS})
#include_directories(${PYTHONQT_INCLUDE_DIR})

find_library(LIBREOFFICE_LIBS liblibreoffice HINTS /usr/lib/libreoffice/program)

find_package(Python COMPONENTS Development REQUIRED)
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
link_libraries(${Python3_LIBRARIES})

find_package(Qt6 COMPONENTS PrintSupport REQUIRED)
find_package(Qt6 COMPONENTS Widgets REQUIRED)
#find_package(Qt6 REQUIRED COMPONENTS WebEngineWidgets)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
#find_package(PythonQt REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        textedit.h
        textedit.cpp
        textedit.ui
        resource.qrc
        view.h
        view.cpp
        commands.h
        commands.cpp
        custom_view.h
        custom_view.cpp
        scene.h
        scene.cpp
        formula_dialog.cpp
        formula_dialog.h
        formula_dialog.ui
        number.cpp
        number.h
        number.ui
        painterapptypes.h
        periodic_tdialog.cpp
        periodic_tdialog.h
        periodic_tdialog.ui
        strokeitem.cpp
        strokeitem.h
        colorpicker.cpp
        colorpicker.h
        doubleclickbutton.cpp
        doubleclickbutton.h
        symbol_dialog.h
        symbol_dialog.cpp
        symbol_dialog.ui
        trail.py
        pyrun.cpp
        pyrun.h
        benzene.h
        benzene.cpp
        hexagon.h
        hexagon.cpp
        hoverellipseitem.h
        hoverellipseitem.cpp
        #mygraphicsview.h
        #mygraphicsview.cpp
        pentagon.h
        pentagon.cpp
        myrectitem.h
        myrectitem.cpp
        lineitem.h
        lineitem.cpp
        #searchdialog.h
        #searchdialog.cpp
        editablepixmapitem.cpp
        editablelineitem.h
        horizontalruler.h
        horizontalruler.cpp
        verticalruler.h
        verticalruler.cpp
        typerectitem.h
        typerectitem.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(qt6-new-demo-qgraphicsview
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET qt6-new-demo-qgraphicsview APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(qt6-new-demo-qgraphicsview SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(qt6-new-demo-qgraphicsview
            ${PROJECT_SOURCES}
        )
    endif()
endif()


target_link_libraries(qt6-new-demo-qgraphicsview PUBLIC ${PYTHON_LIBRARIES})
target_include_directories(qt6-new-demo-qgraphicsview PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(qt6-new-demo-qgraphicsview PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt6::PrintSupport)# ${LIBREOFFICE_LIBS})
#target_link_libraries(target PRIVATE Qt::WebEngineWidgets)
#target_link_libraries(${qt6-new-demo-qgraphicsview} ${PYTHONQT_LIBRARIES})

#target_link_libraries(qt6-new-demo-qgraphicsview PRIVATE ${Python3_LIBRARIES})
target_link_libraries(qt6-new-demo-qgraphicsview PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
find_library(LIBREOFFICE_LIBS liblibreoffice HINTS "C:/Program Files/LibreOffice/sdk/lib")
target_link_libraries(qt6-new-demo-qgraphicsview PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt6::PrintSupport)

set_target_properties(qt6-new-demo-qgraphicsview PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(qt6-new-demo-qgraphicsview)
endif()
