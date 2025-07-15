#pragma once
#include "UIElement.h"
#include <functional>
#include <string>

// �U�镑�����O�����i�ɈϏ�����A�f�[�^���S�̃{�^���N���X
class UIButton : public UIElement
{
public:
    enum class ButtonState { Normal, Hovered, Pressed };

    UIButton(const std::wstring& normalPath,
        const std::wstring& hoverPath = L"",
        const std::wstring& pressedPath = L"");

    // --- �O������g�����߂̃C���^�[�t�F�[�X ---
    void SetOnClick(std::function<void()> callback);

    // --- �V�X�e�������i���i�j����g���郁�\�b�h ---
    void InvokeOnClick();
    ButtonState GetState() const;
    void SetState(ButtonState newState);
    VECTOR2 GetBoundingSize() const override;

private:
    ButtonState m_state = ButtonState::Normal;
    std::function<void()> m_onClick;
};