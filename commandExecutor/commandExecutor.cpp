#include "commandExecutor.hpp"
#include "..\fileOperator\FileOperator.hpp"
#include "..\exceptions\fileException.cpp"
#include "..\dynamicArrayHelper\dynamicArrayHelper.hpp"
#include<iostream>
#include <cmath>

void CommandExecutor::clearAllObjects()
{
    std::cout << "cars : " << vehicles.size();
    for (size_t i = 0; i < vehicles.size(); i++)
    {
        (*vehicles.at(i).getRegistration()).~Registration();
        std::cout << "brrrrrr";
        delete &vehicles.at(i);
        std::cout << i;
    }
    
    for (size_t i = 0; i < persons.size(); i++)
    {
        std::cout << "   trrrrrrr";
        delete &persons.at(i);
        std::cout << i;
    }
    
    vehicles.clear();
    persons.clear();
}

std::vector<std::string> CommandExecutor::generateAllCommands()
{
    std::vector < std::string> result;
    std::string currentCommand;

    for (size_t i = 0; i < vehicles.size(); i++)
    {
        std::string registrationAsString = "";
        DynamicArrayHelper::stringCopy(registrationAsString, vehicles.at(i).getRegistration()->getRegistration());
        currentCommand = "VEHICLE " + registrationAsString + " \"" + vehicles.at(i).getDescription() + '"' + '\n';
        result.push_back(currentCommand);
    }
    
    for (size_t i = 0; i < persons.size(); i++)
    {
        std::string command =  '"' + persons.at(i).getName() + "\" " + std::to_string(persons.at(i).getId());
        command = "PERSON " + command + '\n';

        result.push_back(command);
    }

    for (size_t i = 0; i < vehicles.size(); i++)
    {
        std::cout << "-----" << std::to_string(vehicles.at(i).getOwner()->getId());
        std::string registrationAsString = "";
        DynamicArrayHelper::stringCopy(registrationAsString, vehicles.at(i).getRegistration()->getRegistration());
        currentCommand = std::to_string(vehicles.at(i).getOwner()->getId()) + ' ' + registrationAsString;

        currentCommand = "ACQUIRE " + currentCommand + '\n';
        result.push_back(currentCommand);
    }

    return result;
}

std::string CommandExecutor::findCommandType(const std::string command)
{
    std::string commandType = command.substr(0, command.find(' '));

    return commandType;
}

void CommandExecutor::processOneParameterCommand(std::string command, std::string &parameter)
{
    std::size_t commandLenght = command.size();

    int currentParameter = 0;
    bool isInString = false;

    for (std::size_t i = 0; i < commandLenght; ++i)
    {
        if (command[i] == ' ' && !isInString)
        {
            ++currentParameter;
            ++i;
        } 

        if (command[i] == '"' && !isInString)
        {
            isInString = true;
            ++i;
        }
        if (command[i] == '"' && isInString)
        {
            isInString = false;
            ++i;
            if (command[i] == ' ')
            {
                ++currentParameter;
                ++i;
            }
        }
        
        if (currentParameter == 1)
        {
            parameter.push_back(command[i]);
        }    
    }
}

void CommandExecutor::processTwoParametersCommand(std::string command, std::string& firstParameter, std::string& secondParameter)
{
    std::size_t commandLenght = command.size();

    int currentParameter = 0;
    bool isInString = false;

    for (std::size_t i = 0; i < commandLenght; ++i)
    {
        if (command[i] == ' ' && !isInString)
        {
            ++currentParameter;
            ++i;
        } 

        if (command[i] == '"' && !isInString)
        {
            isInString = true;
            ++i;
        }
        if (command[i] == '"' && isInString)
        {
            isInString = false;
            ++i;
            if (command[i] == ' ')
            {
                ++currentParameter;
                ++i;
            }
        }
        
        if (currentParameter == 1)
        {
            firstParameter.push_back(command[i]);
        }
        else if (currentParameter == 2)
        {
            secondParameter.push_back(command[i]);
        }
           
    }
}

Vehicle& CommandExecutor::getCar(Registration *registration)
{
    for (size_t i = 0; i < vehicles.size(); i++)
    {
        if (*(vehicles.at(i).getRegistration()) == *registration)
        {
            return vehicles.at(i);
        }
    }

    throw std::invalid_argument("vehicle's registration is invalid");
}

Person* CommandExecutor::getPerson(unsigned int id)
{
    for (size_t i = 0; i < persons.size(); i++)
    {
        if (persons.at(i).getId() == id)
        {
            return &(persons.at(i));
        }
    }

    return nullptr;
}

unsigned int CommandExecutor::stringToInt(std::string string)
{
    unsigned int result = 0;
    int size = string.size();
    int multiplier = std::pow(10, size - 1);
        
    for (size_t i = 0; i < size; i++)
    {
        if(string.at(i) < 48 || string.at(i) > 57)
        {
            throw std::invalid_argument("id must be a digit");
        }

        result += (string.at(i) - 48) * multiplier;

        multiplier /= 10;
    }

    return result;
}

