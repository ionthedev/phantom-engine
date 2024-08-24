//
// Created by Brandon Friend on 8/22/24.
//

#include "Player.h"


void Player::Start()
{
    GameObject::Start();
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
    GetComponent<Phantom::TransformComponent>()->SetPosition(Vector3Add(GetComponent<Phantom::TransformComponent>()->GetPosition(), Vector3Scale(MoveDir, deltaTime)));



}

void Player::Render()
{
    GameObject::Render();
}

void Player::MouseLook(double _deltaTime)
{
    const auto fDeltaTime = static_cast<float>(_deltaTime);


    cameraComponent->SetRotationalVelocity({0,0,0});
    Vector3 cameraRotation = cameraComponent->GetRotation();
    Vector3 cameraRotationVelocity = cameraComponent->GetRotationalVelocity();
    cameraRotationVelocity.y += -GetMouseDelta().x * LOOK_SENSITIVITY * 0.001f;
    cameraRotationVelocity.x += GetMouseDelta().y * LOOK_SENSITIVITY * 0.001f;
    //GetComponent<Phantom::TransformComponent>()->SetRotation(Vector3Scale(GetComponent<Phantom::TransformComponent>()->GetRotation(), cameraRotationVelocity.y ));

    cameraRotation.x = Clamp(cameraRotation.x + cameraRotationVelocity.x * fDeltaTime, -PI * 0.5 * 0.95, PI * 0.5 * 0.95);
    cameraRotation.y += cameraRotationVelocity.y * fDeltaTime;
    /*cameraRotation.z = Lerp(cameraRotation.z, 0.0, Clamp(fDeltaTime * 7.5f, 0.0, 1.0));
    cameraRotation.z -= WishDir.x * fDeltaTime * 0.75f;
    cameraRotation.z = Clamp(cameraRotation.z, -PI * 0.3f, PI * 0.5f);*/

    Matrix lookRotMat = Phantom::MatrixFromYawPitchRoll(cameraRotation.y, cameraRotation.x, cameraRotation.z);
    // THIS IS A TEST HERE, IF IT DOESN'T WORK, JUST USE CUSTOM MATH FUNCTIONS
    cameraComponent->SetForward(Phantom::MatrixMultiplyVector3(lookRotMat, {0,0,1}));

    cameraComponent->SetPosition(Vector3Add(GetComponent<Phantom::TransformComponent>()->GetPosition(), Vector3Scale(cameraComponent->GetUp(), 3)));
    cameraComponent->SetTarget(Vector3Add(cameraComponent->GetPosition(), cameraComponent->GetForward()));

    cameraComponent->SetUp(Vector3Normalize(Phantom::QuaternionMultiplyVector3(Phantom::QuaternionAngleAxis(cameraRotation.z * 1.3f, cameraComponent->GetForward()), Vector3{0, 1.0, 0})));
        cameraRotationVelocity = {0,0,0};


    cameraComponent->SetRotationalVelocity(cameraRotationVelocity);
    cameraComponent->SetRotation(cameraRotation);

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

    if (IsKeyDown(KEY_W)) WishDir.z += 1.0f;
    if (IsKeyDown(KEY_S)) WishDir.z -= 1.0f;
    if (IsKeyDown(KEY_A)) WishDir.x += 1.0f;
    if (IsKeyDown(KEY_D)) WishDir.x -= 1.0f;

    // Normalize the direction to ensure the input direction is unit length
    WishDir = Vector3Normalize(WishDir);

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