#include "UIPanel.h"

UIPanel::UIPanel() = default;

void UIPanel::AddChild(const std::shared_ptr<UIComponent>& child)
{
    if (child)
    {
        // 子コンポーネントにも、このパネルと同じオーナーエンティティを設定する
        // これにより、子コンポーネントもUISystemに正しく認識される
        m_children.push_back(child);
    }
}

const std::vector<std::shared_ptr<UIComponent>>& UIPanel::GetChildren() const
{
    return m_children;
}

void UIPanel::Draw(int targetScreen)
{
    if (!IsVisible())
    {
        return;
    }

    // パネル自身が描画するべきものがあれば、ここに記述します。
    // （例：パネルの背景画像を描画するなど）
    //
    // 子要素の描画は、UISystemがZソートして正しく行ってくれるため、
    // ここで子要素のDraw()を呼び出す必要はありません。
    // これにより、UI要素が二重に描画される問題を防ぎます。
}

void UIPanel::SetVisible(bool visible)
{
    // まず、自分自身のVisible状態を基底クラスのメソッドで設定
    UIComponent::SetVisible(visible);

    // 次に、管理しているすべての子要素のVisible状態も一括で変更する
    for (const auto& child : m_children)
    {
        if (child)
        {
            child->SetVisible(visible);
        }
    }
}