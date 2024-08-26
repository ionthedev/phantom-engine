//
// Created by Brandon Friend on 8/22/24.
//

#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H
#include "raylib.h"
#include "raymath.h"
#include "Core/Component.h"


class CameraComponent : public Phantom::Component{
public:
    DEFINE_COMPONENT(CameraComponent)

    void SetPosition(Vector3 _position);
    Vector3 GetPosition();
    void SetTarget(Vector3 _target);
    Vector3 GetTarget();
    void SetRotation(Vector3 _rotation);
    Vector3 GetRotation();
    void SetUp(Vector3 _up);
    Vector3 GetUp();
    void SetProjection(CameraProjection _cameraProjection);
    CameraProjection GetCameraProjection();
    void SetFOV(float _fov);
    float GetFOV();
    void SetForward(Vector3 _forward);
    Vector3 GetForward();

    void SetLookAtMatrix(Matrix matrix);
    Matrix GetLookAtMatrix();

    void SetRotationalVelocity(Vector3 _velocity);
    Vector3 GetRotationalVelocity();

    void SetCamera(Camera _camera);
    Camera GetCamera();
    Camera *GetCameraRef();

    //Phantom::GameObject GetLookat(); TODO: Implement Another Time

    void OnCreate() override;
    void OnDestoy() override;
    void OnUpdate(double deltaTime) override;
    void OnFixedUpdate(double deltaTime) override;
    void OnRender() override;

private:
    Vector3 Position= { 0.0f, 10.0f, 10.0f };
    Vector3 Target = {0,0,0};
    Vector3 Up = { 0.0f, 1.0f, 0.0f };
    CameraProjection Projection = CAMERA_PERSPECTIVE;
    float FOV = 45.0f;
    Vector3 Rotation;
    Vector3 Forward = { 0, 0, 1};
    Matrix LookRotMatrix = {0};
    Vector3 RotationalVelocity = { 0 };
    Camera ViewCamera;


};



#endif //CAMERACOMPONENT_H
