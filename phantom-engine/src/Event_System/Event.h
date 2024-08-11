//
// Created by Brandon Friend on 8/10/24.
//

#ifndef EVENT_H
#define EVENT_H




#include "PhantomPch.h"
#include "Core/Core.h"

namespace Phantom {

    //Event Type Description
    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowUnfocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    //Trace for event types for Logging
    enum EventCategory
    {
        None = 0,
        EventCategoryApplication            = BIT(0),
        EventCategoryInput                  = BIT(1),
        EventCategoryKeyboard               = BIT(2),
        EventCategoryMouse                  = BIT(3),
        EventCategoryMouseButton            = BIT(4)
    };

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
virtual EventType GetEventType() const override { return GetStaticType(); }\
virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }



class PHANTOM_API Event {

    friend class EventDispatcher;
public:

    bool m_Handled = false;

    virtual EventType GetEventType() const = 0;
    virtual const char* GetName() const = 0;
    virtual int GetCategoryFlags() const = 0;
    virtual std::string ToString() const { return GetName(); } //WARN: ONLY FOR DEBUGGING

    inline bool IsInCategory(EventCategory category)
    {
        return GetCategoryFlags()& category;
    }

};

    class EventDispatcher
    {
    public:
        EventDispatcher(Event& event)
            : m_Event(event)
        {
        }

        // F will be deduced by the compiler
        template<typename T, typename F>
        bool Dispatch(const F& func)
        {
            if (m_Event.GetEventType() == T::GetStaticType())
            {
                m_Event.m_Handled |= func(static_cast<T&>(m_Event));
                return true;
            }
            return false;
        }
    private:
        Event& m_Event;
    };


    inline std::string format_as(const Event& e)
    {
        return e.ToString();
    }

} // Phantom

#endif //EVENT_H
