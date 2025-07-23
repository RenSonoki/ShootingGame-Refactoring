#pragma once
#include <vector>
#include <string>
#include <DxLib.h>

/**
 * @class DebugRenderer
 * @brief �f�o�b�O�p�̐}�`�`����Ǘ�����V���O���g��
 */
class DebugRenderer
{
public:
    static DebugRenderer& GetInstance();

    // �R�s�[�ƃ��[�u�͋֎~
    DebugRenderer(const DebugRenderer&) = delete;
    DebugRenderer& operator=(const DebugRenderer&) = delete;

    // --- �`�惊�N�G�X�g�p���\�b�h ---
    void AddLine(const VECTOR& start, const VECTOR& end, unsigned int color);
    void AddSphere(const VECTOR& center, float radius, unsigned int color);
    void AddString(int x, int y, const std::string& text, unsigned int color);

    // ���t���[���̍Ō�ɁA���N�G�X�g���ꂽ�}�`��S�ĕ`�悷��
    void RenderAll();

private:
    DebugRenderer() = default;

    // �`�惊�N�G�X�g�𗭂߂Ă������߂̍\����
    struct LineInfo { VECTOR start, end; unsigned int color; };
    struct SphereInfo { VECTOR center; float radius; unsigned int color; };
    struct StringInfo { int x, y; std::string text; unsigned int color; };

    std::vector<LineInfo> m_lines;
    std::vector<SphereInfo> m_spheres;
    std::vector<StringInfo> m_strings;
};