#pragma once

#include "IUIVisible.h"
#include "IUIRenderable.h"
#include "IUILogicUpdatable.h"
#include "IUITransformable.h"

// �K�{��UI�@�\���܂Ƃ߂������C���^�[�t�F�[�X
// ���̂��̂Ɛ݌v�v�z�͈قȂ邪�A�K�w�\���������̂ɂ͗L���ł���
class IUIElement :
    public IUIVisible,
    public IUIRenderable,
    public IUILogicUpdatable,
    public IUITransformable
{
public:
    virtual ~IUIElement() = default;

    // �K�{�����v�f�F�\������E�`��E���W�b�N�X�V�ETransform����
};