#ifndef TRAINRIDE_H
#define TRAINRIDE_H

#include <iostream>
#include <string>
#include "Train Utils/Wagon.h"
#include "Utils/Utils.h"
using namespace std;

typedef struct SeatInfo
{
    int seat_number;
    int wagon_number;
};

class TrainRide
{
private:
    string name;
    string date;
    string time;
    string destination;
    string origin;
    Wagon* wagons;
    int first_class;
    int second_class;

public:
    TrainRide(string name, string date, string time, string destination, string origin, int first_class_wagons, int second_class_wagons);
    ~TrainRide();
    SeatInfo reserve_any_seat(int class_type);
    int reserve_specific_seat(int wagon_number, int seat_number);
    void find_reserved_seats();
};

#endif // TRAINRIDE_H