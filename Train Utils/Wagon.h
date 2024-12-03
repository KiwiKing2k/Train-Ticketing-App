#ifndef WAGON_H
#define WAGON_H

#include <iostream>

using namespace std;

typedef struct Seat
{
    int seat_number;
    bool reserved;
} Seat;

class Wagon
{
private:
    int class_type; // 1 or 2
    const int max_capacity = 80; // standard for CFR
    Seat seats[80];
    int reserved_seats;

public:
    Wagon();
    void WagonAssigner(int class_type);
    int reserve_any_seat();
    int reserve_seat(int seat_number);
    void see_free_seats();
    void see_reserved_seats();

    friend class TrainRide;
};

#endif // WAGON_H