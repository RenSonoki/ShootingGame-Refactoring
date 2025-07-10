#include "ResourceManager.h"

ResourceManager& ResourceManager::Instance()
{
    static ResourceManager instance;
    return instance;
}

ResourceManager::~ResourceManager()
{
    ClearAll();
}

void ResourceManager::ClearAll()
{
    std::lock_guard<std::mutex> lock(m_mutex);

    // �^�v���̊e�L���b�V���ɑ΂��ăN���A���������s
    for_each_in_tuple([this](auto& cache)
        {
        using CacheType = std::decay_t<decltype(cache)>;
        using T = typename CacheType::key_type; // ����� std::wstring
        using U = typename CacheType::mapped_type; // ����� HandleType

        // Traits����肷�邽�߂Ɍ^��񂪕K�v�����A���ڂ͎��Ȃ��B
        // �����ł̓^�v���̃C���f�b�N�X����^�𔻒肷��w���p�[���g���B
        // ... ���̕����͔��ɕ��G�ɂȂ邽�߁A���ȒP�Ȏ����ɐ؂�ւ��܂��B

        // �ȒP�Ȏ����F�^�v���̊e�v�f�𒼐ڃN���A����
        // �����I�Ɍ^���������炱������ŏC������K�v�����邪�A�ǐ�������
        });

    // �S�Ẵ��f�������
    for (auto const& [path, handle] : std::get<Cache<ModelTag>>(m_caches)) {
        ResourceTraits<ModelTag>::Unload(handle);
    }
    std::get<Cache<ModelTag>>(m_caches).clear();

    // �S�Ẳ摜�����
    for (auto const& [path, handle] : std::get<Cache<ImageTag>>(m_caches)) {
        ResourceTraits<ImageTag>::Unload(handle);
    }
    std::get<Cache<ImageTag>>(m_caches).clear();

    // �S�ẴT�E���h�����
    for (auto const& [path, handle] : std::get<Cache<SoundTag>>(m_caches)) {
        ResourceTraits<SoundTag>::Unload(handle);
    }
    std::get<Cache<SoundTag>>(m_caches).clear();
}

// for_each_in_tuple �̎����́AC++17�� fold expression �Ȃǂ��g�����Y��ɏ�����炵��
// �w�K�����ǐ��ƃV���v�����̂��߂ɍ����ClearAll()�ɒ��ڋL�q���܂����B