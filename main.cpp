#include <iostream>
#include <string>
#include <chrono>

#include "building.h"
#include "buildings.h"
#include "node.h"
#include "nodes.h"
#include "osm.h"
#include "tinyxml2.h"
#include "footways.h"
#include "footway.h"
#include "busstop.h"
#include "busstops.h"
#include "curl_util.h"

using namespace std;
using namespace tinyxml2;

int main() {
    // load file + CURL
    string filename;
    cout << "** NU open street map **" << endl << endl;
    cout << "Enter map filename>" << endl;
    getline(cin, filename);
    XMLDocument in;
    if (!osmLoadMapFile(filename, in)) {
        return 0;
    }
    CURL* curl = curl_easy_init();
    if (curl == nullptr) {
        cout << "**ERROR:" << endl;
        cout << "**ERROR: unable to initialize curl library" << endl;
        cout << "**ERROR:" << endl;
        return 0;
    }

    Nodes nodes;
    nodes.readMapNodes(in);
    Buildings buildings;
    buildings.readMapBuildings(in);
    Footways footways;
    footways.readMapFootways(in);
    BusStops busstops("bus-stops.txt");
    cout << "# of nodes: " << nodes.getNumMapNodes() << endl;
    cout << "# of buildings: " << buildings.getNumMapBuildings() << endl;
    cout << "# of bus stops: " << busstops.getNumStops() << endl << endl;

    // sort each footway's nodeids
    footways.sortFootways();

    // loop of outputting building info from search
    cout << "Enter building name (partial or complete), or * to list, or @ for bus stops, or $ to end> " << endl;
    string input;
    getline(cin, input);

    while (input != "$") {
        if (input == "*") {
            buildings.print();
        }
        else if (input == "@") {
            busstops.printAll();
        }
        else {
            vector<Building> toPrint;
            buildings.findAndPrint(input, nodes, footways, busstops, curl);
        }
        cout << "Enter building name (partial or complete), or * to list, or @ for bus stops, or $ to end> " << endl;
        getline(cin, input);
    }

    //close curl library
    curl_easy_cleanup(curl);

    // output collected info
    cout << endl << "** Done **" << endl;
    return 0;
}