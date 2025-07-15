#pragma once
#include "ResourceTraits.h"
#include <unordered_map>
#include <string>
#include <memory>
#include <mutex>
#include <tuple>
#include <Windows.h>

// ����̂P��ނ̃��\�[�X���Ǘ�����ėp�L���b�V���N���X
template<typename Tag>
class Cache
{
public:
    using Traits = ResourceTraits<Tag>;
    using HandleType = typename Traits::HandleType;

    // �L���b�V�����烊�\�[�X���擾�i�Ȃ���΃��[�h�j����
    HandleType Get(const std::wstring& path)
    {
        // NOTE: ���̎����ł�ResourceManager���ňꊇ���b�N���Ă��܂����A
        //       ������Mutex����������΁A��藱�x�ׂ̍������b�N���\�ł��B
        auto it = m_data.find(path);
        if (it != m_data.end())
        {
            return it->second;
        }

        HandleType handle = Traits::Load(path);
        if (handle != -1)
        {
            m_data[path] = handle;
        }
        else
        {
            OutputDebugStringW((L"[Resource Load Failed] " + path + L"\n").c_str());
        }
        return handle;
    }

    // ���̃L���b�V�����ێ�����S�Ẵ��\�[�X���������
    void Clear()
    {
        for (auto const& [path, handle] : m_data)
        {
            Traits::Unload(handle);
        }
        m_data.clear();
    }
private:
    std::unordered_map<std::wstring, HandleType> m_data;
};


// �ėp���\�[�X�}�l�[�W���[ (Singleton)
class ResourceManager
{
public:
    static ResourceManager& Instance();

    // �e���v���[�g���ꉻ���s�v�ɂȂ�A�P��̔ėp���\�b�h�ɂȂ�
    template<typename Tag>
    typename ResourceTraits<Tag>::HandleType Get(const std::wstring& path);

    void ClearAll();

private:
    ResourceManager() = default;
    ~ResourceManager();
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    // --- �Ǘ����郊�\�[�X�̎�ނ������Œ�` ---
    // NOTE: �V�������\�[�X��ǉ�����ꍇ�A����tuple�� Cache<NewTag> ��ǉ����邾����OK�I
    using AllCaches = std::tuple<
        Cache<ModelTag>,
        Cache<ImageTag>,
        Cache<SoundTag>
        // Cache<EffectTag>,
        // Cache<FontTag> ...
    >;

    AllCaches m_allCaches;
    std::mutex m_resourceMutex;
};


// --- �e���v���[�g�����i�w�b�_�ɋL�q�j ---
template<typename Tag>
typename ResourceTraits<Tag>::HandleType ResourceManager::Get(const std::wstring& path)
{
    std::lock_guard<std::mutex> lock(m_resourceMutex);

    // tuple����ATag�ɑΉ�����Cache�����o����Get���Ă�
    return std::get<Cache<Tag>>(m_allCaches).Get(path);
}