# lib2geom path boolean N-API addon

lib2geom boolean path algorithm wasm port

### Build dependencies in emscripten
```
git clone https://github.com/ampl/gsl.git && cd gsl
# emscripten has issues building  gsl submodule AMPL bindings (arith.h placed as sibling of include folder instead of inside it)
emcmake cmake . -DNO_AMPL_BINDINGS=ON && make
cd ..
git clone https://github.com/google/double-conversion.git 
cd double-conversion
emcmake cmake . && make
cd ..

# from https://github.com/emscripten-core/emscripten/issues/11066#issuecomment-624636388
sudo apt install autoconf libtool m4 automake
pip3 install meson
export PATH=~/.local/bin/:$PATH

# VET THIS CODE then follow instructions here
# https://gist.github.com/kleisauke/acfa1c09522705efa5eb0541d2d00887#file-readme-md

git clone https://gitlab.com/inkscape/lib2geom.git
cd cd lib2geom
emcmake cmake . \
    -DDoubleConversion_INCLUDE_DIR:PATH=${LIBS_DIR}/double-conversion/ \
    -DDoubleConversion_LIBRARY:FILEPATH=${LIBS_DIR}/double-conversion/libdouble-conversion.a \
    -DGLIB_INCLUDE_DIR:PATH=${LIBS_DIR}/glib-emscripten/target/include \
    -DGLIB_LIBRARY:FILEPATH=${LIBS_DIR}/glib-emscripten/target/lib/libglib-2.0.a \
    -DGSL_INCLUDE_DIR:PATH=${LIBS_DIR}/gsl \
    -DGSL_LIBRARY:FILEPATH=${LIBS_DIR}/gsl/libgsl.a \
    -DGSL_CBLAS_LIBRARY:FILEPATH=${LIBS_DIR}/gsl/libgslcblas.a \
    -D2GEOM_TESTING=OFF \
    -DCMAKE_CXX_FLAGS="-sUSE_BOOST_HEADERS=1" \
    -DCMAKE_C_FLAGS="-sUSE_BOOST_HEADERS=1" \
&& make
cd ..
```

## API

These are the same algorithms that power [Inkscape path boolean features](https://www.youtube.com/watch?v=RpWBhu7T13k)

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
