#ifndef COMMANDEXECUTOR_H
#define COMMANDEXECUTOR_H
#include"..\commandsValidator\commandValidator.hpp"
#include"..\factories\personFactory\personFactory.hpp"
#include"..\factories\registrationFactory\registrationFactory.hpp"
#include"..\factories\vehicleFactory\vehicleFactory.hpp"
#include"..\dynamicArrayHelper\dynamicArrayHelper.hpp"

#include<string>

class CommandExecutor
{
private:
    //all vehicles and persons
    std::vector<Vehicle> vehicles;
    std::vector<Person> persons;

    //factories
    RegistrationFactory registrationFactory;
    PersonFactory personFactory;
    VehicleFactory vehicleFactory;

    void processTwoParametersCommand(std::string command,std::string& firstParameter,std::string& secondParameter);
    void processOneParameterCommand(std::string command, std::string &parameter);
    std::string findCommandType(const std::string command);
    bool isCarExisting(Registration *registration);
    bool isPersonExisting(unsigned int id);
    void release(std::string command);
    Vehicle& getCar(Registration *registration);
    Person* getPerson(unsigned int id);
    unsigned int stringToInt(std::string string);
    CommandValidator commandValidator;
    std::vector<std::string> generateAllCommands();
    

public:
    void ExecuteCommand(std::string command);
    void clearAllObjects();
};

#endif