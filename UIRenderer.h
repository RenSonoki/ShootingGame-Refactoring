#pragma once
class UIElement;

// �u�ǂ̂悤�ɕ`�悷�邩�v�Ƃ����U�镑�����`����C���^�[�t�F�[�X
class UIRenderer
{
public:
    virtual ~UIRenderer() = default;
    virtual void Draw(const UIElement* owner) const = 0;
};