#pragma once // �C���ς�
#include "ComponentBase.h"

// �`���S���R���|�[�l���g�̒��ۊ��N���X
class DrawComponent : public ComponentBase
{
public:
    virtual ~DrawComponent() = default;

    // DrawComponent�͕K��Draw�����ׂ��A�Ƃ������[������������
    virtual void Draw() = 0;
};