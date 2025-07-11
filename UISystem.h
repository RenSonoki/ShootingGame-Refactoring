#pragma once

#include <vector>
#include <memory>
#include <string>
#include <algorithm>

// �O���錾
class Entity;
class UIComponent;
class IUILogicUpdatable;
class IUIInteractable;

// UIComponent�����G���e�B�e�B���Ǘ����A�X�V�E�`��EZ�\�[�g���s���V�X�e��
class UISystem
{
public:
    UISystem() = default;

    // UI�����G���e�B�e�B�̓o�^�E����
    void RegisterEntity(const std::shared_ptr<Entity>& entity);
    void UnregisterEntity(const std::shared_ptr<Entity>& entity);

    // �Ǘ����̑SUI�R���|�[�l���g�̃��W�b�N�X�V
    void Update();
    // �Ǘ����̑SUI�R���|�[�l���g��`��iZ�\�[�g��j
    void Draw(int targetScreen = -1);

    // �S�G���e�B�e�B�i�ƃR���|�[�l���g�j���N���A
    void Clear();

    // UIManager���`�揇�����肷�邽�߂́u���C���[�[�x�v��ݒ�
    void SetLayerDepth(int depth);
    int GetLayerDepth() const;

private:
    // �`�揇�̃\�[�g�����s
    void SortComponents();
    // �Ǘ��Ώۂ̃G���e�B�e�B����AUI�R���|�[�l���g���Ď��W����
    void RefreshComponents();

    // Entity�ւ̎�Q��(weak_ptr)��ێ����A���L���̏z��h��
    std::vector<std::weak_ptr<Entity>> m_entities;

    // �`���X�V�̂��߂ɃL���b�V�����ꂽUIComponent�̃��X�g
    std::vector<std::shared_ptr<UIComponent>> m_cachedComponents;

    // ���X�g�̍č\�z�ƍă\�[�g���K�v���������t���O
    bool m_isDirty = true;

    // UIManager���ł̕`�揇�����肷��[�x
    int m_layerDepth = 0;
};