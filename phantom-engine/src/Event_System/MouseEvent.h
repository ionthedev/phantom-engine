//
// Created by Brandon Friend on 8/10/24.
//

#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include <sstream>

#include "Event.h"

namespace Phantom {

    class PHANTOM_API MouseMovedEvent : public Event {
    public:
        MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}

        inline float GetX() const { return m_MouseX; }
        inline float GetY() const { return m_MouseY; }

        std::string ToString() const override
        {
            std::stringstream stringStream;
            stringStream << "MouseMovedEvent: " << m_MouseX << " ," << m_MouseY;
            return stringStream.str();
        }

        EVENT_CLASS_TYPE(MouseMoved);
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    private:
        float m_MouseX, m_MouseY;

    };

    class PHANTOM_API MouseScrolledEvent : public Event {
    public:
        MouseScrolledEvent(float xOffset, float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}

        inline float GetX() const { return m_XOffset; }
        inline float GetY() const { return m_YOffset; }

        std::string ToString() const override
        {
            std::stringstream stringStream;
            stringStream << "MouseScrollEvent: " << m_XOffset << " ," << m_YOffset;
            return stringStream.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled);
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    private:
        float m_XOffset, m_YOffset;

    };

    class PHANTOM_API MouseButtonEvent : public Event {

    public:
        inline int GetMouseButton() const { return m_Button; }
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
    protected:
        MouseButtonEvent(int keycode) : m_Button(keycode) {}

        int m_Button;
    };

    class PHANTOM_API MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

        std::string ToString() const override
        {
            std::stringstream stringStream;
            stringStream << "MouseButtonPressedEvent: " << m_Button;
            return stringStream.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed);
    };

    class PHANTOM_API MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

        std::string ToString() const override
        {
            std::stringstream stringStream;
            stringStream << "MouseButtonReleasedEvent: " << m_Button;
            return stringStream.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased);
    };

} // Phantom

#endif //MOUSEEVENT_H
