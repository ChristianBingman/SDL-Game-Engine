/*****************************
 * Title: Log.h
 * Author: Christian Bingman
 * Description: Logging class to allow for comprehensive and concise output
*****************************/
#pragma once

#include <string>

using namespace std;

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
