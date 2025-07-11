#pragma once

#include "UIComponent.h"
#include <vector>
#include <memory>

// UIComponent �𕡐��܂Ƃ߂Ę_���I�ɃO���[�v�����邽�߂̃p�l��
class UIPanel : public UIComponent
{
public:
    UIPanel();
    virtual ~UIPanel() = default;

    // �qUI�R���|�[�l���g��ǉ�
    void AddChild(const std::shared_ptr<UIComponent>& child);

    // �q�v�f�̃��X�g���擾�i�ǂݎ���p�j
    const std::vector<std::shared_ptr<UIComponent>>& GetChildren() const;

    // �p�l�����g�̕`�揈���i��������΁j
    void Draw(int targetScreen = -1) override;

    // �\������i���g�ƁA�Ǘ�����q�v�f�̕\����Ԃ��ꊇ�Ő؂�ւ���j
    void SetVisible(bool visible) override;

private:
    // �p�l�����_���I�ɕێ�����q�v�f�̃��X�g
    std::vector<std::shared_ptr<UIComponent>> m_children;
};