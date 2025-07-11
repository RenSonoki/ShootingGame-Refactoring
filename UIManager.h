#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <vector>
#include <algorithm>
#include "UISystem.h"

// 複数の UI システム（レイヤー）を名前で管理する統一マネージャ
class UIManager
{
public:
    // UIレイヤー（UISystem）を追加・登録
    void AddSystem(const std::string& name, const std::shared_ptr<UISystem>& system);

    // 名前でレイヤーを取得
    std::shared_ptr<UISystem> GetSystem(const std::string& name) const;

    // 指定レイヤーを削除
    void RemoveSystem(const std::string& name);

    // 全UIレイヤーを描画（レイヤー深度を考慮）
    void DrawAll(int targetScreen = -1);

    // 全UIレイヤーを更新
    void UpdateAll();

    // 全レイヤーを削除（シーン遷移時など）
    void Clear();

private:
    std::unordered_map<std::string, std::shared_ptr<UISystem>> m_systems;
};