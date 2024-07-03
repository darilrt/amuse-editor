
#include "debug_component.hpp"

DebugComponent::DebugComponent()
{
}

void DebugComponent::on_start()
{
    logger.info("DebugComponent on_start");
}

void DebugComponent::on_update()
{
    logger.info("DebugComponent on_update");
}