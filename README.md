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

## Usage

```js
const { intersectPathData, subtractPathData } = require('lib2geom-path-boolean-addon');

const intersection = intersectPathData('M0,0 L10,0 L10,10 L0,10 Z', 'M5,5 L15,5, L15,15 L5,15 Z');

const subtraction = intersectPathData('M0,0 L10,0 L10,10 L0,10 Z', 'M5,5 L15,5, L15,15 L5,15 Z');
```