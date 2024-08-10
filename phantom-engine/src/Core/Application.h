//
// Created by Brandon Friend on 8/8/24.
//

#ifndef APPLICATION_H
#define APPLICATION_H
#include "Layer.h"
#include "LayerStack.h"
#include "Event_System/Event.h"
#include "PhantomPch.h"



int main(int argc, char** argv);

namespace Phantom
{

class Application {

public:
    Application();
    virtual ~Application();

    virtual void Run();
    void MakeLayer(Layer* layer);
    void MakeOverlay(Layer* layer);
private:

    LayerStack m_LayerStack;

};

    Application* CreateApplication();

}
#endif //APPLICATION_H
