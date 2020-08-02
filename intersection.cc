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

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "intersectPath"), Napi::Function::New(env, IntersectPath));
  return exports;
}

NODE_API_MODULE(addon, Init)


// int main () {
//   char const *path1 = "M 111.33207,94.178358 87.385827,83.282535 100.52613,106.07451 81.118891,88.31217 86.572954,114.0492 73.604437,91.159046 70.838379,117.32182 65.578034,91.544493 54.862615,115.57201 57.825362,89.43078 40.209482,108.97106 51.105305,85.024812 28.31333,98.165116 46.075671,78.757875 20.338637,84.211939 43.228794,71.243422 17.066021,68.477364 42.843347,63.217019 18.815831,52.5016 44.95706,55.464346 25.416781,37.848467 49.363028,48.74429 36.222725,25.952314 55.629965,43.714655 50.175901,17.977621 63.144418,40.867779 65.910476,14.705006 71.170821,40.482332 81.88624,16.454815 78.923494,42.596045 96.539374,23.055765 85.643551,47.002013 108.43553,33.861709 90.673185,53.26895 116.41022,47.814886 93.520062,60.783403 119.68283,63.549461 93.905509,68.809806 117.93302,79.525225 91.791795,76.562479 Z";
//   char const *path2 = "M 103.78017,123.75099 80.865156,131.92813 57.166918,126.41838 40.209484,108.97106 35.37672,85.125551 44.202994,62.452646 63.886026,48.150828 88.176594,46.760823 109.36261,58.72395 l 11.35506,21.518048 -2.08105,24.241142 z";
//   cout << intersectDValues(path1, path2);
// }
