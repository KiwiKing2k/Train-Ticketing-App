#ifndef TRAINRIDE_H
#define TRAINRIDE_H

#include <iostream>
#include <string>
#include "Wagon.h"
#include "Utils/Utils.h"
using namespace std;

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
    int reserve_any_seat(int class_type);
};

#endif // TRAINRIDE_H