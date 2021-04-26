#ifndef PRIEST_HPP
#define PRIEST_HPP

#include "JsonEntityBuilder.hpp"
#include "entity.hpp"


class Priest : public Entity
{
private:

    void Smite(Entity * target);
    void GreaterHeal(Entity * target);


public:
    Priest(JsonEntityBuilder &builder, JsonItemBuilder & inventory, uint32_t uid);

    virtual void OutputStatus() const override;
    virtual void WeaponAttack(Entity * target) override;

    virtual void UseAction(Entity * target, const std::string& spellName, const std::string & args) override;


};



#endif