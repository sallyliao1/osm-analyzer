/*footways.h*/
//
// A collection of footways in the Open Street Map
// 
// Sally Liao
// Northwestern University
// CS 211
// 

#pragma once
#include <vector>
#include <string>
#include "node.h"
#include "nodes.h"
#include "footway.h"
#include "tinyxml2.h"
using namespace std;
using namespace tinyxml2;

//
// Footways:
//
// keeps track of all footways
//
class Footways {
private:
    vector<long long> toPrint;
public: 
    vector<Footway> MapFootways;

    //
    // readMapFootways
    //
    // given a XML doc, reads through the document and
    // stores all the footways into the given vector
    //
    void readMapFootways(XMLDocument& xmldoc);

    //
    // sortFootways
    //
    // goes through each footway and sorts it
    //
    void sortFootways();

    //
    // findNodes
    //
    // given a nodeid, check if it is in any footway
    //
    void findNode(long long nodeid);

    //
    // clearPrint
    //
    // clears toPrint
    //
    void clearPrint();
    
    //
    // print
    //
    // prints out all elements in toPrint
    //
    void print();

    //
    // accessors/getters
    //
    int getNumMapFootways() const;

    // 
    // removeDuplicates
    //
    // removes duplicate ids from toPrint
    // 
    void removeDuplicates();
};