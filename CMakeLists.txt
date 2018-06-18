cmake_minimum_required(VERSION 3.1.0)

project(FT232)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Path to QT instalation dir 
set(QT_CMAKE_DIR "/home/vinnik/Qt5.7.0/5.7/gcc_64/lib/cmake")

# Add QT to path
set(CMAKE_PREFIX_PATH "${QT_CMAKE_DIR}")

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)

# External library directories
if(APPLE)
    set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib/macos)
else()
    set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib/linux)
endif()
link_directories(${LIB_DIR})

# Populate a CMake variable with the sources
set(FT232_SRCS
        mainwindow.ui
        mainwindow.cpp
        main.cpp
        USBBus.cpp
        USBDevice.cpp
        FT232.cpp)
# Create executable
add_executable(FT232 ${FT232_SRCS})

set(CMAKE_CXX_FLAGS " -pthread " )

set(LIB_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/lib/include)
target_include_directories(FT232 PUBLIC ${LIB_INCLUDE_DIR})

# Link with libraries
target_link_libraries(FT232
        ftd2xx
        Qt5::Widgets
        usb-1.0
        )
