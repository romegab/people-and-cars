#ifndef REGISTRATION_H
#define REGISTRATION_H
#include <iostream>
#include <string>

class Registration
{
private:
    char *registration;

public:
    Registration();
    Registration(const char *registration);
    Registration(const Registration &source);
    ~Registration();
    void setRegistration(const char* registration);
    const char* getRegistration();
    bool operator==(const Registration &registration);
    void operator=(Registration &registration);
    void print();
};

#endif