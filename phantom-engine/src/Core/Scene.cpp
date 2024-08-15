#include "Scene.h"
#include "Component.h"
#include "Object.h"
#include "Components/Transform2D.h"
#include "Components/Transform3D.h"

namespace Phantom {
    Scene::Scene()
    {
    }

    Scene::~Scene()
    {
    }

    void Scene::Start()
    {
    }

    void Scene::Update(double deltaTime)
    {
    }

    Object Scene::CreateObject()
    {
        Object object = { m_Registry.create(), this};
        object.AddComponent<Transform3D>();
        return object;
    }
} // Phantom
