#pragma once
#include <random>

// C++11�ȍ~�̕W�����C�u�������g�p���ė����𐶐�����N���X
// NOTE: �]���� rand() �֐��̓}���`�X���b�h���ł͈��S�łȂ��񐄏��̂���
class Random
{
private:
    // �����Z���k�E�c�C�X�^�[�@�ɂ�闐�������G���W��
    static std::mt19937 engine;

public:
    // ������
    static void Init()
    {
        // ���ݎ������V�[�h�Ƃ��ăG���W����������
        std::random_device rd;
        engine.seed(rd());
    }

    // �w��͈͂̐����𐶐�
    static int GetInt(int min, int max)
    {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(engine);
    }

    // �w��͈͂̕��������_���𐶐�
    static float GetFloat(float min, float max)
    {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(engine);
    }
};

// �ÓI�����o�ϐ��̎��̂��` (Random.cpp �ɋL�q)
// std::mt19937 Random::engine;