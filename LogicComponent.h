#pragma once
#include "ComponentBase.h"

// �Q�[�����W�b�N��S���R���|�[�l���g�̒��ۊ��N���X
class LogicComponent : public ComponentBase
{
public:
    virtual ~LogicComponent() = default;

    // LogicComponent�͕K��Update�����ׂ��A�Ƃ������[������������
    // Base�N���X��Update���I�[�o�[���C�h���A�������z�ɂ���
    void Update(float deltaTime) override = 0;
};