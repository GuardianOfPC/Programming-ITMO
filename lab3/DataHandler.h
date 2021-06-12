#ifndef PROGA3_DATAHANDLER_H
#define PROGA3_DATAHANDLER_H

#include <string>
#include <unordered_map>

#include "stop.h"

// structs for result storing

struct MaxStreet {
    std::string name;
    int n_stops;
};

struct MaxRouteByStops {
    std::string name;
    int n_stops;
};

struct MaxRouteByDistance {
    std::string name;
    double distance;
};

// struct for calculations

struct Route_Information {
    std::pair<double, double> last_stop_coordinates;
    double distance;
    int n_stops;
};

class DataHandler {
private:
    void handle_street(const std::string &street_name);
    void handle_route(const std::string &type_of_vehicle, const std::string &route_name, const std::pair<double, double> &coordinates);

    std::unordered_map<std::string, int> streets_counters;
    std::unordered_map<std::string, Route_Information> routes_information;
public:
    DataHandler();
    void handle_stop(const Stop& stop);
    std::unordered_map<std::string, MaxRouteByStops> max_routes_by_stops;
    std::unordered_map<std::string, MaxRouteByDistance> max_routes_by_distance;
    MaxStreet max_street;
};

#endif //PROGA3_DATAHANDLER_H
