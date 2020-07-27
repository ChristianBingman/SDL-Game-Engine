/*
 * Title: Log.h
 * Author: Christian Bingman
 * Description: Logging class to enable more creative debugging output
 * Date Created: July 26, 2020
 */
#pragma once

#include <string>

using namespace std;

/*
 * Title: Logger
 * + Logs debug output to screen
 */
class Logger
{
private:
    /* data */
public:
    Logger();
    ~Logger();
    void log(string log_message, int log_level);
    void logStartApp();
};
