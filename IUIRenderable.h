#pragma once

// UI�`��p�C���^�[�t�F�[�X
class IUIRenderable
{
public:
    virtual ~IUIRenderable() = default;
    virtual void Draw() const = 0; // const �ɓ���
};