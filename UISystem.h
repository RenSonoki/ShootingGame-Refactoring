#pragma once

#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include "UIComponent.h"
#include "IUILogicUpdatable.h"

// �P���UI���C���[�i��FHUD�A�|�[�Y���j���[�j���Ǘ�����V�X�e��
class UISystem
{
public:
    UISystem() = default;

    // UI�R���|�[�l���g�̓o�^�E����
    void AddComponent(const std::shared_ptr<UIComponent>& component);
    void RemoveComponent(const std::shared_ptr<UIComponent>& component);

    // UI�̍X�V�E�`�惋�[�v
    void Update();
    void Draw(int targetScreen = -1);

    // UI�R���|�[�l���g�̎擾
    std::shared_ptr<UIComponent> GetComponentByName(const std::string& name) const;
    const std::vector<std::shared_ptr<UIComponent>>& GetComponents() const;

    // �S�R���|�[�l���g���N���A
    void Clear();

    // UIManager���`�揇�����肷�邽�߂́u���C���[�[�x�v��ݒ�
    void SetLayerDepth(int depth);
    int GetLayerDepth() const;

private:
    // Z�I�[�_�[�ł̃\�[�g�����s�iDraw�̒��ŕK�v�ɉ����ČĂ΂��j
    void SortByZOrder();

    std::vector<std::shared_ptr<UIComponent>> m_components;

    // Z�I�[�_�[�̍ă\�[�g���K�v���������t���O
    bool m_isSortNeeded = false;

    // UIManager���ł̕`�揇�����肷��[�x
    int m_layerDepth = 0;
};