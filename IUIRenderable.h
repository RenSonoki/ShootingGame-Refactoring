#pragma once

// UI�`��p�C���^�[�t�F�[�X
class IUIRenderable
{
public:
    virtual ~IUIRenderable() = default;
    virtual void Draw() = 0; // �����͕s�v�BRenderer�ɔC���邽�߁B
};