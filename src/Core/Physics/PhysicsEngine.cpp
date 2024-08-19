//
// Created by Brandon Friend on 8/18/24.
//

#include "PhysicsEngine.h"

#include "Core/Log.h"
#include "Core/Game/Components/PhysicsComponent.h"

namespace Phantom {


    PhysicsEngine* PhysicsEngine::s_Instance = nullptr;

    PhysicsEngine* PhysicsEngine::GetSingleton(bool initialized)
    {
        if (s_Instance == nullptr)
        {

            PH_CORE_ERROR("Physics Engine not initialized. Creating Singleton");
            s_Instance = new PhysicsEngine(initialized);
        }
        return s_Instance;
    }

    PhysicsEngine::PhysicsEngine(const PhysicsEngine&)
    {
    }

    void PhysicsEngine::Init()
    {
    }

    void PhysicsEngine::SetScene(Scene* scene)
    {
        PH_CORE_TRACE("Applicaiton Set");
        m_Scene = scene;
    }

    Scene* PhysicsEngine::GetScene()
    {
        return m_Scene;
    }

    void PhysicsEngine::PhysicsUpdate(double _deltaTime)
    {
        /*for(Object* object : m_Scene->GetChildren())
        {
            object->GetComponent<PhysicsComponent>()->OnUpdate();
        }*/
    }

    PhysicsEngine::PhysicsEngine(bool _initialized)
    {
        PH_CORE_INFO("Physics Engine Initialized");
        initialized = _initialized;

        Init();
    }

    PhysicsEngine::~PhysicsEngine()
    {
    }


} // Phantom