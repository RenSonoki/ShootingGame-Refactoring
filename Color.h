#pragma once

// �F���������߂̃w���p�[�֐��Q���`
namespace ColorUtil
{
    // C++17�ȍ~�ł̓C�����C���ϐ��Ƃ��ăw�b�_�ɒ��ڒ�`�ł��܂�
    inline constexpr unsigned int White = 0xFFFFFFFF;
    inline constexpr unsigned int Black = 0x00000000;
    inline constexpr unsigned int Red = 0xFFFF0000;
    inline constexpr unsigned int Green = 0xFF00FF00;
    inline constexpr unsigned int Blue = 0xFF0000FF;

    // unsigned int �̃J���[�l����R����(0-255)�𒊏o����
    inline constexpr unsigned char GetR(unsigned int color)
    {
        return static_cast<unsigned char>((color >> 16) & 0xFF);
    }

    // G����(0-255)�𒊏o����
    inline constexpr unsigned char GetG(unsigned int color)
    {
        return static_cast<unsigned char>((color >> 8) & 0xFF);
    }

    // B����(0-255)�𒊏o����
    inline constexpr unsigned char GetB(unsigned int color)
    {
        return static_cast<unsigned char>(color & 0xFF);
    }
}