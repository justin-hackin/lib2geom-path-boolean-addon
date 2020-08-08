#include <napi.h>
#include <2geom/svg-path-parser.h>
#include <2geom/svg-path-writer.h>
#include <2geom/intersection-graph.h>
#include <iostream>

using namespace Geom;
using namespace std;

string intersectDValues(char const *pathA, char const *pathB) {
  PathVector pathAParsed = parse_svg_path(pathA);
  PathVector pathBParsed = parse_svg_path(pathB);
  PathIntersectionGraph graph(pathAParsed, pathBParsed);
  return Geom::write_svg_path(graph.getIntersection());
}


string subtractDValues(char const *pathA, char const *pathB) {
  PathVector pathAParsed = parse_svg_path(pathA);
  PathVector pathBParsed = parse_svg_path(pathB);
  PathIntersectionGraph graph(pathAParsed, pathBParsed);
  return Geom::write_svg_path(graph.getAminusB());
}


Napi::String IntersectPath(const Napi::CallbackInfo& info) {
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
  exports.Set(Napi::String::New(env, "intersectPathData"), Napi::Function::New(env, IntersectPath));
  exports.Set(Napi::String::New(env, "subtractPathData"), Napi::Function::New(env, SubtractPaths));
  return exports;
}

NODE_API_MODULE(addon, Init)
