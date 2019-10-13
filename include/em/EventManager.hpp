#ifndef _EVENT_MANAGER
#define _EVENT_MANAGER
#include <iostream>
#include <functional>
#include <map>

namespace em
{
enum class event {
  EVERY
};

template <class Event, typename... EventCallbackType>
class EventManager
{
  public:
    using EventCallback = std::function<void(EventCallbackType...)>;

  private:
    std::map<Event, EventCallback> events;
    std::map<Event, void *> customEvents;
    EventCallback everyCallback = nullptr;

  public:
    EventManager()
    {
    }

    EventManager &on(Event event, EventCallback callback)
    {
        events[event] = callback;
        return *this;
    }

    template <class CustomEventCallback>
    EventManager &on(Event event, CustomEventCallback callback)
    {
        customEvents[event] = (void *)callback;
        return *this;
    }

    template <class T>
    EventManager &on(Event event, T *const object, void (T::*callback)(EventCallbackType...))
    {
        using namespace std::placeholders;
        events[event] = std::bind(callback, object, _1);
        return *this;
    }

    template <class T, class... CustomEventCallbackType>
    EventManager&on (Event event, T *const object, void (T::*callback)(CustomEventCallbackType...))
    {
        using namespace std::placeholders;
        customEvents[event] = std::bind(callback, object, _1);
        return *this;
    }

    template <class T>
    EventManager &on(em::event, T *const object, void (T::*callback)(EventCallbackType...))
    {
        using namespace std::placeholders;
        everyCallback = std::bind(callback, object, _1);
        return *this;
    }

    EventManager &on(em::event, EventCallback callback){
      using namespace std::placeholders;
      everyCallback = callback;
      return *this;
    }

    void fireEvent(Event event, EventCallbackType... t)
    {
        if(everyCallback != nullptr){
            everyCallback(t...);
        }
        if (events[event] != nullptr){
            events[event](t...);
        }
    }

    template <class... CustomEventCallbackType>
    void fireEvent(Event event, CustomEventCallbackType... t)
    {
        using CustomEventCallback = std::function<void(CustomEventCallbackType...)>;
        // if(everyCallback != nullptr){
        //     everyCallback(t...);
        // }
        if (customEvents[event] != nullptr){
            CustomEventCallback *cb = (CustomEventCallback*)customEvents[event];
            (*cb)(t...);
        }
    }

    void fireEvent(em::event event, EventCallbackType... t){
      if(everyCallback == nullptr)
        return;
      everyCallback(t...);
    }
};
}
#endif
