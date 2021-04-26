#ifndef MONSTER_HPP
#define MONSTER_HPP

#include "JsonEntityBuilder.hpp"
#include "entity.hpp"


class Monster : public Entity
{
private:
    uint32_t weapon_damage;

public:
    Monster(JsonEntityBuilder &builder, JsonItemBuilder & inventory, uint32_t uid);
    ~Monster() = default;

    virtual void OutputStatus() const override;
    virtual void WeaponAttack(Entity * target) override;
    virtual void UseAction(Entity * target, const std::string& spellName, const std::string & args) override;

};



#endif