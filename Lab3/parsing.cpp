#include <string>

#include "parsing.h"

std::vector<std::string> parse_broken_routes(const std::string &broken_routes) {
    std::vector<std::string> routes;
    std::string current_route;
    for (char sym: broken_routes)
        if (sym == ',' || sym == '.') {
            routes.push_back(current_route);
            current_route.clear();
        } else current_route += sym;
    if (!current_route.empty())
        routes.push_back(current_route);
    if (routes.empty())
        throw std::runtime_error("Transport stops are absent");
    return routes;
}

std::pair<double, double> parse_broken_coordinates(const std::string &broken_coordinates) {
    std::pair<double, double> coordinates;
    sscanf(broken_coordinates.c_str(), "%lf,%lf", &coordinates.first, &coordinates.second);
    // c_str() - return string in c language format
    return coordinates;
}

Stop parse_xml_stop(const pugi::xml_node &xml_stop) {
    Stop stop;
    stop.street = xml_stop.child_value("the_official_name");
    stop.type_of_vehicle = xml_stop.child_value("type_of_vehicle");
    stop.routes = parse_broken_routes(xml_stop.child_value("routes"));
    stop.coordinates = parse_broken_coordinates(xml_stop.child_value("coordinates"));
    return stop;
}
