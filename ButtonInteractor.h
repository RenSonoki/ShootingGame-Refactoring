#pragma once
#include "UIInteractor.h"

// �{�^���́u�C���^���N�V�����v�U�镑����S������N���X
class ButtonInteractor : public UIInteractor
{
public:
    // UIInteractor�C���^�[�t�F�[�X�̎���
    void UpdateInteraction(UIElement* owner) override;

private:
    bool m_previousMouseDown = false;
};