cmake_minimum_required(VERSION 3.30)
project(Distortion)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Distortion
    Distortion.cpp
    Distortion.h
    main.cpp
    OscEngine.cpp
    OscEngine.h
    PitchProtocol.h)
