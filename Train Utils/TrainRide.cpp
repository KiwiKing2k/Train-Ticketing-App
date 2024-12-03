#include "Train Utils/TrainRide.h"
#include "Utils/Utils.h"
#include <regex>
#include <fstream>

TrainRide::TrainRide(string name, string date, string time, string destination, string origin, int first_class_wagons, int second_class_wagons)
    : name(name), date(date), time(time), destination(destination), origin(origin),
      wagons(new Wagon[first_class_wagons + second_class_wagons]), first_class(first_class_wagons), second_class(second_class_wagons)
{
    //date format check
    if (is_valid_date_format(date) == false)
    {
        throw std::invalid_argument("Invalid date format.");
    }

    try
    {
        is_valid_date(date);
    }catch (const std::invalid_argument& e)
    {
        delete[] wagons;
        throw;
    }

    //time check
    try
    {
        is_valid_time(time);
    }catch (const std::invalid_argument& e)
    {
        delete[] wagons;
        throw;
    }


    //City name check
    if (is_valid_city_name(destination) == false )
    {
        throw std::invalid_argument("Invalid destination city name.");
    }
    if (is_valid_city_name(origin) == false)
    {
        throw std::invalid_argument("Invalid origin city name.");
    }

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

SeatInfo TrainRide::reserve_any_seat(int class_type)
{
    int wagons_nr=0;
    if (class_type == 1)
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
            if (wagons[i].reserve_any_seat() != -1)
            {
                return {wagons[i].reserve_any_seat(), i};
            }
        }
    }
    throw std::invalid_argument("No available seats.");
}

int TrainRide::reserve_specific_seat(int wagon_number, int seat_number)
{
    if (wagon_number < 0 || wagon_number >= first_class + second_class)
    {
        throw std::invalid_argument("Invalid wagon number.");
    }
    if (wagons[wagon_number].reserve_seat(seat_number) == -1)
    {
        throw std::invalid_argument("Seat already reserved.");
    }
    return 1;
}

void TrainRide::find_reserved_seats()
{
    string file_name("../Data/Trains/" + this->name + ".csv");
    ifstream file(file_name);
    if (!file.is_open())
    {
        throw std::invalid_argument("File not found.");
    }
    string line;
    while (getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }
        int wagon_number, seat_number;
        wagon_number = stoi(line.substr(0, line.find(',')));
        line = line.substr(line.find(',') + 1);
        seat_number = stoi(line.substr(0, line.find(',')));
        reserve_specific_seat(wagon_number, seat_number);
    }
}