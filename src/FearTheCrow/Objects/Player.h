//
// Created by Brandon Friend on 8/22/24.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"
#include "Core/GameObject.h"
#include "FearTheCrow/Globals.h"


#include "Core/Math.h"
#include "FearTheCrow/Components/CameraComponent.h"
#include "FearTheCrow/Components/TransformComponent.h"

class Player : public Phantom::GameObject {
public:

    void Start() override;
    void Update(double deltaTime) override;
    void FixedUpdate(double deltaTime) override;
    void Render() override;

    void MouseLook(double _deltaTime);
    void Accelerate(Vector3 wishDir, float wishSpeed, double deltaTime);
    Vector3 CalculateWishDir();
    void ApplyGravityAndFriction(double deltaTime);

private:
    Vector3 MoveDir;
    Vector3 WishDir;
    CameraComponent *cameraComponent = AddComponent<CameraComponent>();
    Phantom::TransformComponent *transformComponent = AddComponent<Phantom::TransformComponent>();


};



#endif //PLAYER_H
