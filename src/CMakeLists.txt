cmake_minimum_required(VERSION 3.7)

project(lapack_test_src VERSION 1.0.0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(LAPACK REQUIRED)
find_package(GSL REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR}
                    ${Qt5Widgets_INCLUDE_DIRS}
                    ${Qt5Core_INCLUDE_DIRS}
                    ${Qt5Gui_INCLUDE_DIRS}
                    ${LAPACK_INCLUDE_DIRS}
                    )

set(HEADERS
    ui/MatrixWidget.h
    ui/MatrixModel.h
    ui/MatrixDelegate.h
    MatrixObject.h
    math/LMatrix.h
)

set(FORMS
    ui/matrix_widget.ui
)

set(SOURCES
    ui/MatrixWidget.cpp
    ui/MatrixModel.cpp
    ui/MatrixDelegate.cpp
    MatrixObject.cpp
    math/LMatrix.cpp
)

set(RESOURCES
)

qt5_wrap_ui(UIS_HDRS ${FORMS} )

include_directories( ui )
include_directories( math )

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS} ${UIS_HDRS}
    ${RESOURCES} ${LAPACK_LIBRARIES})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets GSL::gsl GSL::gslcblas
    ${LAPACK_LIBRARIES})

set(${PROJECT_NAME}_RUNTIME_LIBRARY_DIRS ${CMAKE_INSTALL_LIBDIR} )

target_include_directories(${PROJECT_NAME} PUBLIC
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}> ${LAPACK_INCLUDE_DIRS})

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION lib
)

install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

