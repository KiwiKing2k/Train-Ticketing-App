cmake_minimum_required(VERSION 3.30)
project(Train_Ticketing_App)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Train_Ticketing_App
    main.cpp
        Wagon.cpp
        Wagon.h
        TrainRide.cpp
        TrainRide.h
        Utils/Utils.cpp
        Utils/Utils.h
)
