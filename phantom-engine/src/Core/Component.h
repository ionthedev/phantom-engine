//
// Created by Brandon Friend on 8/14/24.
//

#ifndef COMPONENT_H
#define COMPONENT_H
namespace Phantom{

    class Component
    {
    public:
        virtual ~Component() = default;
        virtual void Update(double _deltaTime);
    };

    inline void Component::Update(double _deltaTime)
    {
    }


}
#endif //COMPONENT_H
