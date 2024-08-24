//
// Created by Brandon Friend on 8/22/24.
//

#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H
#include "raylib.h"
#include "Core/Component.h"

namespace Phantom {

class TransformComponent : public Component {

public:

    DEFINE_COMPONENT(TransformComponent)

    Vector3 GetPosition();
    void SetPosition(Vector3 _position);
    Vector3 GetScale();
    void SetScale(Vector3 _scale);
    Vector3 GetRotation();
    void SetRotation(Vector3 _rotation);

private:
    Vector3 Position { 10, 0, 0 };
    Quaternion Rotation = { 0 };
    Vector3 Scale { 0 };
};

} // Phantom

#endif //TRANSFORMCOMPONENT_H
