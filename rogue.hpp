#ifndef ROGUE_HPP
#define ROGUE_HPP

#include "JsonEntityBuilder.hpp"
#include "entity.hpp"


class Rogue : public Entity
{
private:

    void Backstab(Entity * target);
    void Blindside(Entity * target);
    void PickPocket(Entity * target, uint32_t itemUID);

public:
    Rogue(JsonEntityBuilder &builder, JsonItemBuilder & inventory, uint32_t uid);
    
    virtual void OutputStatus() const override;
    virtual void WeaponAttack(Entity * target) override;


    virtual void UseAction(Entity * target, const std::string& spellName, const std::string & args) override;

};


#endif // ROGUE_HPP