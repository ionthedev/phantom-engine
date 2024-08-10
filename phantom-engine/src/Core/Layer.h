//
// Created by Brandon Friend on 8/10/24.
//

#include "PhantomPch.h"

#ifndef LAYER_H
#define LAYER_H
#include "Core/Core.h"

namespace Phantom {



class PHANTOM_API Layer {
public:
    Layer(const std::string& name = "Layer");
    virtual ~Layer();
    virtual void OnStart() {}
    virtual void OnEnd() {}
    virtual void OnUpdate() {}

    [[nodiscard]] inline const std::string& GetName() const { return m_DebugName; }

private:
    std::string m_DebugName;

};

} // Phantom

#endif //LAYER_H
