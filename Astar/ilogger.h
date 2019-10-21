#ifndef ILOGGER_H
#define	ILOGGER_H
#include "map.h"
#include "struct.h"
#include <unordered_map>
#include <list>
#include <map>

class ILogger
{
    public:
        ILogger(){}
        ILogger(std::string loglevel) {this->loglevel = loglevel;}
        virtual bool getLog(const char* FileName, const std::string* LogParams) = 0;
        virtual void writeToLogMap(const Map& map, const std::list<AgentConfiguration>& path) = 0;
        virtual void writeToLogPath(const std::list<AgentConfiguration>& path) = 0;
        virtual void writeToLogSummary(SearchResult result, double cellSize) = 0;
        virtual ~ILogger() {};
    protected:
        std::string loglevel;
};

#endif

