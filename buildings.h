/* buildings.h */

//
// a collection of buildings in the open street map
//
// Sally Liao
// Northwestern University
// CS 211
//
// Original author: Prof. Joe Hummel
//

#pragma once
#include <vector>
#include "building.h"
#include "footways.h"
#include "busstops.h"
#include "nodes.h"
#include "node.h"
#include "tinyxml2.h"
using namespace std;
using namespace tinyxml2;

//
// Keeps track of all the buildings in the map
//
class Buildings {
    public: 
        vector<Building> MapBuildings;

        //
        // readMapBuildings
        //
        // given a XML doc, reads through the document and
        // stores all the buildings into the given vector
        //
        void readMapBuildings(XMLDocument& xmldoc);

        //
        // print
        //
        // prints out all the buildings in MapBuildings
        //
        void print() const;

        //
        // findAndPrint
        //
        // given a string input on what to search for, outputs all relevant buildings
        // and their nodes
        //
        void findAndPrint(string name, Nodes& nodes, Footways& footways, BusStops& busstops, CURL* curl);

        //
        // accessors/getters
        //
        int getNumMapBuildings() const;
};