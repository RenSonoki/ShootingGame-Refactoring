#pragma once

// UI�`��p�C���^�[�t�F�[�X
class IUIRenderable
{
public:
    virtual ~IUIRenderable() = default;
    virtual void Draw(int targetScreen = -1) = 0; // -1: DX_SCREEN_BACK �Ȃ�
};