void CommandExecutor::release(std::string command)
{
    //RELEASE <owner-id> <vehicle-id>

    std::string rawOwnerId = "";
    std::string rawVehicleId = "";

    processTwoParametersCommand(command, rawOwnerId, rawVehicleId);

    try
    {
        std::size_t registrationSize = rawVehicleId.size();
        char* registrationSource = DynamicArrayHelper::allocateDynamicCharArray(registrationSize);
        DynamicArrayHelper::stringCopy(registrationSource, rawVehicleId);

        Registration registration(registrationSource);
        unsigned int id = stringToInt(rawOwnerId);
        
        Vehicle &v = getCar(&registration);
        Vehicle *vehicle = &v;
        Person *person = getPerson(id);

        if (vehicle == nullptr)
        {
            throw std::invalid_argument("vehicle's registration in invalid");
        }

        if (person == nullptr)
        {
            throw std::invalid_argument("person's id in invalid");
        }
        if(vehicle->getOwner() == nullptr)
        {
            throw std::invalid_argument("the car has no owner!");
        }

        if(vehicle->getOwner()->getId() != person->getId())
        {
            throw std::invalid_argument("this car is not property to this person");
        }

        vehicle->setOwner(nullptr);
        person->removeVehicle(vehicle);
    }
    catch(const std::invalid_argument& e)
    {
        throw e;
    }
    
}

