#include "messageagent.h"

MessageAgent *MessageAgent::instance = 0;

MessageAgent *MessageAgent::getInstance()
{
    if(instance == 0)
        instance = new MessageAgent;
    return instance;
}

void MessageAgent::emitTileClicked()
{
    emit tileClicked();
}

MessageAgent::MessageAgent() {}
