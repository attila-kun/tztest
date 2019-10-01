#include "date/tz.h"
#include <iostream>
#include <type_traits>

class OffsetZone
{
    std::chrono::seconds offset_;

public:
    explicit OffsetZone(std::chrono::seconds offset)
        : offset_{offset}
        {}

    template <class Duration>
        date::local_time<std::common_type_t<Duration, std::chrono::seconds>>
        to_local(date::sys_time<Duration> tp) const
        {
            using namespace date;
            using namespace std;
            using namespace std::chrono;
            using LT = local_time<common_type_t<Duration, seconds>>;
            return LT{(tp + offset_).time_since_epoch()};
        }

    template <class Duration>
        auto
        to_sys(date::local_time<Duration> tp) const
        {
            using namespace date;
            using namespace std;
            using namespace std::chrono;
            using ST = sys_time<common_type_t<Duration, seconds>>;
            return ST{(tp - offset_).time_since_epoch()};
        }
};

int
main()
{
    using namespace date;
    using namespace std::chrono;
    long utcOffset = 60*60*12;
    OffsetZone p3_45{seconds(utcOffset)};
    auto hello = local_days(year_month_day(year(2019), month(October), day(1)));
    zoned_time<milliseconds, OffsetZone*> zt{&p3_45, floor<milliseconds>(hello)};
    std::cout << zt.get_sys_time() << '\n';
    std::cout << zt.get_local_time() << '\n';
}