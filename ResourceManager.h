#pragma once

#include "ResourceTraits.h"
#include <unordered_map>
#include <string>
#include <memory>
#include <tuple>
#include <mutex>
#include <Windows.h> // OutputDebugStringW

// 汎用リソースマネージャー
// NOTE: シングルトンパターンを使用して、アプリケーション全体で一つのインスタンスを共有
// NOTE: フライウェイトパターンを使用して、同じリソースの重複ロードを防ぐ
class ResourceManager
{
public:
    static ResourceManager& Instance();

    // テンプレート化されたリソース取得メソッド
    template<typename T>
    typename ResourceTraits<T>::HandleType Get(const std::wstring& path)
    {
        // 対応するキャッシュを取得
        auto& cache = getCache<T>();

        std::lock_guard<std::mutex> lock(m_mutex);

        // キャッシュ内に存在するか検索
        auto it = cache.find(path);
        if (it != cache.end())
        {
            return it->second; // あればそれを返す
        }

        // なければロード
        auto handle = ResourceTraits<T>::Load(path);
        if (handle == -1) {
            OutputDebugStringW((L"[Resource Load Failed] " + path + L"\n").c_str());
        }
        else {
            cache[path] = handle; // 成功したらキャッシュに登録
        }
        return handle;
    }

    void ClearAll();

private:
    ResourceManager() = default;
    ~ResourceManager();

	// シングルトンインスタンスを保持
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    // 各リソースのキャッシュを定義
    template<typename T>
    using Cache = std::unordered_map<std::wstring, typename ResourceTraits<T>::HandleType>;

    // 全種類のキャッシュをタプルで保持
	// NOTE: タプルとは異なる型のキャッシュを一つのオブジェクトで管理するために使用
	// NOTE: タプルの要素は順番に ModelTag, ImageTag, SoundTag のキャッシュを保持
    std::tuple<Cache<ModelTag>, Cache<ImageTag>, Cache<SoundTag>> m_caches;

    std::mutex m_mutex;

    // 型に応じたキャッシュをタプルから取得するヘルパー
    template<typename T>
    Cache<T>& getCache()
    {
        return std::get<Cache<T>>(m_caches);
    }

    // タプルの全要素に処理を適用するためのヘルパー (実装は .cpp へ)
    template<size_t I = 0, typename Func>
    void for_each_in_tuple(Func f);
};