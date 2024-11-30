#include "Wagon.h"

Wagon::Wagon() = default;

void Wagon::WagonAssigner(int class_type)
{
    this->class_type = class_type;
    reserved_seats = 0;
    for (int i = 0; i < max_capacity; i++)
    {
        seats[i].seat_number = i + 1;
        seats[i].reserved = false;
    }
}

int Wagon::reserve_any_seat()
{
    if (reserved_seats < max_capacity)
    {
        for (int i = 0; i < max_capacity; i++)
        {
            if (!seats[i].reserved)
            {
                seats[i].reserved = true;
                reserved_seats++;
                return seats[i].seat_number;
            }
        }
    }
    return -1;
}

int Wagon::reserve_seat(int seat_number)
{
    if (seat_number > 0 && seat_number <= max_capacity)
    {
        if (!seats[seat_number - 1].reserved)
        {
            seats[seat_number - 1].reserved = true;
            reserved_seats++;
            return seat_number;
        }
    }
    return -1;
}

void Wagon::see_free_seats()
{
    for (int i = 0; i < max_capacity; i++)
    {
        if (!seats[i].reserved)
        {
            cout << seats[i].seat_number << " ";
        }
    }
    cout << endl;
}

void Wagon::see_reserved_seats()
{
    for (int i = 0; i < max_capacity; i++)
    {
        if (seats[i].reserved)
        {
            cout << seats[i].seat_number << " ";
        }
    }
    cout << endl;
}