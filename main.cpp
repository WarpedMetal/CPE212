#include <string>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "entity.hpp"
#include "encounter.hpp"
#include "JsonEntityBuilder.hpp"
#include "monster.hpp"
#include "warrior.hpp"
#include "mage.hpp"
#include "rogue.hpp"
#include "priest.hpp"



int main(int argc, char *argv[])
{
    JsonEntityBuilder builder("database.json");
    JsonItemBuilder inventory("database.json");
    Encounter encounter;
    

    if(argc != 2)
    {
        std::cout << "Invalid use of output.  Proper use of output:\n"
                  << "./Project01 ./InputFileName" << std::endl;
        return -1;
    }

    std::string fileName  = argv[1];
    if(access(fileName.c_str(), F_OK) == -1)
    {
        std::cout << "File " << fileName << " does not exist.  "
                  << "Please use a different file" << std::endl;
        return -1;
    }
    std::ifstream inputFile;
    inputFile.open(fileName);
    if(!inputFile.is_open())
    {
        std::cout << "Could not open file: " << fileName << std::endl;
        return -1;
    }
    std::string line;
    while(std::getline(inputFile, line))
    {
        if(line.size() == 0)
        {
            continue;
        }
        if(line[0] == ' ')
        {
            continue;
        }
        if(line.size() < 3)
        {
            std::cout << "invalid string found: " << line << std::endl;
            return -1;
        }
        char input = line[0];
        char who = line[2];
        // iss >> input;
        switch (input)
        {
        case 's':
            if(who == 'p')
            {
                if(line.size() < 7)
                {
                    std::cout << "Invalid string: " << line << std::endl;
                    return -1;
                }
                char type;
                uint32_t id;
                std::stringstream iss(line);
                iss >> input >> who >> type >> id;
                switch(type)
                {
                case 'w': 
                    encounter.AddEntity(new Warrior(builder, inventory, id));
                    break;
                case 'm':
                    encounter.AddEntity(new Mage(builder, inventory, id));
                    break;
                case 'r':
                    encounter.AddEntity(new Rogue(builder, inventory, id));
                    break;
                case 'p':
                    encounter.AddEntity(new Priest(builder, inventory, id));
                    break;
                default: 
                    std::cout << "Invalid character found:\n" << line << std::endl;
                    std::cout << "Type: " << type << std::endl;
                    return -1;
                }
            }
            else if(who == 'e')
            {
                uint32_t id;
                std::stringstream iss(line);
                iss >> input >> who >> id;
                encounter.AddEntity(new Monster(builder, inventory, id));
            }
            else
            {
                std::cout << "Invalid string: " << line << std::endl;
                return -1;
            }
            
            break;
        case 'p':
            if(line[2] == 'a')
            {
                encounter.PrintAllStatuses();
            }
            else
            {
                uint32_t id;
                std::stringstream iss(line);
                iss >> input >> id;
                encounter.PrintEntityStatus(id);
            }
            

            break;
        case 'a':
            {
                uint32_t user;
                uint32_t target;
                std::string spell;
                std::string args = "";
                char tmp1;
                std::stringstream iss(line);
                iss >> tmp1 >> user >> target >> spell >> args;
                encounter.UseAction(user, target, spell, args);
            }
            break;
        case 'c':
        {
            std::string str = line.substr(2, line.size() -2);
            std::cout << "\"" << str << "\"" << std::endl;
            break;
        }
        default:
            std::cout << "invalid line" << std::endl;
            break;
        }
    }


    return 0;
}