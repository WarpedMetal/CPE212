#ifndef ENCOUNTER_HPP
#define ENCOUNTER_HPP


#include "dictionary.hpp"
#include "vector.hpp"
#include "entity.hpp"


struct EntityNode
{
    Entity *data = nullptr;
    
    EntityNode *_nextItem = nullptr;
};

// forward list of entities.
class Encounter
{

public:
    Encounter();
    ~Encounter();
    

    void AddEntity(Entity * entity);

    void UseAction(uint32_t attackerUID, uint32_t targetUID, const std::string & spellName, const std::string & args = "");
    void PrintEntityStatus(uint32_t entityID) const;
    void PrintAllStatuses() const;

private:

    Dictionary<uint32_t, Entity* > _encounterDictionary;

    // provided
    void PrintBadAccessError(uint32_t uid) const;
    void Bars() const;

};

#endif