#define NOMINMAX
#include "VirtualScreenManager.h"
#include <DxLib.h>
#include <stdexcept>
#include <algorithm>

// ���̊֐������߂ČĂ΂ꂽ�Ƃ��Ɉ�x�����C���X�^���X�����������
VirtualScreenManager& VirtualScreenManager::GetInstance()
{
    static VirtualScreenManager instance;
    return instance;
}

void VirtualScreenManager::Init(int virtualW, int virtualH, ScalingMode mode, unsigned int backgroundColor)
{
    if (m_initialized)
    {
        return; // ���łɏ������ς�
    }

    if (GetColorBitDepth() == 0)
    {
        throw std::runtime_error("DxLib_Init()���O��VirtualScreenManager::Init()���Ă΂�܂���");
    }

    m_virtualWidth = virtualW;
    m_virtualHeight = virtualH;
    m_scalingMode = mode;
    m_backgroundColor = backgroundColor;

    m_virtualScreenHandle = MakeScreen(m_virtualWidth, m_virtualHeight, TRUE);
    if (m_virtualScreenHandle == -1)
    {
        throw std::runtime_error("���z��ʂ̍쐬�Ɏ��s���܂���");
    }

    m_initialized = true;

    // �����p�����[�^���v�Z
    UpdateScalingParameters();
}

void VirtualScreenManager::BeginDraw()
{
    if (!m_initialized) return;

    SetDrawScreen(m_virtualScreenHandle);
    ClearDrawScreen(); // Z�o�b�t�@�Ȃǂ��N���A
    DrawBox(0, 0, m_virtualWidth, m_virtualHeight, m_backgroundColor, TRUE);
}

void VirtualScreenManager::EndDraw()
{
    if (!m_initialized) return;

    // ���t���[���A�E�B���h�E�T�C�Y�̕ύX���`�F�b�N
    UpdateScalingParameters();

    // �`�����o�b�N�o�b�t�@�i���ۂ̉�ʁj�ɖ߂�
    SetDrawScreen(DX_SCREEN_BACK);

    // �v�Z�ς݂̃p�����[�^���g���ĉ��z�X�N���[��������ʂɕ`��
    int drawW = static_cast<int>(m_virtualWidth * m_scaleRatio.x);
    int drawH = static_cast<int>(m_virtualHeight * m_scaleRatio.y);

    DrawExtendGraph(m_drawOffset.x, m_drawOffset.y, m_drawOffset.x + drawW, m_drawOffset.y + drawH, m_virtualScreenHandle, TRUE);
}

void VirtualScreenManager::UpdateScalingParameters()
{
    int currentWindowW, currentWindowH;
    GetWindowSize(&currentWindowW, &currentWindowH);

    // `std::optional`���g���A�E�B���h�E�T�C�Y���ύX���ꂽ���`�F�b�N
    if (m_windowSize.has_value() && m_windowSize->x == currentWindowW && m_windowSize->y == currentWindowH)
    {
        return; // �T�C�Y�ύX���Ȃ���Ή������Ȃ�
    }

    m_windowSize = Vector2I(currentWindowW, currentWindowH);

    if (m_scalingMode == ScalingMode::StretchToFill)
    {
        m_scaleRatio.x = m_windowSize->x / static_cast<float>(m_virtualWidth);
        m_scaleRatio.y = m_windowSize->y / static_cast<float>(m_virtualHeight);
        m_drawOffset = { 0, 0 };
    }
    else // KeepAspect
    {
        float scale = std::min(m_windowSize->x / static_cast<float>(m_virtualWidth),
            m_windowSize->y / static_cast<float>(m_virtualHeight));
        m_scaleRatio = { scale, scale };

        int drawW = static_cast<int>(m_virtualWidth * scale);
        int drawH = static_cast<int>(m_virtualHeight * scale);
        m_drawOffset.x = (m_windowSize->x - drawW) / 2;
        m_drawOffset.y = (m_windowSize->y - drawH) / 2;
    }
}

Vector2I VirtualScreenManager::ConvertMousePositionToVirtual()
{
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);

    int relX = mouseX - m_drawOffset.x;
    int relY = mouseY - m_drawOffset.y;

    return Vector2I(
        static_cast<int>(relX / m_scaleRatio.x),
        static_cast<int>(relY / m_scaleRatio.y)
    );
}

Vector2I VirtualScreenManager::ConvertVirtualToScreen(const Vector2I& virtualPos)
{
    return Vector2I(
        static_cast<int>(m_drawOffset.x + virtualPos.x * m_scaleRatio.x),
        static_cast<int>(m_drawOffset.y + virtualPos.y * m_scaleRatio.y)
    );
}

// --- �Q�b�^�[�̎��� ---
int VirtualScreenManager::GetVirtualWidth() const { return m_virtualWidth; }
int VirtualScreenManager::GetVirtualHeight() const { return m_virtualHeight; }
int VirtualScreenManager::GetVirtualScreenHandle() const { return m_virtualScreenHandle; }
bool VirtualScreenManager::IsInitialized() const { return m_initialized; }
VirtualScreenManager::ScalingMode VirtualScreenManager::GetScalingMode() const { return m_scalingMode; }