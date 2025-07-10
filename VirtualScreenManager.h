#pragma once

#include "Vector2I.h"
#include "Vector2F.h"
#include <DxLib.h>

class VirtualScreenManager
{
public:
	// �X�P�[�����O���[�h�̗񋓌^
    enum class ScalingMode
    {
        StretchToFill,
        KeepAspect
    };

    // ����������
    // NOTE: �w�i�F���w��ł���悤�ɕύX
    static void Init(int virtualW, int virtualH, ScalingMode mode = ScalingMode::KeepAspect, unsigned int backgroundColor = 0x00FFFF);

    // �`��J�n�i���̒��ŉ�ʃN���A���s���j
    static void BeginDraw();

    // �`��I���Ǝ���ʂւ̓]��
    static void EndDraw();

    // ���W�ϊ����\�b�h
    static Vector2I ConvertMousePositionToVirtual();
    static Vector2I ConvertVirtualToScreen(const Vector2I& virtualPos);

    // �Q�b�^�[
    static int GetVirtualWidth();
    static int GetVirtualHeight();
    static int GetVirtualScreenHandle();
    static bool IsInitialized();
    static ScalingMode GetScalingMode();

private:
    VirtualScreenManager() = delete;

    // �X�P�[�����O�p�����[�^���X�V����w���p�[�֐�
    static void UpdateScalingParameters();

    // �ÓI�����o�ϐ�
    static int s_virtualWidth;
    static int s_virtualHeight;
    static int s_virtualScreenHandle;
    static bool s_initialized;
    static ScalingMode s_scalingMode;
    static unsigned int s_backgroundColor;

    static Vector2I s_windowSize;    // ���݂̃E�B���h�E�T�C�Y��ێ�
    static Vector2I s_drawOffset;    // �`��I�t�Z�b�g
	static Vector2F s_scaleRatio;    // XY���ꂼ��̃X�P�[�����O��(StretchToFill�ł̃X�P�[�����O����ێ�����)
};