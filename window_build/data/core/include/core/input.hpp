#pragma once

#include <cstdint>

#include "event_system.hpp"
#include "math.hpp"
#include "key_code.hpp"
#include "dll.hpp"

class AMUSE_API Input
{
public:
    Input(EventSystem &es);

    inline bool is_key_down(KeyCode key_code) const { return keys_down[(uint16_t)key_code]; }
    inline bool is_key_up(KeyCode key_code) const { return keys_up[(uint16_t)key_code]; }
    inline bool is_key_pressed(KeyCode key_code) const { return keys_pressed[(uint16_t)key_code]; }
    inline bool is_mouse_button_down(MouseButton button) const { return mouse_buttons_down[(uint8_t)button]; }
    inline bool is_mouse_button_up(MouseButton button) const { return mouse_buttons_up[(uint8_t)button]; }
    inline bool is_mouse_button_pressed(MouseButton button) const { return mouse_buttons_pressed[(uint8_t)button]; }
    inline const Vec2 &get_mouse_position() const { return mouse_position; }
    inline const Vec2 &get_mouse_delta() const { return mouse_delta; }

private:
    bool keys_down[512] = {false};
    bool keys_up[512] = {false};
    bool keys_pressed[512] = {false};
    bool mouse_buttons_down[5] = {false};
    bool mouse_buttons_up[5] = {false};
    bool mouse_buttons_pressed[5] = {false};
    Vec2 mouse_position = {0, 0};
    Vec2 mouse_delta = {0, 0};
};
