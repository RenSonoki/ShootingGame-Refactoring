#pragma once

// �O���錾
class UIElement;
class Transform2D;

// UI�v�f�̃A�j���[�V�����i���W�b�N�X�V�j�̐U�镑�����`����C���^�[�t�F�[�X
class UIAnimator
{
public:
    virtual ~UIAnimator() = default;

    /**
     * @brief �A�j���[�V�����̃��W�b�N���X�V���܂�
     * @param owner ���̃A�j���[�^�[�����L����UIElement
     * @param transform ����Ώۂ�Transform2D
     * @param deltaTime �O�t���[������̌o�ߎ���
     */
    virtual void Update(const UIElement* owner, Transform2D& transform, float deltaTime) = 0;
};