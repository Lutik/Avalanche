#ifndef _AVALANCHE_LOG_H_
#define _AVALANCHE_LOG_H_

namespace Av
{

class Log
{
private:
	static FILE *logFile;
public:  
	static void open(const char *fileName, bool reset = true);
	static void close();
	static void log(const char *format, ...);
};

} // end of namespace

#endif