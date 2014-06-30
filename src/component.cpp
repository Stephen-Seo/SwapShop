
#include "component.hpp"
#include "componentHolder.hpp"

Component::Component(ComponentHolder* holder) :
holder(holder),
reqUpdate(false),
reqEvents(false),
reqDraw(false),
reqMessage(false)
{}

bool Component::requiresUpdate()
{
    return reqUpdate;
}

bool Component::requiresEvents()
{
    return reqEvents;
}

bool Component::requiresDraw()
{
    return reqDraw;
}

bool Component::requiresMessage()
{
    return reqMessage;
}

void Component::broadcastMessage(int message)
{
    holder->queueMessage(message);
}
