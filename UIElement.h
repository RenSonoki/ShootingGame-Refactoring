#pragma once
#include "IUIElement.h"
#include <memory>
#include <string>

// 前方宣言
class UIRenderer;
class UIInteractor;

class UIElement : public IUIElement
{
protected:
    Transform2D m_transform;
    bool m_isVisible = true;
    std::string m_name;

    // 振る舞いを部品として所有
    std::unique_ptr<UIRenderer> m_renderer;
    std::unique_ptr<UIInteractor> m_interactor;

public:
    UIElement() = default;
    virtual ~UIElement() = default;

    // --- IUIElement インターフェースの実装 ---
    void SetVisible(bool visible) override;
    bool IsVisible() const override;

    Transform2D& GetTransform() override;
    const Transform2D& GetTransform() const override;

    void UpdateLogic() override;
    void Draw() override;

    // --- UIElement 固有の機能 ---
    void UpdateInteraction();
    const std::string& GetName() const;
    void SetName(const std::string& name);

    // 当たり判定用のサイズを返す仮想関数
    // デフォルトではサイズ0。派生クラスが自身のサイズを返すように実装する。
    virtual VECTOR2 GetBoundingSize() const { return { 0.0f, 0.0f }; }

    // 振る舞いを設定するメソッド
    void SetRenderer(std::unique_ptr<UIRenderer> renderer);
    void SetInteractor(std::unique_ptr<UIInteractor> interactor);
};