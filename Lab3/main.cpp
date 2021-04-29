#include <iostream>

#include "pugixml.hpp"

#include "parsing.h"
#include "DataHandler.h"

const std::string XML_FILE_NAME = "data.xml";

int main() {
    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file(XML_FILE_NAME.c_str());
    if (!result)
        throw std::invalid_argument(
                "File " + XML_FILE_NAME + " is invalid\n"
                "Error description: " + result.description() + "\n"
        );
    DataHandler dataHandler;
    pugi::xml_node curr_xml_stop = document.first_child().first_child();
    Stop stop;
    while (curr_xml_stop) {
        stop = parse_xml_stop(curr_xml_stop);
        dataHandler.handle_stop(stop);
        curr_xml_stop = curr_xml_stop.next_sibling();
    }
    std::cout << "Task 1 : Max Routes By Stops" << "\n";
    for (auto& type: types_of_vehicles) {
        std::cout << type << ": " << dataHandler.max_routes_by_stops[type].name << "\n";
    }
    std::cout << "\n";
    std::cout << "Task 2 : Max Routes By Distance" << "\n";
    for (auto& type: types_of_vehicles) {
        std::cout << type << ": " << dataHandler.max_routes_by_distance[type].name << "\n";
    }
    std::cout << "\n";
    std::cout << "Task 3 : Max Street Name" << "\n";
    std::cout << dataHandler.max_street.name << "\n";
    return 0;
}

//std::cout << "MaxStreet: " << stop.street << std::endl;
//std::cout << "Type of vehicle: " << stop.type_of_vehicle << std::endl;
//std::cout << "Routes:" << std::endl;
//for (std::string& route: stop.routes)
//std::cout << route << std::endl;
//std::cout << "Coordinates: " << stop.coordinates.first << " " << stop.coordinates.second << std::endl;