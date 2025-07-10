#pragma once
#include "IComponent.h"

// 前方宣言
class Entity;

// コンポーネント共通基底クラス(ライフサイクルを定義)
class ComponentBase : public IComponent
{
    // NOTE: friend指定は危険だが、SetOwnerをprotectedにしているため
	//       所有者のみが呼び出せるため問題なし
    friend class Entity;

protected:
    Entity* m_owner = nullptr;
    bool m_active = true;

    void SetOwner(Entity* entity) override { m_owner = entity; }

public:
    virtual ~ComponentBase() = default;

    Entity* GetOwner() const override { return m_owner; }
    void SetActive(bool active) override { m_active = active; }
    bool IsActive() const override { return m_active; }

    // ---ライフサイクルメソッドを統一 ---

    // 初期化処理
    virtual void Start() {}

    // 更新処理
    virtual void Update(float deltaTime) {}

    // 描画処理
    virtual void Draw() {}
};