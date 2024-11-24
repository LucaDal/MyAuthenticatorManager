This Class is used to write username and password to EEPROM.

To do so declare the class with: 
where the value passed are:
max 16 char for username;
max 16 char for password;
Starting from 0;
With EEPROM size = 512.
```
AuthManger am((size_t)16, (size_t)16, (size_t)0, (size_t)512);
``` 
and then write to EEPROM:
```
am.writeUsernameAndPassword("username", "password");
```

To read the username and password:
```
const char* password = am.getPassword();
const char* username = am.getUserame();
```
