#include <string>

#include <sys/types.h>  // mkfifo
#include <sys/stat.h>   // mkfifo
#include <fcntl.h>
#include <cstring>
#include <cstdlib>
#include <iostream>

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>

#include "Controller.h"
#include "Logger.h"

Controller* Controller::m_instance = NULL;

Controller *Controller::Instance()
{
    if (!m_instance)
    {
        m_instance = new Controller();
    }
    return m_instance;
}

Controller::Controller()
{
    struct passwd *pw = getpwuid(getuid());
    std::string home_path = std::string(pw->pw_dir);
    std::string legacy_config_path = home_path + "/.dolphin-emu";
    std::string pipe_path;

    struct stat buffer;
    if(stat(legacy_config_path.c_str(), &buffer) != 0)
    {
        //If the legacy app path is not present, see if the new one is
        const char *env_XDG_DATA_HOME = std::getenv("XDG_DATA_HOME");
        if(env_XDG_DATA_HOME == NULL)
        {
            //Try $HOME/.local/share next
            std::string backup_path = home_path + "/.local/share/dolphin-emu";
            if(stat(backup_path.c_str(), &buffer) != 0)
            {
                std::cout << "ERROR: $XDG_DATA_HOME was empty and so was $HOME/.dolphin-emu and $HOME/.local/share/dolphin-emu " \
                    "Are you sure Dolphin is installed? Make sure it is, and then run SmashBot again." << std::endl;
                exit(-1);
            }
            pipe_path = backup_path;
            pipe_path += "/Pipes/SmashBot";
        }
        else
        {
            pipe_path = env_XDG_DATA_HOME;
            pipe_path += "/Pipes/SmashBot";
        }
    }
    else
    {
        pipe_path = legacy_config_path + "/Pipes/SmashBot";
    }

    m_fifo = mkfifo(pipe_path.c_str(), S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
    std::cout << "DEBUG: Waiting for Dolphin..." << std::endl;

    if ((m_fifo = open(pipe_path.c_str(), O_WRONLY)) < 0) {
       printf("%s\n", strerror(errno));
       return;
    }
    std::cout << "DEBUG: Off to the races!" << std::endl;
}

void Controller::pressButton(BUTTON b)
{
    Logger *logger = Logger::Instance();
    std::string button_string;
    switch (b)
    {
        case BUTTON_A:
        {
            button_string = STRING_A;
            logger->Log(INFO, "Button press: " + STRING_A);
            break;
        }
        case BUTTON_B:
        {
            button_string = STRING_B;
            logger->Log(INFO, "Button press: " + STRING_B);
            break;
        }
        case BUTTON_X:
        {
            button_string = STRING_X;
            logger->Log(INFO, "Button press: " + STRING_X);
            break;
        }
        case BUTTON_Y:
        {
            button_string = STRING_Y;
            logger->Log(INFO, "Button press: " + STRING_Y);
            break;
        }
        case BUTTON_L:
        {
            button_string = STRING_L;
            logger->Log(INFO, "Button press: " + STRING_L);
            break;
        }
        case BUTTON_R:
        {
            button_string = STRING_R;
            logger->Log(INFO, "Button press: " + STRING_R);
            break;
        }
        case BUTTON_Z:
        {
            button_string = STRING_Z;
            logger->Log(INFO, "Button press: " + STRING_Z);
            break;
        }
        case BUTTON_START:
        {
            button_string = STRING_START;
            logger->Log(INFO, "Button press: " + STRING_START);
            break;
        }
        case BUTTON_D_UP:
        {
            button_string = STRING_D_UP;
            logger->Log(INFO, "Button press: " + STRING_D_UP);
            break;
        }
        case BUTTON_D_DOWN:
        {
            button_string = STRING_D_DOWN;
            logger->Log(INFO, "Button press: " + STRING_D_DOWN);
            break;
        }
        case BUTTON_D_LEFT:
        {
            button_string = STRING_D_LEFT;
            logger->Log(INFO, "Button press: " + STRING_D_LEFT);
            break;
        }
        case BUTTON_D_RIGHT:
        {
            button_string = STRING_D_RIGHT;
            logger->Log(INFO, "Button press: " + STRING_D_RIGHT);
            break;
        }
        case BUTTON_MAIN:
        {
            button_string = STRING_MAIN;
            logger->Log(INFO, "Button press: " + STRING_MAIN);
            break;
        }
        case BUTTON_C:
        {
            button_string = STRING_C;
            logger->Log(INFO, "Button press: " + STRING_C);
            break;
        }
        default:
        {
            std::cout << "WARNING: Invalid button selected!" << std::endl;
        }
    }

    std::string command = "PRESS " + button_string + "\n";

    m_buffer += command;
}

void Controller::releaseButton(BUTTON b)
{
    Logger *logger = Logger::Instance();
    std::string button_string;
    switch (b)
    {
        case BUTTON_A:
        {
            button_string = STRING_A;
            logger->Log(INFO, "Button release: " + STRING_A);
            break;
        }
        case BUTTON_B:
        {
            button_string = STRING_B;
            logger->Log(INFO, "Button release: " + STRING_B);
            break;
        }
        case BUTTON_X:
        {
            button_string = STRING_X;
            logger->Log(INFO, "Button release: " + STRING_X);
            break;
        }
        case BUTTON_Y:
        {
            button_string = STRING_Y;
            logger->Log(INFO, "Button release: " + STRING_Y);
            break;
        }
        case BUTTON_L:
        {
            button_string = STRING_L;
            logger->Log(INFO, "Button release: " + STRING_L);
            break;
        }
        case BUTTON_R:
        {
            button_string = STRING_R;
            logger->Log(INFO, "Button release: " + STRING_R);
            break;
        }
        case BUTTON_Z:
        {
            button_string = STRING_Z;
            logger->Log(INFO, "Button release: " + STRING_Z);
            break;
        }
        case BUTTON_START:
        {
            button_string = STRING_START;
            logger->Log(INFO, "Button release: " + STRING_START);
            break;
        }
        case BUTTON_D_UP:
        {
            button_string = STRING_D_UP;
            logger->Log(INFO, "Button release: " + STRING_D_UP);
            break;
        }
        case BUTTON_D_DOWN:
        {
            button_string = STRING_D_DOWN;
            logger->Log(INFO, "Button release: " + STRING_D_DOWN);
            break;
        }
        case BUTTON_D_LEFT:
        {
            button_string = STRING_D_LEFT;
            logger->Log(INFO, "Button release: " + STRING_D_LEFT);
            break;
        }
        case BUTTON_D_RIGHT:
        {
            button_string = STRING_D_RIGHT;
            logger->Log(INFO, "Button release: " + STRING_D_RIGHT);
            break;
        }
        case BUTTON_MAIN:
        {
            button_string = STRING_MAIN;
            logger->Log(INFO, "Button release: " + STRING_MAIN);
            break;
        }
        case BUTTON_C:
        {
            button_string = STRING_C;
            logger->Log(INFO, "Button release: " + STRING_C);
            break;
        }
        default:
        {
            std::cout << "WARNING: Invalid button selected!" << std::endl;
        }
    }
    std::string command = "RELEASE " + button_string + "\n";

    m_buffer += command;
}

void Controller::pressShoulder(BUTTON b, double amount)
{
    Logger *logger = Logger::Instance();
    std::string button_string;
    switch (b)
    {
        case BUTTON_L:
        {
            button_string = STRING_L;
            logger->Log(INFO, "Shoulder press: " + STRING_L + " to " + std::to_string(amount));
            break;
        }
        case BUTTON_R:
        {
            button_string = STRING_R;
            logger->Log(INFO, "Shoulder press: " + STRING_R + " to " + std::to_string(amount));
            break;
        }
        default:
        {
            std::cout << "WARNING: Invalid shoulder selected!" << std::endl;
        }
    }
    std::string command = "SET " + button_string + " " + std::to_string(amount) + "\n";

    m_buffer += command;
}

void Controller::tiltAnalog(BUTTON b, double x, double y)
{
    Logger *logger = Logger::Instance();
    std::string button_string;
    switch (b)
    {
        case BUTTON_MAIN:
        {
            button_string = STRING_MAIN;
            logger->Log(INFO, "Tilt analog: " + STRING_MAIN + " to " + std::to_string(x) + ", " + std::to_string(y));
            break;
        }
        case BUTTON_C:
        {
            button_string = STRING_C;
            logger->Log(INFO, "Tilt analog: " + STRING_C + " to " + std::to_string(x) + ", " + std::to_string(y));
            break;
        }
        default:
        {
            std::cout << "WARNING: Invalid analog selected!" << std::endl;
        }
    }
    std::string command = "SET " + button_string + " " + std::to_string(x) +
        " " + std::to_string(y) + "\n";

    m_buffer += command;
}

void Controller::emptyInput()
{
    Logger *logger = Logger::Instance();
    logger->Log(INFO, "Blank controller input");
    tiltAnalog(Controller::BUTTON_MAIN, .5, .5);
    tiltAnalog(Controller::BUTTON_C, .5, .5);
    pressShoulder(Controller::BUTTON_L, 0);
    pressShoulder(Controller::BUTTON_R, 0);
    releaseButton(Controller::BUTTON_X);
    releaseButton(Controller::BUTTON_Y);
    releaseButton(Controller::BUTTON_A);
    releaseButton(Controller::BUTTON_B);
    releaseButton(Controller::BUTTON_L);
    releaseButton(Controller::BUTTON_R);
    releaseButton(Controller::BUTTON_START);
    releaseButton(Controller::BUTTON_Z);
}

void Controller::flush()
{
    uint num = write(m_fifo, m_buffer.c_str(), m_buffer.length());
    if(num < m_buffer.length())
    {
        std::cout << "WARNING: Not all data written to pipe!" << std::endl;
    }

    m_buffer = "";
}
