#include <2geom/svg-path-parser.h>
#include <2geom/svg-path-writer.h>
#include <2geom/intersection-graph.h>

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

