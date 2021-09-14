cmake_minimum_required(VERSION 3.7)

project(lapack_test_app VERSION 1.0)

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
find_package(GSL REQUIRED)    # See below (2)

include_directories(${PROJECT_SOURCE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR}
                    ${Qt5Widgets_INCLUDE_DIRS}
                    ${Qt5Core_INCLUDE_DIRS}
                    ${Qt5Gui_INCLUDE_DIRS}
                    ${Qt5Network_INCLUDE_DIRS}
                    ${GSL_INCLUDE_DIRS}
                    ${gis_patrol_INCLUDE_DIRS}
                    )

set(HEADERS
    LapackTestMainWindow.h
)

set(FORMS
    lapack_test_main_window.ui
)

set(SOURCES
    LapackTestMainWindow.cpp
    main.cpp
)

set(RESOURCES
)

qt5_wrap_ui(UIS_HDRS ${FORMS} )

include_directories( ../src ../src/ui )
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${UIS_HDRS} ${RESOURCES}  )

target_link_libraries(${PROJECT_NAME} Qt5::Widgets GSL::gsl
    GSL::gslcblas ${LAPACK_LIBRARIES} lapack_test_src)

install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
)
