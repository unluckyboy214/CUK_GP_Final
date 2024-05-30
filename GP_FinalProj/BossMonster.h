#ifndef BOSSMONSTER_H
#define BOSSMONSTER_H

#include "Monster.h"

class BossMonster : public Monster {
public:
    BossMonster(int x, int y);
    void Update(float deltaTime, const SDL_Rect& playerRect) override;
    void Render() override;

    int getHP() const;
    void takeDamage(int amount);

private:
    int hp;
};

#endif
