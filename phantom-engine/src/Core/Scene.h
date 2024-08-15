//
// Created by Brandon Friend on 8/14/24.
//

#ifndef SCENE_H
#define SCENE_H
#include <entt/entt.hpp>



namespace Phantom {

    class Object;

    class Scene {
    public:
        Scene();
        ~Scene();

        virtual void Start();
        virtual void Update(double deltaTime) = 0;
        Object CreateObject();

        entt::registry m_Registry;


    };

} // Phantom

#endif //SCENE_H
