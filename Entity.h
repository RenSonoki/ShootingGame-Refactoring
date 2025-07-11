#pragma once

#include <vector>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <typeindex>
#include <algorithm>

// �O���錾
class IComponent;
class ComponentBase;
class LogicComponent;
class DrawComponent;
class UIComponent;

// 
class Entity
{
public:
    Entity();
    virtual ~Entity() = default;

    // ID�Ə�ԊǗ�
    int GetID() const;

	// �A�N�e�B�u��Ԃ̎擾�Ɛݒ�
    bool IsActive() const;
    void SetActive(bool value);

    // �^�O�@�\
    void SetTag(const std::wstring& tag);
    const std::wstring& GetTag() const;

    // �e�q�\���i3D�V�[���p�j
    void SetParent(Entity* parent);
    Entity* GetParent() const;
    const std::vector<std::shared_ptr<Entity>>& GetChildren() const;
    void AddChild(std::shared_ptr<Entity> child);

    // �R���|�[�l���g�Ǘ�
    void AddComponent(const std::shared_ptr<ComponentBase>& component);

    template<typename T>
    std::shared_ptr<T> GetComponent() const;

    template<typename T>
    void RemoveComponent();

    // ����̌^�̃R���|�[�l���g���X�g�𒼐ڎ擾����
    const std::vector<std::shared_ptr<UIComponent>>& GetUIComponents() const;

    // ���C�t�T�C�N��
    virtual void Start();
    virtual void Update(float deltaTime);
    virtual void Draw();

private:
    static int s_nextID;
    int m_entityID;
    bool m_active = true;
    bool m_started = false;

    Entity* m_parent = nullptr;
    std::vector<std::shared_ptr<Entity>> m_children;
    std::wstring m_tag;

    // �S�R���|�[�l���g���^�ō����������邽�߂̃}�b�v
    std::unordered_map<std::type_index, std::shared_ptr<ComponentBase>> m_components;

    // �^�Ŏ��O���ނ��ꂽ���X�g
    std::vector<std::shared_ptr<LogicComponent>> m_logicComponents;
    std::vector<std::shared_ptr<DrawComponent>> m_drawComponents;
    std::vector<std::shared_ptr<UIComponent>> m_uiComponents;
};

// --- �e���v���[�g�̒�` ---

template<typename T>
std::shared_ptr<T> Entity::GetComponent() const
{
    auto it = this->m_components.find(typeid(T));
    if (it != this->m_components.end())
    {
        return std::dynamic_pointer_cast<T>(it->second);
    }
    return nullptr;
}

template<typename T>
void Entity::RemoveComponent()
{
    auto it = this->m_components.find(typeid(T));
    if (it == this->m_components.end()) return;

    auto compToRemove = it->second;
    this->m_components.erase(it);

    // �e��僊�X�g������폜
    if (auto logic = std::dynamic_pointer_cast<LogicComponent>(compToRemove)) {
        std::erase(this->m_logicComponents, logic);
    }
    if (auto draw = std::dynamic_pointer_cast<DrawComponent>(compToRemove)) {
        std::erase(this->m_drawComponents, draw);
    }
    if (auto ui = std::dynamic_pointer_cast<UIComponent>(compToRemove)) {
        std::erase(this->m_uiComponents, ui);
    }
}