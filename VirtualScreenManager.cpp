#define NOMINMAX
#include <windows.h> 
#include <stdexcept>
#include <algorithm>
#include "VirtualScreenManager.h"

// �ÓI�����o��`
int VirtualScreenManager::s_virtualWidth = 0;
int VirtualScreenManager::s_virtualHeight = 0;
int VirtualScreenManager::s_virtualScreenHandle = -1;
bool VirtualScreenManager::s_initialized = false;
VirtualScreenManager::ScalingMode VirtualScreenManager::s_scalingMode = VirtualScreenManager::ScalingMode::KeepAspect;
unsigned int VirtualScreenManager::s_backgroundColor = 0x00FFFF; // �V�A��

// �ǉ����������o�ϐ��̏�����
Vector2I VirtualScreenManager::s_windowSize = Vector2I(-1, -1); // �����������
Vector2I VirtualScreenManager::s_drawOffset = Vector2I(0, 0);
Vector2F VirtualScreenManager::s_scaleRatio = Vector2F(1.0f, 1.0f);

void VirtualScreenManager::Init(int virtualW, int virtualH, ScalingMode mode, unsigned int backgroundColor)
{
    if (s_initialized)
    {
        // ���łɏ������ς݂̏ꍇ�͉������Ȃ����A�G���[�𓊂���
        return;
    }

    if (GetColorBitDepth() == 0)
    {
        throw std::runtime_error("DxLib_Init()���O��VirtualScreenManager::Init()���Ă΂�܂���");
    }

    s_virtualWidth = virtualW;
    s_virtualHeight = virtualH;
    s_scalingMode = mode;
    s_backgroundColor = backgroundColor;

    s_virtualScreenHandle = MakeScreen(s_virtualWidth, s_virtualHeight, TRUE);
    if (s_virtualScreenHandle == -1) 
    {
        throw std::runtime_error("���z��ʂ̍쐬�Ɏ��s���܂���");
    }

    s_initialized = true;

    // �����p�����[�^�v�Z
    UpdateScalingParameters();
}

void VirtualScreenManager::BeginDraw()
{
    if (!s_initialized) return;

    SetDrawScreen(s_virtualScreenHandle);
    // �w�i�F��Z�o�b�t�@���N���A
    // NOTE: WinMain����ClearDrawScreen()��SetBackgroundColor()�͕s�v�ɂȂ�܂�
    ClearDrawScreen();
    DrawBox(0, 0, s_virtualWidth, s_virtualHeight, s_backgroundColor, TRUE);
}

void VirtualScreenManager::EndDraw()
{
    if (!s_initialized) return;

    // �E�B���h�E�T�C�Y���ύX���ꂽ���`�F�b�N���A�K�v�Ȃ�p�����[�^���X�V
    UpdateScalingParameters();

    // �`�����o�b�N�o�b�t�@��
    SetDrawScreen(DX_SCREEN_BACK);

    // �v�Z�ς݂̃p�����[�^���g���ĕ`��
    int drawW = static_cast<int>(s_virtualWidth * s_scaleRatio.x);
    int drawH = static_cast<int>(s_virtualHeight * s_scaleRatio.y);

    DrawExtendGraph(s_drawOffset.x, s_drawOffset.y, s_drawOffset.x + drawW, s_drawOffset.y + drawH, s_virtualScreenHandle, TRUE);
}

void VirtualScreenManager::UpdateScalingParameters()
{
    int currentWindowW, currentWindowH;
    GetWindowSize(&currentWindowW, &currentWindowH);

    // �E�B���h�E�T�C�Y���ω����Ă��Ȃ���Ή������Ȃ�
	// NOTE: �����̖��ʂ�����邽�߁A�E�B���h�E�T�C�Y���ς�����Ƃ������X�V
    if (s_windowSize.x == currentWindowW && s_windowSize.y == currentWindowH)
    {
        return;
    }

    s_windowSize.x = currentWindowW;
    s_windowSize.y = currentWindowH;

    if (s_scalingMode == ScalingMode::StretchToFill)
    {
        s_scaleRatio.x = s_windowSize.x / static_cast<float>(s_virtualWidth);
        s_scaleRatio.y = s_windowSize.y / static_cast<float>(s_virtualHeight);
        s_drawOffset = Vector2I(0, 0);
    }
    else if (s_scalingMode == ScalingMode::KeepAspect)
    {
        float scale = std::min(s_windowSize.x / static_cast<float>(s_virtualWidth),
            s_windowSize.y / static_cast<float>(s_virtualHeight));
        s_scaleRatio.x = scale;
        s_scaleRatio.y = scale;

        int drawW = static_cast<int>(s_virtualWidth * scale);
        int drawH = static_cast<int>(s_virtualHeight * scale);
        s_drawOffset.x = (s_windowSize.x - drawW) / 2;
        s_drawOffset.y = (s_windowSize.y - drawH) / 2;
    }
}

Vector2I VirtualScreenManager::ConvertMousePositionToVirtual()
{
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);

    int relX = mouseX - s_drawOffset.x;
    int relY = mouseY - s_drawOffset.y;

    return Vector2I(
        static_cast<int>(relX / s_scaleRatio.x),
        static_cast<int>(relY / s_scaleRatio.y)
    );
}

Vector2I VirtualScreenManager::ConvertVirtualToScreen(const Vector2I& virtualPos)
{
    return Vector2I(
        static_cast<int>(s_drawOffset.x + virtualPos.x * s_scaleRatio.x),
        static_cast<int>(s_drawOffset.y + virtualPos.y * s_scaleRatio.y)
    );
}

int VirtualScreenManager::GetVirtualWidth() { return s_virtualWidth; }
int VirtualScreenManager::GetVirtualHeight() { return s_virtualHeight; }
int VirtualScreenManager::GetVirtualScreenHandle() { return s_virtualScreenHandle; }
bool VirtualScreenManager::IsInitialized() { return s_initialized; }
VirtualScreenManager::ScalingMode VirtualScreenManager::GetScalingMode() { return s_scalingMode; }