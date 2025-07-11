#pragma once

#include "ResourceTraits.h"
#include <unordered_map>
#include <string>
#include <memory>
#include <mutex>
#include <Windows.h>

// �ėp���\�[�X�}�l�[�W���[ (Singleton)
class ResourceManager
{
public:
    static ResourceManager& Instance();

    // �e���v���[�g���ꉻ���g���A�^���ƂɌʂ̎������`
    template<typename T>
    int Get(const std::wstring& path);

    void ClearAll();

private:
    ResourceManager() = default;
    ~ResourceManager();
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    // ���O�t���̌ʂ̃L���b�V��
    std::unordered_map<std::wstring, int> m_modelCache;
    std::unordered_map<std::wstring, int> m_imageCache;
    std::unordered_map<std::wstring, int> m_soundCache;

    std::mutex m_resourceMutex;
};

// --- �e���v���[�g���ꉻ�̐錾 ---
// ����ɂ��AGet<ModelTag>(...) �� Get<ImageTag>(...) �ŁA
// �قȂ�����i�L���b�V���j���g����悤�ɂȂ�

template<>
int ResourceManager::Get<ModelTag>(const std::wstring& path);

template<>
int ResourceManager::Get<ImageTag>(const std::wstring& path);

template<>
int ResourceManager::Get<SoundTag>(const std::wstring& path);