//
// Created by Brandon Friend on 8/14/24.
//

#ifndef TRANSFORM3D_H
#define TRANSFORM3D_H
#include "Core/Component.h"

namespace Phantom {

class Transform3D : public Component {
public:
    Transform3D();
    Transform3D(const Vector3 postition, const Vector3 scale, const Vector3 rotation) : Position(postition), Scale(scale), Rotation(rotation){}
    ~Transform3D();
    Vector3 Position;
    Vector3 Scale;
    Vector3 Rotation;
    void Update(double _deltaTime) override;
};

} // Phantom

#endif //TRANSFORM3D_H
