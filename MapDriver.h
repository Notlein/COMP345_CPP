#pragma once
#include "Map.h"
#include <string>
#include <vector>
using namespace std;

vector<vector<string> > LoadMaps(int);
vector<vector<string> > parseMap(ifstream &file);