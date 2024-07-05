#include "core/event_system.hpp"
#include "core/input.hpp"
#include "core/key_code.hpp"
#include "core/window.hpp"

Input::Input(EventSystem &es)
{
    es.regist<KeyDown>(
        [&](void *payload)
        {
            this->keys_down[(uint16_t)(reinterpret_cast<KeyDown *>(payload))->key_code] = true;
            this->keys_pressed[(uint16_t)(reinterpret_cast<KeyDown *>(payload))->key_code] = true;
        });

    es.regist<KeyUp>(
        [&](void *payload)
        {
            this->keys_up[(uint16_t)(reinterpret_cast<KeyUp *>(payload))->key_code] = true;
            this->keys_pressed[(uint16_t)(reinterpret_cast<KeyUp *>(payload))->key_code] = false;
        });

    es.regist<MouseButtonDown>(
        [&](void *payload)
        {
            this->mouse_buttons_down[(uint8_t)(reinterpret_cast<MouseButtonDown *>(payload))->button] = true;
            this->mouse_buttons_pressed[(uint8_t)(reinterpret_cast<MouseButtonDown *>(payload))->button] = true;
        });

    es.regist<MouseButtonUp>(
        [&](void *payload)
        {
            this->mouse_buttons_up[(uint8_t)(reinterpret_cast<MouseButtonUp *>(payload))->button] = true;
            this->mouse_buttons_pressed[(uint8_t)(reinterpret_cast<MouseButtonUp *>(payload))->button] = false;
        });

    es.regist<MouseMove>(
        [&](void *payload)
        {
            auto *event = reinterpret_cast<MouseMove *>(payload);
            this->mouse_position = {(float)event->x, (float)event->y};
            this->mouse_delta = {(float)event->dx, (float)event->dy};
        });

    es.regist<MouseScroll>(
        [&](void *payload)
        {
            auto *event = reinterpret_cast<MouseScroll *>(payload);
            this->mouse_delta = {(float)event->x, (float)event->y};
        });

    es.regist<Tick>(
        [&](void *payload)
        {
            std::fill(std::begin(this->keys_down), std::end(this->keys_down), false);
            std::fill(std::begin(this->keys_up), std::end(this->keys_up), false);
            std::fill(std::begin(this->mouse_buttons_down), std::end(this->mouse_buttons_down), false);
            std::fill(std::begin(this->mouse_buttons_up), std::end(this->mouse_buttons_up), false);
            this->mouse_delta = {0, 0};
        });
}
