//
// Created by Brandon Friend on 8/21/24.
//

#include "DemoScene.h"

#include "Core/Game/Components.h"

#include <flecs.h>
#include "flecs/addons/cpp/world.hpp"

#include <iostream>
#include <ostream>

DemoScene::DemoScene()
{
}

void DemoScene::Start()
{
    Scene::Start();
    flecs::world world;


    auto e = world.entity("Bob");

    e.add<Velocity>();
}

void DemoScene::Update(double deltaTime)
{
    Scene::Update(deltaTime);
}

void DemoScene::FixedUpdate(double deltaTime)
{
    Scene::FixedUpdate(deltaTime);
}

void DemoScene::Render()
{
    Scene::Render();
}