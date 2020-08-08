# lib2geom path boolean N-API addon

Exposes lib2geom boolean path algorithms used in the Inkscape project to a node.js project

## Installation

Install system dependencies (debian-based)
`sudo apt-get install g++ cmake libdouble-conversion-dev libgsl-dev libcairo2-dev`

Install cmake-js
`npm i -g cmake-js`

## API

### intersectPathData
Given 2 strings which are svg <path> d-attributes, returns the d-attribute for the intersection of the two paths

### subtractPathData
Given 2 strings which are svg <path> d-attributes, returns the d-attribute for the difference of the two paths
