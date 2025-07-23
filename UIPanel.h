#pragma once
#include "UIElement.h"
#include <vector>
#include <memory>

// UI�v�f���K�w�I�ɃO���[�v�����邽�߂̃p�l���N���X
class UIPanel : public UIElement
{
public:
    UIPanel();
    virtual ~UIPanel();

    void AddChild(std::unique_ptr<UIElement> child);
    const std::vector<std::unique_ptr<UIElement>>& GetChildren() const;

    // --- UIElement�̉��z�֐����I�[�o�[���C�h ---
    void UpdateLogic(float deltaTime) override; // �� �C���_: deltaTime������ǉ�
    void UpdateInteraction() override;          // �� �ǉ�: Interaction�̍X�V���I�[�o�[���C�h
    void Draw() const override;
    void SetVisible(bool visible) override;

protected:
    std::vector<std::unique_ptr<UIElement>> m_children;

    // �� ���P��: Z�I�[�_�[���ύX���ꂽ���������t���O
    bool m_isZOrderDirty = false;
};
