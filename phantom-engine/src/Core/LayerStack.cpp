//
// Created by Brandon Friend on 8/10/24.
//

#include "LayerStack.h"

#include <algorithm>



namespace Phantom {

    LayerStack::LayerStack()
    {
        m_LayerInsert = m_Layers.begin();
    }

    LayerStack::~LayerStack()
    {
        for(Layer* layer : m_Layers)
            delete layer;
    }

    void LayerStack::MakeLayer(Layer* layer)
    {
        m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
    }
    void LayerStack::MakeOverlay(Layer* overlay)
    {

        m_Layers.emplace_back(overlay);
    }

    void LayerStack::TakeLayer(Layer *layer)
    {
        auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
        if(it != m_Layers.end())
        {
            m_Layers.erase(it);
            m_LayerInsert--;
        }
    }

    void LayerStack::TakeOverlay(Layer *overlay)
    {
        auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
        if(it != m_Layers.end())
            m_Layers.erase(it);
    }


} // Phantom