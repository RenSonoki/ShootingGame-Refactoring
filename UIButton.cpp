#include "UIButton.h"
#include "DxLib.h"
#include "VirtualScreenManager.h" // IsMouseOver�ŕK�v

UIButton::UIButton(const std::wstring& normalPath,
    const std::wstring& hoverPath,
    const std::wstring& pressedPath)
{
    // �eSpriteRenderer�ɉ摜�����[�h������
    m_rendererNormal.Load(normalPath);

    // �p�X����Ȃ�A�ʏ펞�̉摜���R�s�[���Ďg��
    m_rendererHover = hoverPath.empty() ? m_rendererNormal : SpriteRenderer(hoverPath);
    m_rendererPressed = pressedPath.empty() ? m_rendererNormal : SpriteRenderer(hoverPath);
}

void UIButton::UpdateInteraction()
{
    if (!IsVisible() || !IsActive())
    {
        // ��A�N�e�B�u���͏�Ԃ�Normal�ɖ߂�
        m_state = ButtonState::Normal;
        return;
    }

    bool isOver = IsMouseOver();
    bool isDown = (GetMouseInput() & MOUSE_INPUT_LEFT) != 0;

    if (isOver)
    {
        m_state = isDown ? ButtonState::Pressed : ButtonState::Hovered;

        // �}�E�X����ŁA�O�̃t���[���ŉ�����Ă��āA���t���[���ŗ����ꂽ�u�ԂɃN���b�N�C�x���g����
        if (m_previousMouseDown && !isDown && m_onClick)
        {
            m_onClick();
        }
    }
    else
    {
        m_state = ButtonState::Normal;
    }

    m_previousMouseDown = isDown;
}

void UIButton::Draw(int targetScreen)
{
    if (!IsVisible()) return;

    // ��Ԃɉ����āA�S����SpriteRenderer�ɕ`����˗����邾��
    const SpriteRenderer* rendererToUse = &m_rendererNormal;
    switch (m_state)
    {
    case ButtonState::Hovered:
        rendererToUse = &m_rendererHover;
        break;
    case ButtonState::Pressed:
        rendererToUse = &m_rendererPressed;
        break;
    default:
        break;
    }

    // SpriteRenderer��Draw�� Transform �𐳂��������Ă����
    rendererToUse->Draw(GetTransform(), true);
}

void UIButton::SetOnClick(std::function<void()> callback)
{
    m_onClick = std::move(callback);
}

UIButton::ButtonState UIButton::GetState() const
{
    return m_state;
}

bool UIButton::IsMouseOver() const
{
    // Transform2D �� Contains ���\�b�h���g���Đ��m�ȓ����蔻����s��
    Vector2I mousePosInt = VirtualScreenManager::ConvertMousePositionToVirtual();
    VECTOR2 mousePos = { (float)mousePosInt.x, (float)mousePosInt.y };

    // �{�^���̃T�C�Y�́A�ʏ펞�̉摜�̃T�C�Y����ɂ���
    VECTOR2 size = {
        (float)m_rendererNormal.GetOriginalWidth(),
        (float)m_rendererNormal.GetOriginalHeight()
    };

    return GetTransform().Contains(mousePos, size);
}