/* buildings.cpp*/

//
// a collection of buildings in an open street map
//
// Sally Liao
// Northwestern University
// CS 211
//
// Original author: Prof. Joe Hummel
//

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

#include "building.h"
#include "buildings.h"
#include "footway.h"
#include "footways.h"
#include "node.h"
#include "nodes.h"
#include "osm.h"
#include "tinyxml2.h"
#include "busstops.h"

//
// readMapBuildings
//
// given a XML doc, reads through the document and
// stores all the buildings into the given vector
//
void Buildings::readMapBuildings(XMLDocument& xmldoc) {
    XMLElement* osm = xmldoc.FirstChildElement("osm");
    XMLElement* way = osm->FirstChildElement("way");

    while (way != nullptr) { //loop through all ways
        if (osmContainsKeyValue(way, "building", "university")) { // if is a building
            // get id, name, and street addr and put into a building
            const XMLAttribute* attrId = way->FindAttribute("id");
            long long id = attrId->Int64Value();
            string name = osmGetKeyValue(way, "name");
            string streetAddr = osmGetKeyValue(way, "addr:housenumber") + " " + osmGetKeyValue(way, "addr:street");
            Building B(id, name, streetAddr);
            XMLElement* nd = way->FirstChildElement("nd");

            while (nd != nullptr) { //get all nodes + add
                const XMLAttribute* ndref = nd->FindAttribute("ref");
                assert(ndref != nullptr);
                long long id = ndref->Int64Value();
                B.add(id); // add node
                nd = nd->NextSiblingElement("nd");
            }
            MapBuildings.push_back(B);
        }
        way = way->NextSiblingElement("way");
    }
    
}

//
// print
//
// prints out all the buildings in MapBuildings
//
void Buildings::print() const {
    for (const Building& building : MapBuildings) {
        cout << building.ID << ": " << building.Name << ", " << building.StreetAddress << endl;
    }
}

//
// findAndPrint
//
// given a string input on what to search for, outputs all relevant buildings, footways, 
// and their nodes
//
void Buildings::findAndPrint(string name, Nodes& nodes, Footways& footways, BusStops& busstops, CURL* curl) {
    bool found = false;
    for (Building& building : MapBuildings) { // loop through all buildings
        if (building.Name.find(name) != string::npos) { //if building found
            found = true;
            building.print(nodes, footways, busstops, curl);
        }
    }
    if (!found) {
        cout << "No such building" << endl;
    }
}

//
// getNumMapBuildings
//
// returns num of map buildings
// 
int Buildings::getNumMapBuildings() const {
    return MapBuildings.size();
}
