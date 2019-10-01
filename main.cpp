#include "date/tz.h"
#include <iostream>

int
main()
{
    using namespace std::chrono_literals;
    using namespace date;

    auto departure = make_zoned("America/New_York", local_days{December/30/1978} + 12h + 1min);
    auto flight_length = 14h + 44min;
    auto arrival = make_zoned("Asia/Tehran", departure.get_sys_time() + flight_length);

    std::cout << "departure NYC time:  " << departure << '\n';
    std::cout << "flight time is       " << make_time(flight_length) << '\n';
    std::cout << "arrival Tehran time: " << arrival << '\n';
}