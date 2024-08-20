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
        PH_CORE_TRACE("Physics Scene Set");
        m_Scene = scene;
    }

    Scene* PhysicsEngine::GetScene()
    {
        return m_Scene;
    }

    void PhysicsEngine::PhysicsUpdate(double _deltaTime)
    {

    }

    void PhysicsEngine::SetGravity(Vector3 gravityDir)
    {
        Gravity = gravityDir;
    }

    Vector3 PhysicsEngine::GetGravity()
    {
        return Gravity;
    }

    void PhysicsEngine::RemovePhysicsObject(size_t object, PhysicsComponent* _object)
    {
        auto itr = PhysicsObjects.find(object);
        if (itr == PhysicsObjects.end())
            return;

        itr->second->OnDestoy();
        PhysicsObjects.erase(itr);
    }

    PhysicsComponent* PhysicsEngine::AddPhysicsObject(std::unique_ptr<PhysicsComponent> component)
    {
        size_t id = component->GetTypeId();
        if(GetPhysicsObject(id) == nullptr)
        {
            component->OnCreate();  // Call OnCreate after the component is added
            PhysicsObjects.insert_or_assign(id, std::move(component));
            return GetPhysicsObject(id);
        }
        return nullptr;
    }

    PhysicsComponent* PhysicsEngine::GetPhysicsObject(size_t objectID)
    {
        auto itr = PhysicsObjects.find(objectID);
        if (itr == PhysicsObjects.end())
            return nullptr;

        return itr->second.get();
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