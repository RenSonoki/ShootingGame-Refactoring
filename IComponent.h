#pragma once

// 前方宣言
class Entity;

// コンポーネントのインターフェース
class IComponent
{
public:
    virtual ~IComponent() = default;

	// NOTE: 所有者を知ることで、Component間の相互作用を可能にする
    virtual void SetOwner(Entity* entity) = 0;
    virtual Entity* GetOwner() const = 0;

    virtual void SetActive(bool active) = 0;
    virtual bool IsActive() const = 0;
};