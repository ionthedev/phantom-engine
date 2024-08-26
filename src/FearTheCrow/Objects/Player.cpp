//
// Created by Brandon Friend on 8/22/24.
//

#include "Player.h"

#include <rcamera.h>


void Player::Start()
{
    GameObject::Start();
    transformComponent->SetPosition({0,0,-10.f});
    cameraComponent->SetTarget({0,0,0});
}

void Player::Update(double deltaTime)
{
    GameObject::Update(deltaTime);
}

void Player::FixedUpdate(double deltaTime)
{
    GameObject::FixedUpdate(deltaTime);
    WishDir = CalculateWishDir();

    Accelerate(WishDir, 5.0f, deltaTime);
    ApplyGravityAndFriction(deltaTime);
    MouseLook(deltaTime);
    transformComponent->SetPosition(Vector3Add(transformComponent->GetPosition(), Vector3Scale(MoveDir, static_cast<float>(deltaTime))));



}

void Player::Render()
{
    GameObject::Render();
}

void Player::MouseLook(double _deltaTime)
{
    const auto fDeltaTime = static_cast<float>(_deltaTime);
    Vector3 camRotVel = {0};
    camRotVel.y += -GetMouseDelta().x * LOOK_SENSITIVITY * 0.01f;
    camRotVel.x += GetMouseDelta().y * LOOK_SENSITIVITY * 0.01f;

    Vector3 camRot = cameraComponent->GetRotation();

    camRot.x = Clamp(camRot.x + camRotVel.x * fDeltaTime, -PI * 0.5 * 0.95, PI * 0.5 * 0.95);

    camRot.z = Lerp(camRot.z, 0.0, Clamp(fDeltaTime * 7.5f, 0.0, 1.0));
    camRot.z -= MoveDir.x * fDeltaTime * 0.75f;
    camRot.z = Clamp(camRot.z, 0.3f, 0.5f);



    cameraComponent->SetRotation({camRot.x, camRot.y + camRotVel.y * fDeltaTime, camRot.z});
    cameraComponent->SetPosition(Vector3Add(transformComponent->GetPosition(), Vector3Scale(cameraComponent->GetUp(), 3)));
    cameraComponent->SetTarget(Vector3Add(cameraComponent->GetPosition(), Phantom::MatrixMultiplyVector3(Phantom::MatrixFromYawPitchRoll(camRot.y, camRot.x, camRot.z), {0,0,1})));


}

void Player::Accelerate(Vector3 wishDir, float wishSpeed, double deltaTime)
{
    float accel = 10.0f; // Quake's air acceleration value
    float currentSpeed = Vector3DotProduct(MoveDir, wishDir);
    float addSpeed = wishSpeed - currentSpeed;
    if (addSpeed <= 0) return;

    float accelSpeed = accel * deltaTime * wishSpeed;
    if (accelSpeed > addSpeed)
        accelSpeed = addSpeed;

    MoveDir = Vector3Add(MoveDir, Vector3Scale(wishDir, accelSpeed));
}

Vector3 Player::CalculateWishDir()
{

    // Normalize the direction to ensure the input direction is unit length
    WishDir = Vector3Normalize({GetInputDir().x, 0, GetInputDir().y});

    // Transform the wishDir to be relative to the camera's rotation
    WishDir = Vector3Transform(WishDir, Phantom::MatrixFromYawPitchRoll(cameraComponent->GetRotation().y, cameraComponent->GetRotation().x, 0.0f));

    // Since we don't want to affect the y (vertical) direction with player input (standard for FPS games),
    // we can flatten the direction vector by zeroing out the y component.
    WishDir.y = 0.0f;

    // Normalize again after flattening to ensure correct length
    WishDir = Vector3Normalize(WishDir);

    return WishDir;
}

void Player::ApplyGravityAndFriction(double deltaTime)
{
    // Apply gravity
    //MoveDir.y -= 9.8f * deltaTime;

    // Apply friction
    float friction = 6.0f; // Quake's friction value
    float speed = Vector3Length(MoveDir);
    if (speed != 0) {
        float drop = speed * friction * deltaTime;
        MoveDir = Vector3Scale(MoveDir, fmaxf(speed - drop, 0) / speed);
    }
}

Vector2 Player::GetInputDir()
{
    Vector2 dir = {0};

    if(IsKeyDown(KEY_W))
        dir.y += 1.0f;
    if(IsKeyDown(KEY_A))
        dir.x += 1.0f;
    if(IsKeyDown(KEY_S))
        dir.y -= 1.0f;
    if(IsKeyDown(KEY_D))
        dir.x -= 1.0f;

    return dir;
}