//
// Created by Brandon Friend on 8/14/24.
//

#ifndef OBJECT_H
#define OBJECT_H
#include "Core.h"
#include "Scene.h"
#include "entt/entt.hpp"

namespace Phantom {

class Object {
public:
    Object(entt::entity, Scene* scene);
    Object(const Object& other) = default;

    template<typename T, typename... Args>
    T& AddComponent(Args&&... args)
    {
        PH_CORE_ASSERT(!HasComponent<T>(), "Entity does not have this component!");
        T& component = m_Scene->m_Registry.emplace<T>(m_entityHandle, std::forward<Args>(args)...);
        return component;
    }
    template<typename T, typename... Args>
    T& AddOrReplaceComponent(Args&&... args)
    {
        T& component = m_Scene->m_Registry.emplace_or_replace<T>(m_entityHandle, std::forward<Args>(args)...);
        return component;
    }
    template<typename T>
    T& GetComponent()
    {
        PH_CORE_ASSERT(HasComponent<T>(), "Entity does not have this component!");
        return m_Scene->m_Registry.get<T>(m_entityHandle);
    }
    template<typename T>
    bool HasComponent()
    {
        return m_Scene->m_Registry.all_of<T>(m_entityHandle);
    }
    template<typename T>
    void RemoveComponent()
    {
        PH_CORE_ASSERT(HasComponent<T>(), "Entity does not have this component!");
        m_Scene->m_Registry.remove<T>(m_entityHandle);
    }


private:
    entt::entity m_entityHandle;
    Scene* m_Scene;

};

} // Phantom

#endif //OBJECT_H
