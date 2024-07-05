#pragma once

#include "types.hpp"

#define Event(T) \
    struct T;

Event(Tick {
    float delta_time;
    float life_time;
});

using EventHandler = Function<void(void *)>;

class EventSystem
{
public:
    // Function to register an event into the event system
    // the event system will call the handler when the event is emitted
    // the handler will be called with the engine state and the event
    // the event can be nullptr if the event is emitted without data
    // example:
    // ```c++
    // es.regist<Start>([&](const EngineState &s, void *_) {
    //     std::cout << "Start" << std::endl;
    // });
    // ```
    template <typename T>
    void regist(EventHandler handler)
    {
        event_handlers[TypeID<T>::value()].push_back(handler);
    }

    // Function to emit an event
    // The event will be passed to all the handlers registered for this event
    // Example:
    // ```c++
    //  es.emit<Start>();
    // ```
    // or with data
    // ```c++
    //  es.emit(Update { delta_time = 1 });
    // ```
    template <typename T>
    void emit(T event)
    {
        for (auto &handler : event_handlers[TypeID<T>::value()])
        {
            handler((void *)&event);
        }
    }

    // Function to emit an event
    // The event will be passed to all the handlers registered for this event
    // Example:
    // ```c++
    //  es.emit<Start>();
    // ```
    // or with data
    // ```c++
    //  es.emit(Update { delta_time = 1 });
    // ```
    template <typename T>
    void emit()
    {
        for (auto &handler : event_handlers[TypeID<T>::value()])
        {
            handler(nullptr);
        }
    }

private:
    std::unordered_map<size_t, std::vector<EventHandler>> event_handlers;
};
