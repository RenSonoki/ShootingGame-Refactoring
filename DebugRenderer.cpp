#include "DebugRenderer.h"

DebugRenderer& DebugRenderer::GetInstance()
{
    static DebugRenderer instance;
    return instance;
}

void DebugRenderer::AddLine(const VECTOR& start, const VECTOR& end, unsigned int color)
{
    m_lines.push_back({ start, end, color });
}

void DebugRenderer::AddSphere(const VECTOR& center, float radius, unsigned int color)
{
    m_spheres.push_back({ center, radius, color });
}

void DebugRenderer::AddString(int x, int y, const std::string& text, unsigned int color)
{
    m_strings.push_back({ x, y, text, color });
}

#include <tchar.h> // Include this header for TCHAR compatibility

void DebugRenderer::RenderAll()
{
    // 3D�}�`��`�悷��O��Z�o�b�t�@��L����
    SetUseZBuffer3D(TRUE);
    SetWriteZBuffer3D(TRUE);

    for (const auto& line : m_lines)
    {
        DrawLine3D(line.start, line.end, line.color);
    }
    for (const auto& sphere : m_spheres)
    {
        DrawSphere3D(sphere.center, sphere.radius, 16, sphere.color, sphere.color, FALSE);
    }

    // 2D�e�L�X�g��`�悷��O��2D���[�h�ɐ؂�ւ�
    SetUseZBuffer3D(FALSE);
    SetWriteZBuffer3D(FALSE);
    // (�K�v�Ȃ�SetupCamera_Ortho�Ȃǂ��Ă�)

    for (const auto& str : m_strings)
    {
        // Convert std::string to TCHAR-compatible string
        #ifdef UNICODE
            std::wstring tcharText = std::wstring(str.text.begin(), str.text.end());
            DrawFormatString(str.x, str.y, str.color, tcharText.c_str());
        #else
            DrawFormatString(str.x, str.y, str.color, str.text.c_str());
        #endif
    }

    // ���̃t���[���̂��߂Ƀ��N�G�X�g���N���A
    m_lines.clear();
    m_spheres.clear();
    m_strings.clear();
}