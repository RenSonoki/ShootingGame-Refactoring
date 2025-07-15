#include "Random.h"

Random& Random::GetInstance()
{
    static Random instance;
    return instance;
}

// private�R���X�g���N�^���ŁA�ŏ��̃C���X�^���X�������Ɉ�x�����V�[�h
Random::Random()
{
    std::random_device rd;
    m_engine.seed(rd());
}

int Random::GetInt(int min, int max)
{
    // m_mutex�����̃X�R�[�v�̊ԁAm_engine�ւ̃A�N�Z�X��ی삷��
	// NOTE: thread_local���g���ăX���b�h���Ƃɗ���������������@������
    std::lock_guard<std::mutex> lock(m_mutex);
    std::uniform_int_distribution<int> dist(min, max);
    return dist(m_engine);
}

float Random::GetFloat(float min, float max)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    std::uniform_real_distribution<float> dist(min, max);
    return dist(m_engine);
}