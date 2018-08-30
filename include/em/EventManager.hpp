#ifndef _EVENT_MANAGER
#define _EVENT_MANAGER
#include <iostream>
#include <functional>
#include <map>

namespace em
{
template <class Event, typename... EventCallbackType>
class EventManager
{
  public:
    typedef std::function<void(EventCallbackType...)> EventCallback;

  private:
    std::map<Event, EventCallback> events;

  public:
    EventManager()
    {
    }

    void addEventHandler(Event event, EventCallback callback)
    {
        events[event] = callback;
    }

    template <class T>
    void addEventHandler(Event event, T *const object, void (T::*callback)(EventCallbackType...))
    {
        using namespace std::placeholders;
        events[event] = std::bind(callback, object, _1);
    }

    void fireEvent(Event event, EventCallbackType... t)
    {
        if (events[event] == nullptr)
            return;
        EventCallback callback = events[event];
        callback(t...);
    }
};
}
#endif
