#include <SDL2/SDL.h>

#include "logger.hpp"
#include "core/window.hpp"
#include "imgui/backends/imgui_impl_sdl2.h"

Window::Window(const std::string &title, int width, int height)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        logger.panic("SDL could not initialize! SDL_Error: {}", SDL_GetError());
        return;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetSwapInterval(1);

    sdl_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    gl_context = SDL_GL_CreateContext((SDL_Window *)sdl_window);

    if (sdl_window == nullptr)
    {
        logger.panic("Window could not be created! SDL_Error: {}", SDL_GetError());
        return;
    }
    id = SDL_GetWindowID((SDL_Window *)sdl_window);
}

Window::~Window()
{
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow((SDL_Window *)sdl_window);
    SDL_Quit();
}

void Window::poll_events(EventSystem &es)
{
    static SDL_Event event;

    while (SDL_PollEvent(&event) != 0)
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT)
        {
            es.emit<WindowClose>();
            is_open = false;
        }
        else if (event.type == SDL_WINDOWEVENT && event.window.windowID == id)
        {
            switch (event.window.event)
            {
            case SDL_WINDOWEVENT_RESIZED:
                es.emit<WindowResize>({
                    .width = event.window.data1,
                    .height = event.window.data2,
                });
                break;
            }
        }
        else if (event.type == SDL_KEYDOWN)
        {
            es.emit<KeyDown>({
                .key_code = (KeyCode)event.key.keysym.scancode,
            });
        }
        else if (event.type == SDL_KEYUP)
        {
            es.emit<KeyUp>({
                .key_code = (KeyCode)event.key.keysym.scancode,
            });
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            es.emit<MouseButtonDown>({
                .button = (MouseButton)event.button.button,
            });
        }
        else if (event.type == SDL_MOUSEBUTTONUP)
        {
            es.emit<MouseButtonUp>({
                .button = (MouseButton)event.button.button,
            });
        }
        else if (event.type == SDL_MOUSEMOTION)
        {
            es.emit<MouseMove>({
                .x = event.motion.x,
                .y = event.motion.y,
                .dx = event.motion.xrel,
                .dy = event.motion.yrel,
            });
        }
        else if (event.type == SDL_MOUSEWHEEL)
        {
            es.emit<MouseScroll>({
                .x = event.wheel.x,
                .y = event.wheel.y,
            });
        }
    }
}

void Window::swap_buffers()
{
    SDL_GL_SwapWindow((SDL_Window *)sdl_window);
}

void Window::set_title(const std::string &title)
{
    SDL_SetWindowTitle((SDL_Window *)sdl_window, title.c_str());
}

void Window::set_vsync(VSync vsync)
{
    SDL_GL_SetSwapInterval((int)vsync);
}

void Window::set_resizable(bool resizable)
{
    SDL_SetWindowResizable((SDL_Window *)sdl_window, resizable ? SDL_TRUE : SDL_FALSE);
}

void Window::maximize()
{
    SDL_MaximizeWindow((SDL_Window *)sdl_window);
}

Vec2i Window::get_size()
{
    int w, h;
    SDL_GetWindowSize((SDL_Window *)sdl_window, &w, &h);
    return {w, h};
}
