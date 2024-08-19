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

#include "rlgl.h"
#include "Core/Log.h"
#include "Core/Game/Components/ModelComponent.h"
#include "Core/Game/Components/TransformComponent.h"

#include "Core/Physics/Collision.h"

namespace FearTheCrow {
} // FearTheCrow
FTC::PrototypeScene::PrototypeScene()
{
}

FTC::PrototypeScene::~PrototypeScene()
{
    UnloadCollider(&test_meshCol);
    UnloadCollider(&floorMeshCol);
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
    test_mesh->AddComponent<Phantom::ModelComponent>();
    test_mesh->GetComponent<Phantom::ModelComponent>()->SetModel("../resources/Suzanne.gltf");
    test_mesh->GetComponent<Phantom::TransformComponent>()->SetPosition({0, 20, 0});
    floorMesh = AddObject();
    floorMesh->AddComponent<Phantom::ModelComponent>();
    floorMesh->GetComponent<Phantom::ModelComponent>()->SetModel("../resources/floor.gltf");

    // Fetch the meshes from both objects
    const Mesh& meshA = test_mesh->GetComponent<Phantom::ModelComponent>()->GetModel().meshes[0];
    SetupColliderMesh(&test_meshCol, meshA);

    const Mesh& meshB = floorMesh->GetComponent<Phantom::ModelComponent>()->GetModel().meshes[0];
    SetupColliderMesh(&floorMeshCol, meshB);
}

void FTC::PrototypeScene::Update()
{

    Vector3 normal = {0}; //Init the normal value
    collision = CheckCollision(test_meshCol, floorMeshCol, &normal);
    // Update the position of the moving mesh
    Vector3 pos = test_mesh->GetComponent<Phantom::TransformComponent>()->GetPosition();
    if(!collision) pos.y -= 0.1f;  // Move downward
    test_mesh->GetComponent<Phantom::TransformComponent>()->SetPosition(pos);

    UpdateCollider(test_mesh->GetComponent<Phantom::TransformComponent>()->GetPosition(), &test_meshCol);
    UpdateCollider(floorMesh->GetComponent<Phantom::TransformComponent>()->GetPosition(), &floorMeshCol);


    // Check for collision between the meshes


    // Call the base class update method
    Scene::Update();

    // Update components for rendering
    test_mesh->Update();
    floorMesh->Update();
}


void FTC::PrototypeScene::FixedUpdate()
{
    Scene::FixedUpdate();
}

void FTC::PrototypeScene::Render()
{
    Scene::Render();
    DrawGrid(10, 1.0f);
    ClearBackground(DARKGRAY);
    if (collision) {
        DrawText("Collision Detected!", 10, 10, 20, RED);
    } else {
        DrawText("No Collision", 10, 10, 20, GREEN);
    }
    test_mesh->Render();
    floorMesh->Render();
}



