#pragma once
#ifndef K_NPC_H
#define K_NPC_H

class K_Npc {
public:
    K_Npc();
    void interact();
    void HandleEvents();
    void Update(float deltaTime);
    void Render();
    // 기타 멤버 함수 및 변수

private:
    // NPC의 상태나 속성에 대한 변수들
};

#endif
