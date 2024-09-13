/*busstops.h*/

//
// a collection of all BusStops
// 
// Sally Liao
// Northwestern University
// CS 211
// 

#pragma once

#include <string>
#include <vector>
#include <utility>
#include <set>
#include "busstop.h"
using namespace std;

//
// BusStops
//
// collection of all BusStops. initializer takes in the CSV file name and builds BusStop objects
//
class BusStops {
    private:
        string inputFile;
        set<BusStop> allBusStops;

    public:
        BusStops(string inputfile);

        //
        // printAll
        //
        // prints all bus stops
        //
        void printAll();

        //
        // getClosestStop
        //
        // returns the closest stop given a position
        //
        BusStop getClosestStop(pair<double, double> location, bool north);

        //
        // getNumStops
        //
        // returns num of stops
        //
        int getNumStops() const;
};