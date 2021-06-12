#include <cmath>

#include "DataHandler.h"

DataHandler::DataHandler(): max_street({.n_stops = 0}) // иначе в n_stops будет мусор (при выделении памяти)
{}

void DataHandler::handle_street(const std::string &street_name) {
    if (street_name.empty())
        return;
    streets_counters[street_name]++;
    if (streets_counters[street_name] > max_street.n_stops){
        max_street.name = street_name;
        max_street.n_stops = streets_counters[street_name];
    }
}

static double distance(double lat1, double lon1, double lat2, double lon2) {
    double lat = (lat2-lat1) * (M_PI/180);
    double lon = (lon2-lon1) * (M_PI/180);
    double res = sin(lat/2) * sin(lat/2) + cos(lat1*(M_PI/180)) * cos(lat2*(M_PI/180)) * sin(lon/2) * sin(lon/2);
    return 2 * 6371 * atan2(sqrt(res), sqrt(1-res));
}

void DataHandler::handle_route(const std::string &type_of_vehicle, const std::string &route_name, const std::pair<double, double> &coordinates) {
    Route_Information& route_information = routes_information[type_of_vehicle + route_name];
    route_information.n_stops++;
    MaxRouteByStops& maxRouteByStops = max_routes_by_stops[type_of_vehicle];
    if (maxRouteByStops.n_stops < route_information.n_stops){
        maxRouteByStops.name = route_name;
        maxRouteByStops.n_stops = route_information.n_stops;
    }

    double lat_first = route_information.last_stop_coordinates.first, lat_second = coordinates.first;
    double lon_first = route_information.last_stop_coordinates.second, lon_second = coordinates.second;
    route_information.distance += distance(lat_first, lon_first, lat_second, lon_second);
    route_information.last_stop_coordinates = coordinates;
    MaxRouteByDistance& maxRouteByDistance = max_routes_by_distance[type_of_vehicle];
    if (maxRouteByDistance.distance < route_information.distance) {
        maxRouteByDistance.name = route_name;
        maxRouteByDistance.distance = route_information.distance;
    }
}

void DataHandler::handle_stop(const Stop &stop) {
    handle_street(stop.street);
    for (const std::string& route: stop.routes)
        handle_route(stop.type_of_vehicle, route, stop.coordinates);
}
