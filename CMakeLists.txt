cmake_minimum_required(VERSION 3.30)
project(Train_Ticketing_App)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Train_Ticketing_App
    main.cpp
        Utils/Utils.cpp
        Utils/Utils.h
        Admin/Operator.cpp
        Admin/Operator.h
        "Train Utils/Wagon.cpp"
        "Train Utils/Wagon.h"
        "Train Utils/TrainRide.cpp"
        "Train Utils/TrainRide.h"
        Users/User.cpp
        Users/User.h
        Encryption/Encryption.cpp
        Encryption/Encryption.h
)
