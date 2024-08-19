//
// Created by Brandon Friend on 8/17/24.
//

#ifndef COMPONENT_H
#define COMPONENT_H
#include <memory>

namespace Phantom
{
    // macro to define common code that all components need
    // computes a runtime unique ID for each component using the name
    // NOTE that this ID is not deterministic, a real system would hash the name and use a better ID
    #define DEFINE_COMPONENT(T) \
    static const char* GetComponentName() { return #T;}  \
    static size_t GetComponentId() { return reinterpret_cast<size_t>(#T); } \
    inline size_t GetTypeId() const override { return GetComponentId(); } \
    T(Phantom::Object& object) : Component(object) {}

    class Object;
    class Component {
    private:
        Object& HostingObject;

    protected:
        Object& GetObject() { return HostingObject; }
        const Object& GetObject() const { return HostingObject; }

    public:
        virtual size_t GetTypeId() const = 0;

        Component(Object& object)
            : HostingObject(object)
        {
            Component::OnCreate();
        }
        virtual ~Component() = default;

        // no copy
        Component(const Component&) = delete;
        Component& operator=(Component const&) = delete;

        Component* GetComponent(size_t componentID);

        template<class T>
        T* GetComponent()
        {
            return static_cast<T*>(GetComponent(T::GetComponentId()));
        }

        virtual void OnCreate() {};
        virtual void OnDestoy() {};
        virtual void OnUpdate() {};
        virtual void OnRender() {};


    };
}



#endif //COMPONENT_H
