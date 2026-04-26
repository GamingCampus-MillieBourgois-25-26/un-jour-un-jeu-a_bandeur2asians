#pragma once
#include "Core/Component.h"

namespace BulletHell
{
    class Health : public Component
    {
    public:
        Health(float maxHp) : m_hp(maxHp), m_maxHp(maxHp) {}

        void TakeDamage(float amount)
        {
            m_hp -= amount;
            if (m_hp <= 0.f)
            {
                m_hp = 0.f;
                m_dead = true;
            }
        }

        float GetHp()    const { return m_hp; }
        float GetMaxHp() const { return m_maxHp; }
        bool  IsDead()   const { return m_dead; }

        void Reset() { m_hp = m_maxHp; m_dead = false; }

    private:
        float m_hp;
        float m_maxHp;
        bool  m_dead = false;
    };
}