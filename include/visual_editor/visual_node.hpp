#pragma once

#include <string>
#include <vector>

#include "core/math.hpp"

class VisualNodeSocket
{
public:
    enum Type
    {
        Input,
        Output
    };

    std::string data_type;
    Type type;
};

class VisualConnection
{
public:
    VisualNodeSocket *from;
    VisualNodeSocket *to;
};

class VisualNode
{
public:
    std::string title;
    Vec2 position;
    std::vector<VisualNodeSocket> sockets;
};