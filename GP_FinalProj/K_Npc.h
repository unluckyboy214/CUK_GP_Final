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
    // ��Ÿ ��� �Լ� �� ����

private:
    // NPC�� ���³� �Ӽ��� ���� ������
};

#endif
