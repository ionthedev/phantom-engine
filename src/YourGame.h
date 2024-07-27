//
// Created by Brandon Friend on 7/27/24.
//

#ifndef YOURGAME_H
#define YOURGAME_H


#include "PE_Core.h"

class PE_Core;


class YourGame {

public:
    YourGame();

    ~YourGame()
    {
    }

    virtual void Start() const;
    virtual void Update(double _deltaTime) const;
    virtual void FixedUpdate(double _deltaTime) const;
    virtual void Render() const;
    virtual void HandleInput() const;

    const int screenWidth = 800;
    const int screenHeight = 450;




};


#endif //YOURGAME_H
