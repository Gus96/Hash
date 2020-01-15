#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <ctime>
#include <random>
#include <string>
#include <fstream>
#include <map>
#include <unordered_map>
#include <time.h> 
#include <chrono>
#include <cmath>


using namespace std::chrono;
using namespace std;


unsigned m;
std::random_device rd;
std::mt19937 gen(rd());


std::string random_string();