#include "logger.hpp"

Logger logger;

Logger::Logger()
{
    name = "LOG";
}

Logger::Logger(const std::string &name)
{
    this->name = name;
}
