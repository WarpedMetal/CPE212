#ifndef MAGE_HPP
#define MAGE_HPP


#include "JsonEntityBuilder.hpp"
#include "entity.hpp"

class Mage : public Entity
{
private:
    void Fireball(Entity * target);
    void MagicMissiles(Entity * target);

public:

    Mage(JsonEntityBuilder &builder, JsonItemBuilder & inventory, uint32_t uid);

    virtual void OutputStatus() const override;
    virtual void WeaponAttack(Entity * target) override;

    virtual void UseAction(Entity * target, const std::string& spellName, const std::string & args) override;
};


#endif