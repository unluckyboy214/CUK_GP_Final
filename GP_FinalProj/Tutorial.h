#ifndef TUTORIAL_H
#define TUTORIAL_H

#include "Map.h"

class Tutorial : public Map {
public:
    Tutorial();
    virtual void SpawnMonsters() override;
    virtual void SpawnMonster() override;
    virtual void Update(float deltaTime) override;
    virtual void Render() override;
    virtual void HandleEvent(SDL_Event& event);
    void ResetPortalCloaking();

private:
    SDL_Texture* portalTexture;
    SDL_Rect portalRect;
    bool showPortal;
};

#endif // Tutorial_H