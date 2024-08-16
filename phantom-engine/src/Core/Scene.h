//
// Created by Brandon Friend on 8/14/24.
//

#ifndef SCENE_H
#define SCENE_H


#include "PhantomPch.h"
#include <entt/entt.hpp>



namespace Phantom {

    class Object;

    class Scene {
    public:
        Scene();
        virtual ~Scene();

        virtual void Start();
        virtual void Update(double deltaTime) = 0;
        Object CreateObject();
        std::string GetValue(const std::string &json, const std::string &key);
        std::vector<float> ParseFloatArray(const std::string &arrayStr);
        std::vector<unsigned short> ParseUShortArray(const std::string &arrayStr);
        Model LoadPMD(const std::string &filename);

        entt::registry m_Registry;


    };

} // Phantom

#endif //SCENE_H
