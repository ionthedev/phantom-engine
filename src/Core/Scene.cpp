//
// Created by Brandon Friend on 8/17/24.
//

#include "Scene.h"

namespace Phantom {
    Scene::Scene()
    {
    }

    Scene::~Scene()
    {
    }

    void Scene::Start()
    {
        GameObject::Start();
    }

    void Scene::Update(double deltaTime)
    {
        GameObject::Update(deltaTime);
    }

    void Scene::FixedUpdate(double deltaTime)
    {
        GameObject::FixedUpdate(deltaTime);
    }

    void Scene::Render()
    {
        GameObject::Render();
    }
} // Phantom