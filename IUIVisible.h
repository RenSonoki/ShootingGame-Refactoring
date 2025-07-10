#pragma once

// �\����ԊǗ��C���^�[�t�F�[�X
class IUIVisible
{
public:
    virtual ~IUIVisible() = default;

    virtual void SetVisible(bool visible) = 0;
    virtual bool IsVisible() const = 0;
};
