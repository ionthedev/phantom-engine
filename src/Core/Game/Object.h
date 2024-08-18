//
// Created by Brandon Friend on 8/17/24.
//

#ifndef OBJECT_H
#define OBJECT_H

#include "Component.h"
#include <unordered_map>
#include <memory>
#include <string>
#include <vector>

#include "Component.h"

namespace Phantom {

    class Object {
    private:
        Object* Parent = nullptr;
        std::vector<Object*> Children;

        std::string Name;

    protected:
        std::unordered_map<size_t, std::unique_ptr<Component>> Components;

    public:
        ~Object();

        void Update();
        void Render();

        Component* AddComponent(std::unique_ptr<Component> component);
        void RemoveComponent(size_t componentID);
        Component* GetComponent(size_t componentID);


        template<class T>
        T* AddComponent()
        {
            return static_cast<T*>(AddComponent(std::make_unique<T>(*this)));
        }

        template<class T>
        void RemoveComponent()
        {
            RemoveComponent(T::GetComponentId());
        }

        template<class T>
        T* GetComponent()
        {
            return static_cast<T*>(GetComponent(T::GetComponentId()));
        }

        const std::vector<Object*>& GetChildren() const { return Children; }
        Object* GetParent() const { return Parent; }

        Object* AddChild();

        std::string_view GetName() const;
        void SetName(std::string_view name);
    };

} // Phantom

#endif //OBJECT_H
