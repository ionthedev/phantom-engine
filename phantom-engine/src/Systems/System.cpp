//
// Created by Brandon Friend on 8/14/24.
//

#include "System.h"

#include <Core/Log.h>

namespace Phantom {


    System* System::s_Instance = nullptr;

    System * System::GetSingleton(bool initialized)
    {
        if(s_Instance == nullptr)
        {
            s_Instance = new System(initialized);
        }
        return s_Instance;
    }

    void System::Init() const
    {
    }

    void System::Update() const
    {
    }

    void System::FixedUpdate() const
    {
    }

    System::System(bool _initialized)
    {
        initialized = _initialized;

        System::Init();
    }

} // Phantom