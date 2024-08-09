//
// Created by Brandon Friend on 7/25/24.
//


#ifndef PHANTOMENGINE_H
#define PHANTOMENGINE_H

#include <cstring>
#include <string>
#include "imgui.h"
#include "rlImGui.h"
#include "raylib.h"
#include "raymath.h"
#include "rcamera.h"
#include "Math/PHMath.h"
#include "Core/Application.h"
#include "Core/Core.h"


namespace Phantom
{
    class PhantomEngine
    {
        void test();
    };

    inline void PhantomEngine::test()
    {
        PHMath::m_Clip(1.0f, 2.0f, 3.0f);
    }
}

#endif //PHANTOMENGINE_H
