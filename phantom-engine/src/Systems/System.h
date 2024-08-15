//
// Created by Brandon Friend on 8/14/24.
//

#ifndef SYSTEM_H
#define SYSTEM_H
#include <iostream>
namespace Phantom {

class System {
public:
    // Static method to access the singleton instance
    static System* GetSingleton(bool initialized = false);

    // Delete copy constructor and assignment operator to prevent copies
    System(const System&);
    System& operator=(const System&) = delete;

    virtual void Init() const;
    virtual void Update() const;
    virtual void FixedUpdate() const;

protected:
    System(bool _initialized); // Protected constructor
    ~System() = default; // Protected destructor

private:
    bool initialized;
    static System* s_Instance; // Static instance pointer

};

} // Phantom

#endif //SYSTEM_H
