//
// Description: Logger class for logging
//
// Usage:
// Logger logger("AMUSE");
// logger.info("Hello, World!");
// logger.warn("Hello, World!");
// logger.error("Hello, World!");
// logger.panic("Hello, World!");
//
// Output:
// [AMUSE][INFO] Hello, World!
// [AMUSE][WARN] Hello, World!
// [AMUSE][ERROR] Hello, World!
// [AMUSE][PANIC] Hello, World!
//
// Note: This is a simple logger class for logging
//
// If LOGGER_NO_INFO is defined, the info method will not be compiled
// #define LOGGER_NO_INFO
//

#pragma once

#include <string>
#include <iostream>
#include <format>

#include "dll.hpp"

class Logger
{
public:
    std::string name;

    AMUSE_API Logger();
    AMUSE_API Logger(const std::string &name);

#ifdef LOGGER_NO_INFO
    template <typename... Args>
    void info(std::format_string<Args...> fmt, Args &&...args) {}
#else
    template <typename... Args>
    void info(std::format_string<Args...> fmt, Args &&...args)
    {
        std::cout << std::format("[{}][INFO] {}", name, std::format(fmt, std::forward<Args>(args)...)) << std::endl;
    }
#endif

    template <typename... Args>
    void warn(std::format_string<Args...> fmt, Args &&...args)
    {
        std::cout << std::format("[{}][WARN] {}", name, std::format(fmt, std::forward<Args>(args)...)) << std::endl;
    }

    template <typename... Args>
    void error(std::format_string<Args...> fmt, Args &&...args)
    {
        std::cerr << std::format("[{}][ERROR] {}", name, std::format(fmt, std::forward<Args>(args)...)) << std::endl;
    }

    template <typename... Args>
    void panic(std::format_string<Args...> fmt, Args &&...args)
    {
        std::cerr << std::format("[{}][PANIC] {}", name, std::format(fmt, std::forward<Args>(args)...)) << std::endl;
        std::exit(1);
    }
};

extern AMUSE_API Logger logger;