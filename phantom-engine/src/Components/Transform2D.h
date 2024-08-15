//
// Created by Brandon Friend on 8/14/24.
//

#ifndef TRANSFORM2D_H
#define TRANSFORM2D_H
#include "Core/Component.h"

namespace Phantom {

class Transform2D : public Component {
public:
    Transform2D();
    Transform2D(const Vector2 postition, const Vector2 scale) : Position(postition), Scale(scale){}
    ~Transform2D();
    Vector2 Position;
    Vector2 Scale;

    void Update(double _deltaTime) override;

};

} // Phantom

#endif //TRANSFORM2D_H
