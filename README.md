
_ABANDONED: this project is abandoned in favor of [paper.js](https://github.com/paperjs/paper.js) boolean operations. This does necessitates some bloat of canvas-related rendering code as per [this issue](https://github.com/paperjs/paper.js/issues/1325)._

# lib2geom path boolean N-API addon

Exposes lib2geom boolean path algorithms used in the Inkscape project to a node.js project

_WARNING: this library is experimental and not recommended for production use. It is proving difficult to build on Windows.
Explored wasm compilation in the wasm branch without success yet._

## Installation

### As N-API module (recommended)

`npm i lib2geom-path-boolean-addon@n-api`

### With post-install build via cmake-js

`npm i -g cmake-js`

##### Debian-based, e.g. Ubuntu
`sudo apt-get install g++ cmake libdouble-conversion-dev libgsl-dev libcairo2-dev`

##### Windows (not recommended, see See [lib2geom issue](https://gitlab.com/inkscape/lib2geom/-/issues/37))
* https://osdn.net/projects/mingw/downloads/68260/mingw-get-setup.exe/ (use to install base and g++)
* https://sourceforge.net/projects/boost/files/boost/1.55.0/boost_1_55_0.zip/download
* https://nodejs.org/en/download/
* https://github.com/wingtk/gvsbuild (dependency: extras installed with nodejs)
* https://sourceforge.net/projects/gnu-scientific-library-windows/

`npm i lib2geom-path-boolean-addon`

## API

### intersectPathData
Given 2 strings which are svg <path> d-attributes, returns the d-attribute for the intersection of the two paths

### subtractPathData
Given 2 strings which are svg <path> d-attributes, returns the d-attribute for the difference of the two paths

### unifyPathData
Given 2 strings which are svg <path> d-attributes, returns the d-attribute for the union of the two paths

## Usage

```js
const { intersectPathData, subtractPathData, unifyPathData } = require('lib2geom-path-boolean-addon');

const intersection = intersectPathData('M0,0 L10,0 L10,10 L0,10 Z', 'M5,5 L15,5, L15,15 L5,15 Z');
const subtraction = subtractPathData('M0,0 L10,0 L10,10 L0,10 Z', 'M5,5 L15,5, L15,15 L5,15 Z');
const union = unifyPathData('M0,0 L10,0 L10,10 L0,10 Z', 'M5,5 L15,5, L15,15 L5,15 Z');
```
