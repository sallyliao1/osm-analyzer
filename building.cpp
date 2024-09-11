/*building.cpp*/

//
// A building in the Open Street Map.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211
// 

#include "building.h"
#include "nodes.h"
#include "nodes.h"
#include "footway.h"
#include "footways.h"
#include "busstop.h"
#include "busstops.h"
#include "dist.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <stddef.h>
#include <limits>
#include <utility>
#include "tinyxml2.h"
#include <cmath>

using namespace std;


//
// constructor
//
Building::Building(long long id, string name, string streetAddr)
  : ID(id), Name(name), StreetAddress(streetAddr)
{ 
  //
  // the proper technique is to use member initialization list above,
  // in the same order as the data members are declared:
  //
  //this->ID = id;
  //this->Name = name;
  //this->StreetAddress = streetAddr;

  // vector is default initialized by its constructor
}

//
// adds the given nodeid to the end of the vector.
//
void Building::add(long long nodeid)
{
  this->NodeIDs.push_back(nodeid);
}


//
// print
//
// prints all of the info of a building
//
void Building::print(const Nodes& nodes, Footways& footways, BusStops& busstops, CURL* curl) {
  double lat;
  double lon;

  pair<double, double> location = getLocation(nodes);
  cout << Name << endl;
  cout << "Address: " << StreetAddress << endl;
  cout << "Building ID: " << ID << endl;
  cout << "# perimeter nodes: " << numPerimNodes << endl;
  cout << "Location: (" << location.first << ", " << location.second << ")" << endl;
  
  BusStop closestSouth = busstops.getClosestStop(location, false);
  cout << "Closest southbound bus stop: " << endl;
  double dist = distBetween2Points(closestSouth.getLat(), closestSouth.getLon(), location.first, location.second);
  cout << "  " << closestSouth.getStopID() << ": " << closestSouth.getStopName() << ", bus #" << closestSouth.getBusRoute() << ", " << closestSouth.getStopLocation() << ", " << dist << " miles";
  closestSouth.printPredict(curl);

  BusStop closestNorth = busstops.getClosestStop(location, true);
  cout << "Closest northbound bus stop: " << endl;
  dist = distBetween2Points(closestNorth.getLat(), closestNorth.getLon(), location.first, location.second);
  cout << "  " << closestNorth.getStopID() << ": " << closestNorth.getStopName() << ", bus #" << closestNorth.getBusRoute() << ", " << closestNorth.getStopLocation() << ", " << dist << " miles";
  closestNorth.printPredict(curl);
}

// 
// getLocation
//
// gets the center (lat, lon) of the building based
// on the nodes that form the perimeter
//
pair<double,double> Building::getLocation(const Nodes& nodes) {
  double sumLat = 0.0;
  double sumLon = 0.0;
  numPerimNodes = 0;
  
  for (const long long& nodeid: NodeIDs) {
    double lat;
    double lon;
    bool isEntrance;
    if (nodes.find(nodeid, lat, lon, isEntrance)) {
      sumLat += lat;
      sumLon += lon;
      numPerimNodes++;
    }
  }
  double avgLat = sumLat/numPerimNodes;
  double avgLon = sumLon/numPerimNodes;
  return make_pair(avgLat, avgLon);
}