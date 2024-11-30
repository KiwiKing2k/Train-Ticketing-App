#include "TrainRide.h"

TrainRide::TrainRide(string name, string date, string time, string destination, string origin, int first_class_wagons, int second_class_wagons)
    : name(name), date(date), time(time), destination(destination), origin(origin),
      wagons(new Wagon[first_class_wagons + second_class_wagons]), first_class(first_class_wagons), second_class(second_class_wagons)
{
    for (int i = 0; i < first_class_wagons; i++)
    {
        this->wagons[i].WagonAssigner(1);
    }
    for (int i = first_class_wagons; i < first_class_wagons + second_class_wagons; i++)
    {
        this->wagons[i].WagonAssigner(2);
    }
}

TrainRide::~TrainRide()
{
    delete[] wagons;
}

int TrainRide::reserve_any_seat(int class_type)
{
    int wagons_nr = (class_type == 1) ? first_class : second_class;
    for (int i = 0; i < wagons_nr; i++)
    {
        if (wagons[i].class_type == class_type)
        {
            if (wagons[i].reserve_any_seat() != -1)
            {
                return 1;
            }
        }
    }
    return -1;
}