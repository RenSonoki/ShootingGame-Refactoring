#pragma once
#include <string>
#include "Transform2D.h"
#include "Color.h"

namespace BlendMode
{
    constexpr int None = 0;
    constexpr int Alpha = 2;
    constexpr int Add = 1;
    constexpr int Subtract = 3;
}

/**
 * @class SpriteRenderer
 * @brief �ꖇ�̃X�v���C�g�摜�̕`��ɕK�v�ȃf�[�^�ƃ��W�b�N���J�v�Z��������N���X
 */
class SpriteRenderer
{
public:
    SpriteRenderer();
    explicit SpriteRenderer(const std::wstring& path);
    ~SpriteRenderer();

    // �R�s�[�͋֎~���A���[�u�i���L���̈ړ��j��������
    SpriteRenderer(const SpriteRenderer&) = delete;
    SpriteRenderer& operator=(const SpriteRenderer&) = delete;
    SpriteRenderer(SpriteRenderer&& other) noexcept;
    SpriteRenderer& operator=(SpriteRenderer&& other) noexcept;

    bool Load(const std::wstring& path);

    // �`�惁�\�b�h�i������Transform�݂̂ŃV���v���Ɂj
    void Draw(const Transform2D& transform) const;

    // --- �`��p�����[�^��ݒ肷��Z�b�^�[ ---
    void SetVisible(bool visible);
    void SetColor(unsigned int color);
    void SetBlendParam(int blendParam); // �u�����h�̋�����ݒ�

    // --- �Q�b�^�[ ---
    int GetOriginalWidth() const;
    int GetOriginalHeight() const;
    int GetHandle() const;

private:
    void Release(); // ����������܂Ƃ߂�w���p�[

    int m_handle;
    int m_originalWidth;
    int m_originalHeight;

    bool m_visible;
    unsigned int m_color;
    int m_blendParam; // �u�����h�̋���(0-255)
};