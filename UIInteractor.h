#pragma once
class UIElement;

// �u���[�U�[����ɂǂ��������邩�v�Ƃ����U�镑�����`����C���^�[�t�F�[�X
class UIInteractor
{
public:
    virtual ~UIInteractor() = default;
    virtual void UpdateInteraction(UIElement* owner) = 0;
};

