#include <SDL2/SDL.h>
#include <iostream>

#include "core.hpp"
#include "editor/editor.hpp"

int main(int argc, char **argv)
{
    Editor *editor = new Editor();
    editor->run();

    return 0;
}