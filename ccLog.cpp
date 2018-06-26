#include "ccLog.h"

Log::Log(ccMainAppInterface* app)
{
	this->m_app = app;
}

void Log::logInfo(QString s)
{
    this->m_app->dispToConsole("[ICP] " + s, ccMainAppInterface::STD_CONSOLE_MESSAGE);
}

void Log::logWarn(QString s)
{
    this->m_app->dispToConsole("[ICP] " + s, ccMainAppInterface::WRN_CONSOLE_MESSAGE);
}

void Log::logError(QString s)
{
    this->m_app->dispToConsole("[ICP] " + s, ccMainAppInterface::ERR_CONSOLE_MESSAGE);
} 
