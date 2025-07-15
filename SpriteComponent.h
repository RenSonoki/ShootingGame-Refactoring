#pragma once

#include "UIComponent.h"
#include "SpriteRenderer.h"
#include <string>

// SpriteRenderer�����AUI�V�X�e���ɓ������邽�߂̃R���|�[�l���g
class SpriteComponent : public UIComponent
{
public:
    explicit SpriteComponent(const std::wstring& imagePath);
    virtual ~SpriteComponent() = default;

    // UIComponent�̏������z�֐��ł���Draw���I�[�o�[���C�h
    void Draw(int targetScreen = -1) override;

    // ������SpriteRenderer�ɃA�N�Z�X�������ꍇ�i�C�Ӂj
    const SpriteRenderer& GetRenderer() const { return m_renderer; }
    SpriteRenderer& GetRenderer() { return m_renderer; }

private:
    // SpriteRenderer�������o�[�Ƃ��ĕێ��ihas-a�֌W�j
    SpriteRenderer m_renderer;
};