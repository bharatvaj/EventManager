#ifndef _EVENT_MANAGER
#define _EVENT_MANAGER
#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include <typeinfo>

namespace em
{
enum class event {
  EVERY
};

template <class Event>
class EventManager
{
  public:

  private:
    std::map<Event, std::vector<std::pair<std::size_t, void*>>> events;
    std::vector<void*> everyCallback;

  public:
    EventManager()
    {
    }

    // template <class... T>
    // EventManager &on(Event event, std::function<void(T...)> callback)
    // {
    //     using CustomEventCallback = std::function<void(T...)>;
    //     events[event].push_back(std::make_pair(typeid(callback).hash_code(), (void*)new CustomEventCallback(callback)));
    //     return *this;
    // }

    template <class... T>
    EventManager &on(Event event, void(*callback)(T...)){
        events[event].push_back(std::make_pair(typeid(callback).hash_code(), (void*)callback));
        return *this;
    }

    template <class P, class... T>
    EventManager&on (Event event, P *object, void (P::*callback)(T...))
    {
        using namespace std::placeholders;
        events[event].push_back(std::make_pair(typeid(callback).hash_code(), (void*)new std::function<void(T...)>(std::bind(callback, object, _1)) ));
        return *this;
    }

    template <class... T>
    void fireEvent(Event event, T... t)
    {
        // if(everyCallback != nullptr){
        //     everyCallback(t...);
        // }
        for(std::pair<std::size_t, void*> eventCb : events[event]){
          if (eventCb.second != nullptr 
          && eventCb.first == typeid(void(*)(T...)).hash_code()){
              (*(void(*)(T...))eventCb.second)(t...);
          }
        }
    }

    // template <class... CustomEventCallbackType>
    // void fireEvent(em::event event, CustomEventCallbackType... t){
    //   // if(everyCallback == nullptr)
    //   //   return;
    //   // everyCallback(t...);
    //   // for()
    // }
};
}
#endif
