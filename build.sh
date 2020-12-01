#!/bin/sh

emcc -L ../lib2geom/build/src/2geom -I ../lib2geom/include -s LLD_REPORT_UNDEFINED boolean.cc
