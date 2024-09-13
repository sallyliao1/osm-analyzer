/*BusStop.cpp*/

//
// A BusStop from bus-stops.txt
// 
// Sally Liao
// Northwestern University
// CS 211
// 

#include <iostream>
#include <vector>
#include <string>
#include "busstop.h"
#include "curl_util.h"
#include "json.hpp"
#include "dist.h"
#include <stdexcept>

using namespace std;
using json = nlohmann::json;

BusStop::BusStop(long long stopid, int busroute, string stopname, string diroftravel, string stoplocation, pair<double, double> position)
    : StopID(stopid), BusRoute(busroute), StopName(stopname), DirOfTravel(diroftravel), StopLocation(stoplocation), Position(position) {}

// gets stopID
long long BusStop::getStopID() const {
    return StopID;
}

// gets lat
double BusStop::getLat() const {
    return Position.first;
}

// gets lon
double BusStop::getLon() const {
    return Position.second;
}

// gets dir of travel
string BusStop::getDirOfTravel() const {
    return DirOfTravel;
}

// gets stop name
string BusStop::getStopName() const {
    return StopName;
}
// gets bus route
int BusStop::getBusRoute() const {
    return BusRoute;
}
// gets stop location
string BusStop::getStopLocation() const {
    return StopLocation;
}

//
// <
//
bool BusStop::operator<(const BusStop& a) const {
    return StopID < a.StopID;
}

//
// print
//
// prints out info on the busstop
//
void BusStop::print() const {
    cout << StopID << ": bus " << BusRoute << ", " << StopName << ", " << DirOfTravel << ", " << StopLocation << ", location (" << Position.first << ", " << Position.second << ")" << endl;
}

//
// printPredict
//
// prints out the prediction for the closest bus to arrive at the busstop
//
void BusStop::printPredict(CURL* curl) const {
    string url = "https://ctabustracker.com/bustime/api/v2/getpredictions?key=AziyxTzRUz9zzDdNdntDVNWeh&rt=" + to_string(BusRoute) + "&stpid=" + to_string(StopID) + "&format=json";
    cout << "  " << endl;

    string response;
    bool success = callWebServer(curl, url, response);
    if (!success) {
        cout << "  <<bus predictions unavailable, call failed>>" << endl;
        return;
    }
    auto jsondata = json::parse(response);
    auto bus_response = jsondata["bustime-response"];
    auto predictions = bus_response["prd"];

    // for each prediction in list
    int numRuns = 0;
    for(auto& M : predictions) {
        try {
            numRuns++;
            cout << "  vehicle #" << stoi(M["vid"].get_ref<std::string&>()) << " on route " << stoi(M["rt"].get_ref<std::string&>()) << " travelling " << M["rtdir"].get_ref<std::string&>()<< " to arrive in " << stoi(M["prdctdn"].get_ref<std::string&>())<< " mins" << endl;
        }
        catch (exception& e) {
            cout << "  error" << endl;
            cout << "  malformed CTA response, prediction unavailable"
                 << " (error: " << e.what() << ")" << endl;
        }
    }
    if (numRuns == 0) {
        cout << "  <<no predictions available>>" << endl;
    }
}