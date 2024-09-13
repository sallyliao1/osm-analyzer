/*busstops.h*/

//
// a collection of all BusStops
// 
// Sally Liao
// Northwestern University
// CS 211
// 

#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <iostream>
#include <algorithm>

#include "busstops.h"
#include "busstop.h"
#include "dist.h"

using namespace std;

BusStops::BusStops(string filename) {
    ifstream input;
    input.open(filename);
    assert(input.is_open());

    string line;
    while (!input.eof()) {
        getline(input, line);
        if (input.fail()) {
            break;
        }
        stringstream parser(line);
        string stopid, busroute, stopname, diroftravel, stoplocation, lat, lon;
        getline(parser, stopid, ',');
        getline(parser, busroute, ',');
        getline(parser, stopname, ',');
        getline(parser, diroftravel, ',');
        getline(parser, stoplocation, ',');
        getline(parser, lat, ',');
        getline(parser, lon);

        pair<double, double> location;
        location.first = stod(lat);
        location.second = stod(lon);

        allBusStops.emplace(stoll(stopid), stoi(busroute), stopname, diroftravel, stoplocation, location);
    }
}

//
// printAll
//
// prints all bus stops
//
void BusStops::printAll() {
    for (const BusStop& b : allBusStops) {
        b.print();
    }
}

//
// compareDist
//
// compares the distance between bus stops
//
bool compareDist(pair<BusStop, double> a, pair<BusStop, double> b) {
    return a.second < b.second;
}

//
// getClosestStop
//
// returns the closest stop given a position
//
BusStop BusStops::getClosestStop(pair<double, double> location, bool north) {
    vector<pair<BusStop, double>> stopIDToDist;
    string comp;
    if (north) {
        comp = "Northbound";
    }
    else {
        comp = "Southbound";
    }
    for (const BusStop& b : allBusStops) {
        if (b.getDirOfTravel().compare(comp) == 0) {
            double dist = distBetween2Points(location.first, location.second, b.getLat(), b.getLon());
            stopIDToDist.emplace_back(make_pair(b, dist));
        }
    }

    sort(stopIDToDist.begin(), stopIDToDist.end(), compareDist);

    return stopIDToDist[0].first;
    
}

//
// getNumStops
//
// returns num of stops
//
int BusStops::getNumStops() const {
    return allBusStops.size();
}