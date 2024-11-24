#include "AuthenticationManager.h"

AuthManger::AuthManger(size_t size_username, size_t size_password, size_t start_address, size_t eeprom_size){
    this->max_size_username = size_username;
    this->max_size_password = size_password;
    this->start_address = start_address;
    EEPROM.begin(eeprom_size);
}

 void write(const char * value, size_t max_lenght, size_t start_address){
    
    for (size_t i = 0; i < max_lenght; i++){
        if(i < strlen(value)){
            EEPROM.write(start_address + i, value[i]);
        }else{
            EEPROM.write(start_address + i, 0);
        }
    }
}

 char * read(size_t size_to_read, size_t start_address){
    char * ptr = (char *) malloc(size_to_read * sizeof(char));
    for (size_t i = 0; i < size_to_read; i++){
        ptr[i] = (char)EEPROM.read(start_address + i);
    }
    return ptr;
}

extern char * AuthManger::getUserame(){
    return read(this->max_size_username, this->start_address);
}

extern char * AuthManger::getPassword(){
    return read(this->max_size_password, (this->start_address + this->max_size_username));
}

extern void AuthManger::writeUsername(const char * username){
    write(username, this->max_size_username, this->start_address);
    EEPROM.commit();
}
extern void AuthManger::writePassword(const char * password){
    write(password, this->max_size_password, (this->start_address + this->max_size_username));
    EEPROM.commit();
}

extern void AuthManger::writeUsernameAndPassword(const char * username, const char * psw){
    write(username, this->max_size_username, this->start_address);
    write(psw, this->max_size_password, this->start_address + this->max_size_username);
    EEPROM.commit();
}