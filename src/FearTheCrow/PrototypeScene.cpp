//
// Created by Brandon Friend on 8/17/24.
//

#include "PrototypeScene.h"
#pragma region imgui
#include "imgui.h"
#include "rlImGui.h"
#include "imguiThemes.h"
#pragma endregion
#include <cmath>

#include "Components/ModelComponent.h"
#include "Components/TransformComponent.h"

namespace FearTheCrow {
} // FearTheCrow
FTC::PrototypeScene::PrototypeScene()
{
}

FTC::PrototypeScene::~PrototypeScene()
{
}

void FTC::PrototypeScene::Start()
{

    Scene::Start();

    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
    test_mesh = AddObject();
    test_mesh->AddComponent<TransformComponent>();
    test_mesh->AddComponent<ModelComponent>()->SetModel("../resources/Suzanne.gltf");


}

void FTC::PrototypeScene::Update()
{
    Scene::Update();
    Vector3 size = test_mesh->GetComponent<TransformComponent>()->GetScale();





    test_mesh->GetComponent<TransformComponent>()->SetScale(size);
}

void FTC::PrototypeScene::FixedUpdate()
{
    Scene::FixedUpdate();
}

void FTC::PrototypeScene::Render()
{
    Scene::Render();
    DrawGrid(10, 1.0f);
    ClearBackground(RAYWHITE);
    test_mesh->Render();
}
