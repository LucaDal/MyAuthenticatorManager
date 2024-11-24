#include "AuthenticationManager.h"

/// @brief username and password can be of 255 char max
/// @param start_address 
/// @param eeprom_size 
AuthManger::AuthManger(size_t start_address, size_t eeprom_size){
    this->start_address = start_address;
    EEPROM.begin(eeprom_size);
}

void write(String value, size_t start_address){
    
    for (size_t i = 0; i < value.length(); i++)
        EEPROM.write(start_address + i, value[i]);
}

 char * read(size_t size_to_read, byte start_address){
    char * ptr = (char *) malloc(size_to_read * sizeof(char));
    for (size_t i = 0; i < size_to_read; i++){
        ptr[i] = (char)EEPROM.read(start_address + i);
    }
    return ptr;
}

extern char * AuthManger::getUserame(){
    size_t user_length = (size_t)EEPROM.read(start_address);
    return read(user_length, this->start_address + 2);
}

extern char * AuthManger::getPassword(){
    size_t user_length = (size_t)EEPROM.read(start_address);
    size_t psw_length = (size_t)EEPROM.read(start_address + 1);
    return read(psw_length, (this->start_address + user_length + 2));
}

extern void AuthManger::writeUsernameAndPassword(const char * username, const char * password){

    String tmp_user = String(username);
    String tmp_psw = String(password);
    //write at start address len of username
    EEPROM.write(start_address, (byte)tmp_user.length());
    //write at start address + 1 len of psw
    EEPROM.write(start_address + 1, (byte)tmp_psw.length());
    
    write(tmp_user, (size_t)(this->start_address + 2));
    write(tmp_psw, (size_t)(this->start_address + tmp_user.length() + 2));

    EEPROM.commit();
}
