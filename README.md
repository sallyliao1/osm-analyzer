# OpenStreetMap (OSM) analyzer
This is a C++ program which allows users to easily search a OSM file for a desired building and find the building’s closest northbound and southbound CTA bus stops, address, ID, geographic coordinates. It uses an API key to extract when the next northbound and southbound bus is going to arrive at the closest bus stops.

This project was created in the Winter '24 section of a CS class.

## How to use
In the terminal, run the following lines: 
```
make build
./a.out
```
Then, follow the instructions outputted to the terminal. To use test file that come with the program, use file <b>nu.osm</b> when prompted to enter file name. One larger test file (ns.osm) was omitted from GitHub to avoid using GitHub LFS.

## How to read code
Almost each unique file name corresponds to a new class, which includes a .h file detailing the class & its functions and a .cpp file with its implementation.
