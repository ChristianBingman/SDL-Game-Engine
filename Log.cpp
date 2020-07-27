/*
 * Title: Log.cpp
 * Author: Christian Bingman
 * Description: Logger header functions
 * Date Created: July 26, 2020
 */

#include<iostream>
#include "Log.h"
#include "Game.h"

/*
 * Logger::Logger
 * + Logger constructor
 *
 * Arguments:
 * + None
 *
 * Return Type: void
 */
Logger::Logger(/* args */)
{
    cout << "LOGS: Logger Initialized" << endl;
}

/*
 * Logger::~Logger
 * + Logger destructor
 *
 * Arguments:
 * + None
 *
 * Return Type: void
 */
Logger::~Logger()
{
    cout << "LOGS: Logger Cleanup" << endl;
}

/*
 * Logs output to console
 * + log_message - Message to be logged to console
 * + log_level - how output will be displayed
 * ++ 0 - General logs / unknown
 * ++ 1 - Information
 * ++ 2 - Warning
 * ++ 3 - Error
 * ++ 4 - Panic
 */
void Logger::log(string log_message, int log_level){
    string output;
    switch (log_level)
    {
    case 0:
        output.append("LOGS: ");
        break;
    case 1:
        output.append("\033[0;36mINFO: ");
        break;
    case 2:
        output.append("\033[0;33mWARN: ");
        break;
    case 3:
        output.append("\033[0;31mERROR: ");
        break;
    case 4:
        output.append("\033[0;35mPANIC: ");
        Game::isRunning = false;
        break;
    default:
        output.append("INFO: ");
        break;
    }

    output.append(log_message);

    cout << output << endl;
}

/*
 * Logger::logStartApp
 * + Prints MOTD style header for debug output
 *
 * Arguments:
 * + None
 *
 * Return Type: void
 */
void Logger::logStartApp(){
    cout << "\033[1;32mWelcome to a Simple SDL App" << endl
        << "\tFunctions:" << endl
        << "\t  - Shows stuff" << endl;
}