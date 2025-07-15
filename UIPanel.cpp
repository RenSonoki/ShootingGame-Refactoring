#include "UIPanel.h"

UIPanel::UIPanel() = default;

void UIPanel::AddChild(std::unique_ptr<UIElement> child)
{
    if (child)
    {
        // unique_ptrの所有権をベクターに移動させる
        m_children.push_back(std::move(child));
    }
}

void UIPanel::UpdateLogic()
{
    // 自身がアクティブでなければ、子要素も更新しない
    if (!IsVisible()) return;

    // まず、自分自身のロジックを更新（基底クラスの処理を呼ぶ）
    UIElement::UpdateLogic();

    // 次に、管理しているすべての子要素のロジックも更新する
    for (const auto& child : m_children)
    {
        if (child)
        {
            child->UpdateLogic();
            child->UpdateInteraction(); // インタラクションも更新
        }
    }
}

void UIPanel::Draw()
{
    // 自身が非表示なら、子要素も描画しない
    if (!IsVisible()) return;

    // まず、自分自身の描画を行う（パネルの背景など）
    // （基底クラスのDrawは、自身に設定されたRendererを呼び出す）
    UIElement::Draw();

    // 次に、管理しているすべての子要素も描画する
    for (const auto& child : m_children)
    {
        if (child)
        {
            child->Draw();
        }
    }
}

void UIPanel::SetVisible(bool visible)
{
    // まず、自分自身のVisible状態を設定
    UIElement::SetVisible(visible);

    // 次に、管理しているすべての子要素のVisible状態も一括で変更する
    for (const auto& child : m_children)
    {
        if (child)
        {
            child->SetVisible(visible);
        }
    }
}