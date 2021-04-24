#include "pugi/src/pugixml.hpp"
#include <iostream>

class Jopa{
private:
    pugi::xml_document document;
    pugi::xml_node root;
public:

    void open(){
    pugi::xml_parse_result result = document.load_file("data.xml");
    root = document.child(L"dataset");
}

    void parse(){
        std::wstring type, route, coord;
    }
};