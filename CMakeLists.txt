cmake_minimum_required(VERSION 3.1.0)

project(FT232)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Path to QT instalation dir 
set(QT_CMAKE_DIR "/Users/Oleg/Qt/5.10.0/clang_64/lib/cmake")

# Add QT to path
set(CMAKE_PREFIX_PATH "${QT_CMAKE_DIR}")

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)

# Populate a CMake variable with the sources
set(FT232_SRCS
    	mainwindow.ui
    	mainwindow.cpp
    	main.cpp
		USBBus.cpp
		USBDevice.cpp)
# Tell CMake to create the helloworld executable
add_executable(FT232 ${FT232_SRCS})
# Use the Widgets module from Qt 5
target_link_libraries(FT232
		Qt5::Widgets
        usb-1.0)
