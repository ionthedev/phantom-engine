//
// Created by Brandon Friend on 8/10/24.
//

#ifndef LAYERSTACK_H
#define LAYERSTACK_H

#include "Layer.h"
#include "PhantomPch.h"

#include <vector>

namespace Phantom {

class LayerStack {

public:
    LayerStack();
    ~LayerStack();

    void MakeLayer(Layer* layer);
    void MakeOverlay(Layer* overlay);
    void TakeLayer(Layer* layer);
    void TakeOverlay(Layer* overlay);

    std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
    std::vector<Layer*>::iterator end() { return m_Layers.end(); }

private:
    std::vector<Layer*> m_Layers;
    std::vector<Layer*>::iterator m_LayerInsert;

};

} // Phantom

#endif //LAYERSTACK_H
