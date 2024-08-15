//
// Created by Brandon Friend on 7/25/24.
//


#ifndef PHANTOMPCH_H
#define PHANTOMPCH_H

#if defined(_WIN32)
    #include <windows.h>
#elif defined(__APPLE__)
    #include <mach-o/dyld.h>
#elif defined(__linux__)
    #include <unistd.h>
    #include <limits.h>
#endif


#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <functional>
#include <thread>
#include <mutex>
#include <sstream>
#include "imgui.h"
#include "rlImGui.h"
#include "raylib.h"
#include "raymath.h"
#include "rcamera.h"
#include "Math/PHMath.h"


#endif //PHANTOMPCH_H
