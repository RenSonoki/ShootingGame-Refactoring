#include "EntitySystem.h"
#include "Entity.h"
#include "ICollisionComponent.h"
#include "UIComponent.h" // UIComponent�����O���邽�߂ɕK�v

void EntitySystem::AddEntity(std::shared_ptr<Entity> entity) { m_entities.push_back(entity); }
void EntitySystem::RemoveEntity(std::shared_ptr<Entity> entity) { std::erase(m_entities, entity); }
void EntitySystem::Start() { for (auto& e : m_entities) e->Start(); }
void EntitySystem::Clear() { m_entities.clear(); }

void EntitySystem::Update(float deltaTime) {
    // �����؂�̃|�C���^�����S�ɏ���
    m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(),
        [](const auto& e) { return !e || !e->IsActive(); }), m_entities.end());

    for (auto& entity : m_entities) {
        // �� UI�����G���e�B�e�B�́AUISystem���X�V����̂ŏ��O����
        if (entity->GetComponent<UIComponent>()) continue;

        entity->Update(deltaTime);
    }
}
void EntitySystem::Draw() {
    for (auto& entity : m_entities) {
        // UI�����G���e�B�e�B�́AUISystem���`�悷��̂ŏ��O����
        if (entity->GetComponent<UIComponent>()) continue;

        entity->Draw();
    }
}