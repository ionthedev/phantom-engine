//
// Created by Brandon Friend on 8/10/24.
//

#ifndef KEYEVENT_H
#define KEYEVENT_H
#include <sstream>

#include "Event.h"

namespace Phantom {

class PHANTOM_API KeyEvent : public Event {

public:
    inline int GetKeyCode() const { return m_KeyCode; }
    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);
protected:
    KeyEvent(int keycode) : m_KeyCode(keycode) {}

    int m_KeyCode;
};

    class PHANTOM_API KeyPressedEvent : public KeyEvent
    {
        KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount) {}

        inline int GetRepeatCount() const { return m_RepeatCount; }

        std::string ToString() const override
        {
            std::stringstream stringStream;
            stringStream << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
            return stringStream.str();
        }

        EVENT_CLASS_TYPE(KeyPressed);
    private:
        int m_RepeatCount;
    };

    class PHANTOM_API KeyReleasedEvent : public KeyEvent
    {
        KeyPressedEvent(int keycode) : KeyEvent(keycode) {}

        std::string ToString() const override
        {
            std::stringstream stringStream;
            stringStream << "KeyPressedEvent: " << m_KeyCode;
            return stringStream.str();
        }

        EVENT_CLASS_TYPE(KeyReleased);
    };

} // Phantom

#endif //KEYEVENT_H
