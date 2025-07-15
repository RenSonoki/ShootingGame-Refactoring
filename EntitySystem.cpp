#include "EntitySystem.h"
#include "Entity.h"
#include "ICollisionComponent.h"
#include "UIComponent.h" // UIComponentを除外するために必要

void EntitySystem::AddEntity(std::shared_ptr<Entity> entity) { m_entities.push_back(entity); }
void EntitySystem::RemoveEntity(std::shared_ptr<Entity> entity) { std::erase(m_entities, entity); }
void EntitySystem::Start() { for (auto& e : m_entities) e->Start(); }
void EntitySystem::Clear() { m_entities.clear(); }

void EntitySystem::Update(float deltaTime) {
    // 期限切れのポインタを安全に除去
    m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(),
        [](const auto& e) { return !e || !e->IsActive(); }), m_entities.end());

    for (auto& entity : m_entities) {
        // ★ UIを持つエンティティは、UISystemが更新するので除外する
        if (entity->GetComponent<UIComponent>()) continue;

        entity->Update(deltaTime);
    }
}
void EntitySystem::Draw() {
    for (auto& entity : m_entities) {
        // UIを持つエンティティは、UISystemが描画するので除外する
        if (entity->GetComponent<UIComponent>()) continue;

        entity->Draw();
    }
}