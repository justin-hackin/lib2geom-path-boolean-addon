#include <stdio.h>
#include <string>
#include <cstring>

#include "2geom/svg-path-parser.h"
#include "2geom/svg-path-writer.h"
#include "2geom/intersection-graph.h"

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

int main() {
  const char d1[] = "M0,0 L10,0 L10,10 L0,10 Z";
  const char d2[] = "M5,5 L15,5, L15,15 L5,15 Z";
  cout << intersectDValues(d1, d2);
  return 0;
}
