#pragma once

#include "ResourceTraits.h"
#include <unordered_map>
#include <string>
#include <memory>
#include <mutex>
#include <Windows.h>

// 汎用リソースマネージャー (Singleton)
class ResourceManager
{
public:
    static ResourceManager& Instance();

    // テンプレート特殊化を使い、型ごとに個別の実装を定義
    template<typename T>
    int Get(const std::wstring& path);

    void ClearAll();

private:
    ResourceManager() = default;
    ~ResourceManager();
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    // 名前付きの個別のキャッシュ
    std::unordered_map<std::wstring, int> m_modelCache;
    std::unordered_map<std::wstring, int> m_imageCache;
    std::unordered_map<std::wstring, int> m_soundCache;

    std::mutex m_resourceMutex;
};

// --- テンプレート特殊化の宣言 ---
// これにより、Get<ModelTag>(...) や Get<ImageTag>(...) で、
// 異なる実装（キャッシュ）が使われるようになる

template<>
int ResourceManager::Get<ModelTag>(const std::wstring& path);

template<>
int ResourceManager::Get<ImageTag>(const std::wstring& path);

template<>
int ResourceManager::Get<SoundTag>(const std::wstring& path);