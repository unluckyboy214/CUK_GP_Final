// Monster.h
#ifndef MONSTER_H
#define MONSTER_H

class Monster {
public:
    Monster(int x, int y);
    void Render();
    int getX() const;
    int getY() const;

private:
    int x, y;
};

#endif // MONSTER_H
