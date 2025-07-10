#pragma once// 修正済み

#include <unordered_map>
#include <string>
#include <memory>
#include <vector>
#include "IEntityPrototype.h"

// Prototype パターンを用いたエンティティ生成管理クラス（Singleton）
class PrototypeManager
{
public:
    static PrototypeManager& Instance();

    // プロトタイプ登録（ID: wstring）
    void Register(const std::wstring& id, std::shared_ptr<IEntityPrototype> prototype);

    // 複製（通常）例：Clone()
    std::shared_ptr<Entity> Create(const std::wstring& id) const;

    // 位置付き複製（例：弾や敵の初期スポーン位置）
    std::shared_ptr<Entity> CreateAt(const std::wstring& id, const VECTOR& pos) const;

    // 存在確認（安全なチェックに使用）
    bool Has(const std::wstring& id) const;

    // 登録済み ID 一覧取得（UI用など）
    std::vector<std::wstring> GetAllIDs() const;

    // 全削除（シーンリセット時など）
    void Clear();

private:
    PrototypeManager() = default;
    PrototypeManager(const PrototypeManager&) = delete;
    PrototypeManager& operator=(const PrototypeManager&) = delete;

    std::unordered_map<std::wstring, std::shared_ptr<IEntityPrototype>> m_prototypes;
};