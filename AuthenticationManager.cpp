#include "AuthenticationManager.h"

/// @brief username and password can be of 255 char max
/// @param start_address 
/// @param eeprom_size 
AuthManger::AuthManger(size_t start_address, size_t eeprom_size){
    this->start_address = start_address;
    EEPROM.begin(eeprom_size);
}

void write(const char * value, size_t address){
    for (size_t i = 0; i < strlen(value); i++)
        EEPROM.write(address + i, value[i]);
}

 char * read(size_t size_to_read, byte address){
    char * ptr = (char *) malloc(size_to_read * sizeof(char));
    for (size_t i = 0; i < size_to_read; i++){
        ptr[i] = (char)EEPROM.read(address + i);
    }
    return ptr;
}

extern char * AuthManger::getUserame(){
    size_t user_length = (size_t)EEPROM.read(this->start_address);
    return read(user_length, this->start_address + 2);
}

extern char * AuthManger::getPassword(){
    size_t user_length = (size_t)EEPROM.read(this->start_address);
    size_t psw_length = (size_t)EEPROM.read(this->start_address + 1);
    return read(psw_length, (this->start_address + user_length + 2));
}

extern void AuthManger::writeUsernameAndPassword(const char * username, const char * password){
    //write at start address len of username
    EEPROM.write(this->start_address, (byte)strlen(username));
    //write at start address + 1 len of psw
    EEPROM.write(this->start_address + 1, (byte)strlen(password));
    
    write(username, (size_t)(this->start_address + 2));
    write(password, (size_t)(this->start_address + 2 + strlen(username)));

    EEPROM.commit();
}
