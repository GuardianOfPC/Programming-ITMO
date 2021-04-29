#ifndef PROGA3_PARSING_H
#define PROGA3_PARSING_H

#include "pugixml.hpp"

#include "stop.h"

Stop parse_xml_stop(const pugi::xml_node& xml_stop);

#endif //PROGA3_PARSING_H
