#ifndef WARRIOR_HPP
#define WARRIOR_HPP

#include "JsonEntityBuilder.hpp"
#include "entity.hpp"


class Warrior : public Entity
{
private:

    void Strike(Entity* target);
    void ShieldSmash(Entity * target);

public:
    Warrior(JsonEntityBuilder &builder, JsonItemBuilder & inventory, uint32_t uid);

    virtual void OutputStatus() const override;
    virtual void WeaponAttack(Entity * target) override;

    virtual void UseAction(Entity * target, const std::string& spellName, const std::string & args) override;

};



#endif // WARRIOR_HPP