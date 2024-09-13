/* footways.cpp*/

//
// a collection of footways in an open street map
//
// Sally Liao
// Northwestern University
// CS 211
//

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

#include "footway.h"
#include "footways.h"
#include "node.h"
#include "nodes.h"
#include "osm.h"
#include "tinyxml2.h"

//
// sortFootways
//
// goes through each footway and sorts it
//
void Footways::sortFootways() {
    // for (Footway f : MapFootways) {
    //     f.sortNodeIDs();
    // }
    for (size_t i = 0; i < MapFootways.size(); i++) {
        MapFootways[i].sortNodeIDs();
    }
}

//
// getAndAddNodes
//
// gets and adds nodes to the footway
//
void getAndAddNodes(XMLElement* nd, Footway& F) {
    while (nd != nullptr) { //get all nodes + add
        const XMLAttribute* ndref = nd->FindAttribute("ref");
        assert(ndref != nullptr);
        long long id = ndref->Int64Value();
        F.add(id); // add node
        nd = nd->NextSiblingElement("nd");
    }
}

//
// readMapFootways
//
// given a XML doc, reads through the document and
// stores all the footways into the given vector
//
void Footways::readMapFootways(XMLDocument& xmldoc) {
    XMLElement* osm = xmldoc.FirstChildElement("osm");
    XMLElement* way = osm->FirstChildElement("way");

    while (way != nullptr) { //loop through all ways
        if (osmContainsKeyValue(way, "highway", "footway") || osmContainsKeyValue(way, "area:highway", "footway")) { // if is a footway
            // get id, name, and street addr and put into a building
            const XMLAttribute* attrId = way->FindAttribute("id");
            long long id = attrId->Int64Value();
            Footway F(id);
            XMLElement* nd = way->FirstChildElement("nd");
            getAndAddNodes(nd, F);
            MapFootways.push_back(F);
        }
        way = way->NextSiblingElement("way");
    }
}

//
// findNode
//
// given a nodeid, check if it is in any footway
//
void Footways::findNode(long long nodeid) {
    for (const Footway& f : MapFootways) {
        // loop through all nodes of footway and see if there is anything that matches
        long long result = f.findNode(nodeid);
        if (result != -1) {
            toPrint.push_back(result);
        }
    }
}

//
// print
//
// prints out all elements in toPrint
//
void Footways::print() {
    sort(toPrint.begin(), toPrint.end());
    removeDuplicates();

    cout << "Footways that intersect: " << toPrint.size() << endl;

    if (toPrint.size() == 0) {
        cout << " None" << endl;
        return;
    }
    
    for (long long ele : toPrint) {
        cout << " Footway " << ele << endl;
    }
}

//
// clearPrint
//
// clears toPrint
//
void Footways::clearPrint() {
    toPrint.clear();
}


//
// getNumMapFootways
//
// returns num of map footways
// 
int Footways::getNumMapFootways() const {
    return MapFootways.size();
}

// 
// removeDuplicates
//
// removes duplicate ids from toPrint. assumes alr sorted
// 
void Footways::removeDuplicates() {
    if (toPrint.size() == 0) {
        return;
    }
    vector<long long> result;

    long long prev = toPrint[0];
    result.push_back(prev);
    for (size_t i = 1; i < toPrint.size(); i++) {
        if (toPrint[i] != prev) {
            result.push_back(toPrint[i]);
            prev = toPrint[i];
        }
    }
    toPrint = result;
}