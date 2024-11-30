#include <iostream>
#include <string>
using namespace std;

typedef struct Seat
{
    int seat_number;
    bool reserved;
};

class Wagon
{
private:
    int class_type; // 1 or 2
    const int max_capacity = 80; /// standard for CFR
    Seat seats[80];
    int reserved_seats;

public:
    Wagon()
    {
    };

    void WagonAssigner(int class_type)
    {
        this->class_type = class_type;
        reserved_seats = 0;
        for (int i = 0; i < max_capacity; i++)
        {
            seats[i].seat_number = i + 1;
            seats[i].reserved = false;
        }
    }

    int reserve_any_seat()
    {
        if (reserved_seats < max_capacity)
        {
            for (int i = 0; i < max_capacity; i++)
            {
                if (seats[i].reserved == false)
                {
                    seats[i].reserved = true;
                    reserved_seats++;
                    return seats[i].seat_number;
                }
            }
        }
        return -1;
    }

    int reserve_seat(int seat_number)
    {
        if (seat_number > 0 && seat_number <= max_capacity)
        {
            if (seats[seat_number - 1].reserved == false)
            {
                seats[seat_number - 1].reserved = true;
                reserved_seats++;
                return seat_number;
            }
        }
        return -1;
    }

    void see_free_seats()
    {
        for (int i = 0; i < max_capacity; i++)
        {
            if (seats[i].reserved == false)
            {
                cout << seats[i].seat_number << " ";
            }
        }
        cout << endl;
    }

    void see_reserved_seats()
    {
        for (int i = 0; i < max_capacity; i++)
        {
            if (seats[i].reserved == true)
            {
                cout << seats[i].seat_number << " ";
            }
        }
        cout << endl;
    }

    friend class TrainRide;
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
    TrainRide(string name, string date, string time, string destination, string origin, int first_class_wagons, int second_class_wagons)
        : name(name), date(date), time(time), destination(destination), origin(origin),
          wagons(new Wagon[first_class_wagons + second_class_wagons]), first_class(first_class_wagons), second_class
          (second_class_wagons)
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

    ~TrainRide()
    {
        delete[] wagons;
    }

    int reserve_any_seat(int class_type)
    {
        int wagons_nr = 0;
        if (class_type)
        {
            wagons_nr = first_class;
        }
        else
        {
            wagons_nr = second_class;
        }
        for (int i = 0; i < wagons_nr; i++)
        {
            if (wagons[i].class_type == class_type)
            {
                if (wagons[i].reserve_any_seat())
                {
                    return 1;
                }
            }
        }
        return -1;
    }
};

int main()
{
    TrainRide train("Train1", "12.12.2020", "12:00", "Bucharest", "Cluj", 2, 3);
    cout << train.reserve_any_seat(1) << endl;
    return 0;
}
