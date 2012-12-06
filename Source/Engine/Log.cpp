#include "stdafx.h"
#include "Log.h"

namespace Av
{

FILE *Log::logFile = nullptr;

void Log::open(const char *fileName, bool reset)
{
	if(logFile)
	{
		fclose(logFile);
		logFile = nullptr;
	}

	fopen_s(&logFile, fileName, reset ? "w" : "a");
}

void Log::close()
{
	if(logFile != NULL) 
	{
		fclose(logFile);
		logFile = NULL;
	}
}

void Log::log(const char *format, ...)
{
	if (format == nullptr || logFile == nullptr) return;

	va_list	ap;
	va_start(ap, format);
	vfprintf(logFile, format, ap);
	fflush(logFile);
}

} // end of namespace