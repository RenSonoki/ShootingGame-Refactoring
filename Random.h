#pragma once
#include <random>
#include <mutex>

// �����_���������N���X
class Random
{
public:
    static Random& GetInstance();

	// �R�s�[�ƃ��[�u���֎~(�V���O���g���p�^�[���̂���)
    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;

    // �w��͈͂̐����𐶐� (�X���b�h�Z�[�t)
    int GetInt(int min, int max);

    // �w��͈͂̕��������_���𐶐� (�X���b�h�Z�[�t)
    float GetFloat(float min, float max);

private:
    // �R���X�g���N�^�ŃV�[�h��������
    Random();

    std::mt19937 m_engine;
    std::mutex m_mutex;
};