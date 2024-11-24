#ifndef AUTHENTICATIONMANAGER_H
#define AUTHENTICATIONMANAGER_H

#include <EEPROM.h>
#include <Arduino.h>
//Scrivi su eeprom o leggi da eprom username and password;
class AuthManger{
    private:
        size_t start_address;
    public:
        AuthManger(size_t start_address, size_t eeprom_size);
        char *getUserame();
        char *getPassword();
        void writeUsernameAndPassword(const char * username, const char * password);
};

#endif