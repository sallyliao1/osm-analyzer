/*footway.cpp*/

//
// A footway in the Open Street Map.
// 
// Sally Liao
// Northwestern University
// CS 211
// 

#include "footway.h"
#include "nodes.h"
#include "nodes.h"
#include <iostream>
#include <algorithm>

using namespace std;

//
// constructor
//
Footway::Footway(long long id)
  : ID(id)
{}

//
// add
//
// adds the given nodeid to the end of the vector.
//
void Footway::add(long long nodeid) {
  this->NodeIDs.push_back(nodeid);
}

//
// sortNodeIDs
//
// sorts the Node IDs
//
void Footway::sortNodeIDs() {
  sort(NodeIDs.begin(), NodeIDs.end());
}

//
// findNode
//
// given a nodeid, looks for the nodeid in this footway
// returns the id of the footway if found. else returns -1
// 
long long Footway::findNode(long long nodeid) const {
  if (binary_search(NodeIDs.begin(), NodeIDs.end(), nodeid)) {
    return ID;
  }
  return -1;
}