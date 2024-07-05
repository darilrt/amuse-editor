#pragma once

#include "core/event_system.hpp"
#include "core/key_code.hpp"
#include "core/math.hpp"
#include "dll.hpp"

Event(WindowResize {
    int width;
    int height;
});
Event(WindowClose);

Event(KeyDown {
    KeyCode key_code;
});
Event(KeyUp {
    KeyCode key_code;
});

// Mouse events
Event(MouseMove {
    int x;
    int y;
    int dx;
    int dy;
});
Event(MouseButtonDown {
    MouseButton button;
});
Event(MouseButtonUp {
    MouseButton button;
});
Event(MouseScroll {
    int x;
    int y;
});

enum class VSync : int
{
    Off = 0,
    On = 1,
};

struct Window
{
    uint32_t id;
    void *sdl_window;
    void *gl_context;
    bool is_open = true;

    AMUSE_API Window(const std::string &title, int width, int height);

    AMUSE_API ~Window();

    AMUSE_API void poll_events(EventSystem &es);

    AMUSE_API void swap_buffers();

    AMUSE_API void set_title(const std::string &title);

    inline void quit() { is_open = false; }

    AMUSE_API void set_vsync(VSync vsync);

    AMUSE_API void set_resizable(bool resizable);

    AMUSE_API void maximize();

    AMUSE_API Vec2i get_size();
};