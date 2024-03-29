cmake_minimum_required(VERSION 3.14)

# Set a variable for commands below
set(PROJECT_NAME led_lighting)

# Define your project and language
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)

set(${PROJECT_NAME}_BOARD nano328)

link_directories(./libs)

# Define the source code
set(${PROJECT_NAME}_SRCS
        led_lighting.cpp
        utils.h utils.cpp
        Settings.h Settings.cpp
        input/InputManager.h input/InputManager.cpp
        input/EncoderHandler.h input/EncoderHandler.cpp
        input/TTP229Handler.h input/TTP229Handler.cpp
        led/Blinker.h led/Blinker.cpp
        led/LedLine.h led/LedLine.cpp
        led/LedsManager.h led/LedsManager.cpp)

# Define the port for uploading code to the Arduino
set(${PROJECT_NAME}_PORT /dev/ttyUSB0)

# Command to generate code arduino firmware (.hex file)
generate_arduino_firmware(${PROJECT_NAME})
