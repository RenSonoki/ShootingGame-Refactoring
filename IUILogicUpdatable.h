#pragma once

// UI�̃��W�b�N���X�V���邽�߂̃C���^�[�t�F�[�X
class IUILogicUpdatable
{
public:
    virtual ~IUILogicUpdatable() = default;
    virtual void UpdateLogic() = 0;
};