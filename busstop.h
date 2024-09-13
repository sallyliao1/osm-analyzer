/*busstop.h*/

//
// A BusStop from bus-stops.txt
// 
// Sally Liao
// Northwestern University
// CS 211
// 

#pragma once

#include <string>
#include <vector>
#include <utility>
#include "curl_util.h"
using namespace std;

//
// BusStop
//
// Defines a BusStop with a stop ID, bus route, stop name, direction of travel,
// location of the stop, position (lat, lon)
//

class BusStop {
    private:
        long long StopID;
        int BusRoute;
        string StopName;
        string DirOfTravel;
        string StopLocation;
        pair<double, double> Position;

    public: 
        BusStop(long long stopid, int busroute, string stopname, string diroftravel, string stoplocation, pair<double, double> position);
        // accessors:
        // gets stop id
        long long getStopID() const;
        // gets lat
        double getLat() const;
        // gets lon
        double getLon() const;
        // gets dir of travel
        string getDirOfTravel() const;
        // gets stop name
        string getStopName() const;
        // gets bus route
        int getBusRoute() const;
        // gets stop location
        string getStopLocation() const;
        
        //
        // <
        //
        bool operator<(const BusStop& a) const;

        //
        // print
        //
        // prints out info of busstop
        //
        void print() const;

        //
        // printPredict
        //
        // prints out the prediction for the closest bus to arrive at the busstop
        //
        void printPredict(CURL* curl) const;
};