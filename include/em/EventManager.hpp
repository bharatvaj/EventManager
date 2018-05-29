#ifndef _EVENT_MANAGER
#define _EVENT_MANAGER
#include <iostream>
#include <functional>
#include <map>
namespace em
{
template <class Event, class EventCallbackType>
class EventManager
{
    typedef std::function<void(EventCallbackType *)> EventCallback;

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

    void fireEvent(Event event, EventCallbackType *t)
    {
        if (events[event] == nullptr)
            return;
        EventCallback callback = events[event];
        callback(t);
    }
};
}
#endif