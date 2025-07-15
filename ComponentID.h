#pragma once

// プロジェクトに存在するコンポーネントの種類をすべて列挙します。
// NOTE: 新しいコンポーネントを追加したら、ここにも追加してください。
enum class ComponentID
{
    // 基本コンポーネント
    Transform,

    // 描画コンポーネント
    SpriteRenderer,
    ModelRenderer,

    // ロジック・物理コンポーネント
    PlayerController,
    AIController,
    Rigidbody,
    Collider,

    // その他
    Animator
};