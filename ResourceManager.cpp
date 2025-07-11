#include "ResourceManager.h"
#include "DxLib.h"

ResourceManager& ResourceManager::Instance()
{
    static ResourceManager instance;
    return instance;
}

ResourceManager::~ResourceManager()
{
    ClearAll();
}

// --- 各リソースタイプごとの、Getメソッドの具体的な実装 ---

template<>
int ResourceManager::Get<ModelTag>(const std::wstring& path)
{
    std::lock_guard<std::mutex> lock(m_resourceMutex);

    // モデルキャッシュを検索
    auto it = m_modelCache.find(path);
    if (it != m_modelCache.end())
    {
        return it->second;
    }

    // なければロード
    int handle = ResourceTraits<ModelTag>::Load(path);
    if (handle != -1) {
        m_modelCache[path] = handle;
    }
    else {
        OutputDebugStringW((L"[Resource Load Failed] " + path + L"\n").c_str());
    }
    return handle;
}

template<>
int ResourceManager::Get<ImageTag>(const std::wstring& path)
{
    std::lock_guard<std::mutex> lock(m_resourceMutex);

    // イメージキャッシュを検索
    auto it = m_imageCache.find(path);
    if (it != m_imageCache.end()) {
        return it->second;
    }

    // なければロード
    int handle = ResourceTraits<ImageTag>::Load(path);
    if (handle != -1) {
        m_imageCache[path] = handle;
    }
    else {
        OutputDebugStringW((L"[Resource Load Failed] " + path + L"\n").c_str());
    }
    return handle;
}

template<>
int ResourceManager::Get<SoundTag>(const std::wstring& path)
{
    std::lock_guard<std::mutex> lock(m_resourceMutex);

    // サウンドキャッシュを検索
    auto it = m_soundCache.find(path);
    if (it != m_soundCache.end()) {
        return it->second;
    }

    // なければロード
    int handle = ResourceTraits<SoundTag>::Load(path);
    if (handle != -1) {
        m_soundCache[path] = handle;
    }
    else {
        OutputDebugStringW((L"[Resource Load Failed] " + path + L"\n").c_str());
    }
    return handle;
}


void ResourceManager::ClearAll()
{
    std::lock_guard<std::mutex> lock(m_resourceMutex);

    // 各キャッシュを解放
    for (auto const& [path, handle] : m_modelCache) {
        ResourceTraits<ModelTag>::Unload(handle);
    }
    m_modelCache.clear();

    for (auto const& [path, handle] : m_imageCache) {
        ResourceTraits<ImageTag>::Unload(handle);
    }
    m_imageCache.clear();

    for (auto const& [path, handle] : m_soundCache) {
        ResourceTraits<SoundTag>::Unload(handle);
    }
    m_soundCache.clear();
}