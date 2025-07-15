#pragma once
#include "Vector.h" // �e���v���[�g������Vector.h���C���N���[�h
#include <optional>   // std::optional ���g�p

// ���z�X�N���[���̊Ǘ��N���X
class VirtualScreenManager
{
public:
    enum class ScalingMode
    {
        StretchToFill,
        KeepAspect
    };

    // �B��̃C���X�^���X���擾���邽�߂̐ÓI���\�b�h
    static VirtualScreenManager& GetInstance();

    // �V���O���g���p�^�[���̂���@�Ƃ��āA�R�s�[�ƃ��[�u���֎~
    VirtualScreenManager(const VirtualScreenManager&) = delete;
    VirtualScreenManager& operator=(const VirtualScreenManager&) = delete;

    void Init(int virtualW, int virtualH, ScalingMode mode = ScalingMode::KeepAspect, unsigned int backgroundColor = 0x00FFFF);
    void BeginDraw();
    void EndDraw();

    Vector2I ConvertMousePositionToVirtual();
    Vector2I ConvertVirtualToScreen(const Vector2I& virtualPos);

    // �Q�b�^�[
    int GetVirtualWidth() const;
    int GetVirtualHeight() const;
    int GetVirtualScreenHandle() const;
    bool IsInitialized() const;
    ScalingMode GetScalingMode() const;

private:
    // private�R���X�g���N�^�ŁA�O������̒��ړI�ȃC���X�^���X�����֎~
    VirtualScreenManager() = default;

    void UpdateScalingParameters();

    // �����o�ϐ�
    int m_virtualWidth = 0;
    int m_virtualHeight = 0;
    int m_virtualScreenHandle = -1;
    bool m_initialized = false;
    ScalingMode m_scalingMode = ScalingMode::KeepAspect;
    unsigned int m_backgroundColor = 0x00FFFF;

    // `std::optional`�Łu�l���܂��Ȃ��v��Ԃ����S�ɕ\��
    std::optional<Vector2I> m_windowSize;

    Vector2I m_drawOffset = { 0, 0 };
    Vector2F m_scaleRatio = { 1.0f, 1.0f };
};