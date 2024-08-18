//
// Created by Brandon Friend on 8/17/24.
//

#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H
#include "raylib.h"
#include "Core/Game/Component.h"

namespace FTC
{
    class ModelComponent : public Phantom::Component
    {
    public:
        DEFINE_COMPONENT(ModelComponent)

        void SetModel(const char* path);
        Model GetModel();


        void OnRender() override;

    private:
        Model m_Model;
    };


}

#endif //MESHCOMPONENT_H
