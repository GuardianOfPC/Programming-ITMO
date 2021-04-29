#ifndef PROGA3_STOP_H
#define PROGA3_STOP_H

#include <string>
#include <vector>

const std::vector<std::string> types_of_vehicles = {
        "Трамвай",
        "Троллейбус",
        "Автобус",
};

struct Stop {
    std::string street;
    std::string type_of_vehicle;
    std::vector<std::string> routes;
    std::pair<double, double> coordinates;
};

#endif //PROGA3_STOP_H
