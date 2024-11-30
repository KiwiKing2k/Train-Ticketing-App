#include <iostream>
#include <string>
#include "TrainRide.h"
using namespace std;

int main()
{
    TrainRide train("Train1", "12.12.2020", "12:00", "Bucharest", "Cluj", 2, 3);
    cout << train.reserve_any_seat(1) << endl;
    return 0;
}
