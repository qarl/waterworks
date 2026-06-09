#include "ww.h"


void wwProto::doIt(const wwMapColor &input, wwMapColor &output)
{

  // class i edit to do testing on new effects

  output = input;

  WW_MAP_LOOP(i,j)
    output.colors[i][j][1] = 255;
}
