#include <napi.h>
#include <2geom/svg-path-parser.h>
#include <2geom/svg-path-writer.h>
#include <2geom/intersection-graph.h>
#include <iostream>

using namespace Geom;
using namespace std;

PathIntersectionGraph getIntersectionGraph(char const *pathA, char const *pathB) {
  return graph(parse_svg_path(pathA), parse_svg_path(pathB));
}

string intersectDValues(char const *pathA, char const *pathB) {
  return Geom::write_svg_path(getIntersectionGraph(pathA, pathB).getIntersection());
}


string subtractDValues(char const *pathA, char const *pathB) {
    return Geom::write_svg_path(getIntersectionGraph(pathA, pathB).getAminusB());

}

Napi::String IntersectPaths(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() < 2) {
    Napi::TypeError::New(env, "Wrong number of arguments")
        .ThrowAsJavaScriptException();
    // though suggested in example, the following line leads to compiler errors
    // return env.Null();
  }

  if (!info[0].IsString() || !info[1].IsString()) {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    // return env.Null();
  }

  string arg0 = info[0].As<Napi::String>().Utf8Value();
  string arg1 = info[1].As<Napi::String>().Utf8Value();
  Napi::String intersection = Napi::String::New(env, intersectDValues(arg0.c_str(), arg1.c_str()));

  return intersection;
}


Napi::String SubtractPaths(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() < 2) {
    Napi::TypeError::New(env, "Wrong number of arguments")
        .ThrowAsJavaScriptException();
    // though suggested in example, the following line leads to compiler errors
    // return env.Null();
  }

  if (!info[0].IsString() || !info[1].IsString()) {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    // return env.Null();
  }

  string arg0 = info[0].As<Napi::String>().Utf8Value();
  string arg1 = info[1].As<Napi::String>().Utf8Value();
  Napi::String subtraction = Napi::String::New(env, subtractDValues(arg0.c_str(), arg1.c_str()));

  return subtraction;
}


Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "intersectPathData"), Napi::Function::New(env, IntersectPaths));
  exports.Set(Napi::String::New(env, "subtractPathData"), Napi::Function::New(env, SubtractPaths));
  return exports;
}

NODE_API_MODULE(addon, Init)
