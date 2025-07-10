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

    // タプルの各キャッシュに対してクリア処理を実行
    for_each_in_tuple([this](auto& cache)
        {
        using CacheType = std::decay_t<decltype(cache)>;
        using T = typename CacheType::key_type; // これは std::wstring
        using U = typename CacheType::mapped_type; // これは HandleType

        // Traitsを特定するために型情報が必要だが、直接は取れない。
        // ここではタプルのインデックスから型を判定するヘルパーを使う。
        // ... この部分は非常に複雑になるため、より簡単な実装に切り替えます。

        // 簡単な実装：タプルの各要素を直接クリアする
        // 将来的に型が増えたらここを手で修正する必要があるが、可読性が高い
        });

    // 全てのモデルを解放
    for (auto const& [path, handle] : std::get<Cache<ModelTag>>(m_caches)) {
        ResourceTraits<ModelTag>::Unload(handle);
    }
    std::get<Cache<ModelTag>>(m_caches).clear();

    // 全ての画像を解放
    for (auto const& [path, handle] : std::get<Cache<ImageTag>>(m_caches)) {
        ResourceTraits<ImageTag>::Unload(handle);
    }
    std::get<Cache<ImageTag>>(m_caches).clear();

    // 全てのサウンドを解放
    for (auto const& [path, handle] : std::get<Cache<SoundTag>>(m_caches)) {
        ResourceTraits<SoundTag>::Unload(handle);
    }
    std::get<Cache<SoundTag>>(m_caches).clear();
}

// for_each_in_tuple の実装は、C++17の fold expression などを使うと綺麗に書けるらしい
// 学習中かつ可読性とシンプルさのために今回はClearAll()に直接記述しました。