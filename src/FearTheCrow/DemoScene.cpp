//
// Created by Brandon Friend on 8/21/24.
//

#include "DemoScene.h"

#include "Objects/Player.h"


#include <iostream>
#include <ostream>

DemoScene::DemoScene()
{
}

void DemoScene::Start()
{
    player = new Player();
    camera = player->GetComponent<CameraComponent>()->GetCamera();
}

void DemoScene::Update(double deltaTime)
{
    Scene::Update(deltaTime);
    player->Update(deltaTime);
}

void DemoScene::FixedUpdate(double deltaTime)
{
    Scene::FixedUpdate(deltaTime);
    player->FixedUpdate(deltaTime);
}

void DemoScene::Render()
{
    BeginMode3D(player->GetComponent<CameraComponent>()->GetCamera());
    Scene::Render();
    ClearBackground(RAYWHITE);
    player->Render();

    DrawCube({0,0,0}, 2.0f, 2.0f, 2.0f, RED);
    DrawCubeWires({0,0,0}, 2.0f, 2.0f, 2.0f, MAROON);
    DrawGrid(10, 1.0f);
    EndMode3D();
}