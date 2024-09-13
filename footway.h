/*footway.h*/
//
// A footway in the Open Street Map
// 
// Sally Liao
// Northwestern University
// CS 211
// 

#pragma once

//
// Footway:
//
// A footway is a walkway for pedestrians
// it holds an ID and a vector of NodeIDs
//

#include <vector>
#include "node.h"
#include "nodes.h"
#include "tinyxml2.h"

class Footway {
private:
    long long ID;
    vector<long long> NodeIDs;
public:
    //
    // constructor
    //
    Footway(long long ID);

    //
    // adds the given nodeid to the end of the vector.
    //
    void add(long long nodeid);
    
    //
    // sortNodeIDs
    //
    // sorts the Node IDs
    //
    void sortNodeIDs();

    //
    // findNode
    //
    // given a nodeid, looks for the nodeid in this footway
    // 
    long long findNode(long long nodeid) const;
};