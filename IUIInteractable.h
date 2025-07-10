#pragma once

// UI�̃C���^���N�V�������Ǘ�����C���^�[�t�F�[�X
class IUIInteractable
{
public:
    virtual ~IUIInteractable() = default;
    virtual void UpdateInteraction() = 0;
    virtual void OnClick() = 0;
    virtual void OnHover() {}
};