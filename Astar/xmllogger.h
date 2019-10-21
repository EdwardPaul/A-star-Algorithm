#ifndef XMLLOGGER_H
#define	XMLLOGGER_H
#include "tinyxml2.h"
#include "string.h"
#include "map.h"
#include <map>
#include <unordered_map>
#include "config.h"
#include "ilogger.h"

class XmlLogger:public ILogger
{
private:
    std::string LogFileName;
    tinyxml2::XMLDocument doc;
public:
    XmlLogger();
    XmlLogger(std::string loglevel):ILogger(loglevel){}
    virtual ~XmlLogger() {};
    bool getLog(const char *FileName, const std::string *LogParams);
    void saveLog();
    void writeToLogMap(const Map &Map, const std::list<AgentConfiguration> &path);
    void writeToLogPath(const std::list<AgentConfiguration> &path);
    void writeToLogNotFound();
    void writeToLogSummary(SearchResult result, double cellSize);
};

#endif