void CommandExecutor::ExecuteCommand(std::string command)
{
    try
    {
        commandValidator.isCommandValid(command);
    }
    catch(const std::invalid_argument& exception)
    {
        throw exception;
    }
    
    std::string commandType = findCommandType(command);

    if (commandType == "save")
    {
        FileOperator fileOperator;
        std::string commandParameter = "";

        processOneParameterCommand(command, commandParameter);

        try
        {
            fileOperator.openFile(commandParameter);
            if (!fileOperator.isFileEmpty())
            {
                std::cout << "the chossen file is not empty! Are you sure you want to override it? Type yes or no!";
                std::string confirmation;
                std::getline(std::cin, confirmation);

                if (confirmation == "yes")
                {
                    std::vector<std::string> allCommands = generateAllCommands();

                    for (std::string currentCommand: allCommands)
                    {
                        fileOperator.addToFile(currentCommand);
                    } 
                }
            }
        }
        catch(const FileException& e)
        {
            std::cout << "the save file doesn't exists \n";
        }
    }
    else if(commandType == "vehicle")
    {
        std::string rawRegistration = "";
        std::string description = "";
        char *registrationSource = nullptr;

        processTwoParametersCommand(command, rawRegistration, description);

        try
        {
            std::size_t registrationSize = rawRegistration.size();
            char* registrationSource = DynamicArrayHelper::allocateDynamicCharArray(registrationSize);
            DynamicArrayHelper::stringCopy(registrationSource, rawRegistration);

            Registration* registration = registrationFactory.createRegistration(registrationSource);
            vehicles.push_back(vehicleFactory.createVehicleWithoutOwner(registration, description));

            delete[] registrationSource;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            delete[] registrationSource;
        }
    }
    else if(commandType == "person")
    {
        std::string name = "";
        std::string rawId = "";

        processTwoParametersCommand(command, name, rawId);

        try
        {
            unsigned int id = stringToInt(rawId);
            persons.push_back(*personFactory.createPerson(id, name));
        }
        catch(const std::invalid_argument& exception)
        {
            throw exception;
        }
    }
    else if(commandType == "acquire")
    {
        //ACQUIRE <owner-id> <vehicle-id>
        std::string rawOwnerId = "";
        std::string rawVehicleId = "";

        processTwoParametersCommand(command, rawOwnerId, rawVehicleId);

        try
        {
            std::size_t registrationSize = rawVehicleId.size();
            char* registrationSource = DynamicArrayHelper::allocateDynamicCharArray(registrationSize);
            DynamicArrayHelper::stringCopy(registrationSource, rawVehicleId);

            Registration registration(registrationSource);
            unsigned int id = stringToInt(rawOwnerId);
            Vehicle *vehicle = &(getCar(&registration));
            Person *person = getPerson(id);
            
            if (vehicle == nullptr)
            {
                throw std::invalid_argument("vehicle's registration is invalid");
            }

            if (person == nullptr)
            {
                throw std::invalid_argument("person's id in invalid");
            }
            
            if (vehicle->getOwner() != nullptr)
            {
                release(command);
            }
            
            vehicle->setOwner(person);
            person->addVehicle(vehicle);
        }
        catch(const std::invalid_argument& exception)
        {
            throw exception;
        }

    }
    else if (commandType == "release")
    {
        release(command);
    }
    else if (commandType == "remove")
    {
        std::string commandArgument = "";
        processOneParameterCommand(command, commandArgument);
        bool isArgumentId = false;
        bool isArgumentRegistration = false;
        unsigned int id;
        Registration registration;
        char *registrationSource = nullptr;
        Vehicle *vehicle = nullptr;

        //checks if the parameter is person's id
        try
        {
            id = stringToInt(commandArgument);
            isArgumentId = true;
        }
        catch(const std::invalid_argument& exception)
        {
            isArgumentId = false;
        }

        //checks if the parameter is vehicle registration
        

        if (!isArgumentId)
        {
            try
            {
                std::size_t registrationSize = commandArgument.size();
                registrationSource = DynamicArrayHelper::allocateDynamicCharArray(registrationSize);
                DynamicArrayHelper::stringCopy(registrationSource, commandArgument);
                registration.setRegistration(registrationSource);
            
                vehicle = &(getCar(&registration));
                if(vehicle == nullptr)
                {
                    throw std::invalid_argument("this registration is invalid or there is not car with such registration");
                }
                else
                {
                    isArgumentRegistration = true;
                }

                delete[] registrationSource;
            }
            catch(const std::invalid_argument& exception)
            {
                delete[] registrationSource;
                isArgumentRegistration = false;
            }
        }
        
        if (!isArgumentId && !isArgumentRegistration)
        {
            throw std::invalid_argument("you can remove only persons and vehicles, your argument is invalid");
        }
        if (isArgumentRegistration)
        {
            std::string registrationAsString = "";
            DynamicArrayHelper::stringCopy(registrationAsString, vehicle->getRegistration()->getRegistration());

            std::string command = ' ' + std::to_string(vehicle->getOwner()->getId()) + ' ' +  registrationAsString;
            command = "release" + command;
            release(command);

            for (size_t i = 0; i < vehicles.size(); i++)
            {
                if (*(vehicles.at(i).getRegistration()) == *(vehicles.at(i).getRegistration()))
                {
                    delete &vehicles.at(i);
                    vehicles.erase(vehicles.begin() + i, vehicles.begin() + i + 1);

                    break;
                }
            }
        }
        else if(isArgumentId)
        {
            for (size_t i = 0; i < persons.size(); i++)
            {
                if (persons.at(i).getId() == id)
                {
                    std::vector<Vehicle> ownedVehicles = persons.at(i).getOwnedVehicles();

                    for (size_t i = 0; i < ownedVehicles.size(); i++)
                    {
                        ownedVehicles.at(i).setOwner(nullptr);
                    }
                    
                }

                delete &(persons.at(i));
                persons.erase(persons.begin() + i, persons.begin() + i + 1);
            }            
        }
    }          
    else if (commandType == "show")
    {
        std::string commandParameter = "";

        processOneParameterCommand(command, commandParameter);

        if (commandParameter == "PEOPLE")
        {
            for (Person currentPerson : persons)
            {
                currentPerson.print();
            }
            
        }
        else if (commandParameter == "VEHICLES")
        {
            for (Vehicle currentVehicle : vehicles)
            {
                currentVehicle.print();
            }
        }
        else
        {
            bool isArgumentId = false;
            bool isArgumentRegistration = false;
            unsigned int id;
            Registration registration;
            char *registrationSource = nullptr;
            Vehicle *vehicle = nullptr;

            //checks if the parameter is person's id
            try
            {
                id = stringToInt(commandParameter);
                isArgumentId = true;
            }
            catch(const std::invalid_argument& exception)
            {
                throw exception;
            }

            if (!isArgumentId)
            {
                try
                {
                    std::size_t registrationSize = commandParameter.size();
                    registrationSource = DynamicArrayHelper::allocateDynamicCharArray(registrationSize);
                    DynamicArrayHelper::stringCopy(registrationSource, commandParameter);

                    registration.setRegistration(registrationSource);
            
                    vehicle = &(getCar(&registration));

                    if(vehicle == nullptr)
                    {
                        throw std::invalid_argument("this registration is invalid or there is not car with such registration");
                    }
                    else
                    {
                        isArgumentRegistration = true;
                    }

                    delete[] registrationSource;
                }
                catch(const std::invalid_argument& exception)
                {
                    delete[] registrationSource;
                    throw exception;
                }
            }

            if (!isArgumentId && !isArgumentRegistration)
            {
                throw std::invalid_argument("you can show only all people, vehicles, exact vehicle or exact person. Your command argument is invalid");
            }
            if (isArgumentRegistration)
            {
                vehicle->print();
            }

            else if(isArgumentId)
            {
                for (Person person: persons)
                {
                    if (person.getId() == id)
                    {
                        person.print();
                    }
                } 
            }
        }
    }   
}