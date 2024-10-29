#include "colors.h"
#include <vector>
const Color darkGrey = {26, 31, 40, 255};
const Color cyan = {21, 204, 209, 255};
const Color orange = {226, 116, 17, 255};
const Color purple = {166, 0, 247, 255};
const Color yellow = {237, 234, 4, 255};
const Color blue = {0, 0, 255, 255};
const Color green = {0, 255, 0, 255};
const Color red = {255, 0, 0, 255};
const Color darkBlue = {44, 44, 127, 255};
const Color lightBlue = {173, 216, 230, 255};

vector<Color> getCellColors()
{
    return {darkGrey, cyan, orange, purple, yellow, blue, green, red};
}