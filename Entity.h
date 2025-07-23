#pragma once
#include <vector>
#include <memory>
#include <string>
#include "ComponentBase.h" // IComponent�̑����ComponentBase�𒼐ڎQ�Ƃ��Ă��ǂ�

/**
 * @class Entity
 * @brief �Q�[�����E�ɑ��݂���S�ẴI�u�W�F�N�g�̊��N���X�B�R���|�[�l���g�̓��ꕨ�B
 */
class Entity : public std::enable_shared_from_this<Entity>
{
public:
    Entity();
    virtual ~Entity() = default;

    // --- �R���|�[�l���g�Ǘ� ---
    template<typename T, typename... Args>
    std::shared_ptr<T> AddComponent(Args&&... args);

    template<typename T>
    std::shared_ptr<T> GetComponent() const;

    template<typename T>
    bool HasComponent() const;

    // --- ���C�t�T�C�N�� ---
    void Start();
    void Update(float deltaTime);
    void Draw() const;

    // --- �Q�b�^�[/�Z�b�^�[ ---
    int GetID() const;
    bool IsActive() const;
    void SetActive(bool value);
    const std::wstring& GetTag() const;
    void SetTag(const std::wstring& tag);

private:
    static int s_nextID;
    int m_entityID;

    bool m_active = true;
    bool m_started = false;
    std::wstring m_tag;

    // �S�ẴR���|�[�l���g��ێ����郊�X�g
    std::vector<std::shared_ptr<IComponent>> m_components;
};


// --- �e���v���[�g�֐��̎��� (�w�b�_�[�t�@�C���ɋL�q) ---

template<typename T, typename... Args>
std::shared_ptr<T> Entity::AddComponent(Args&&... args)
{
    // �V�����R���|�[�l���g�𐶐�
    auto newComponent = std::make_shared<T>(std::forward<Args>(args)...);

    // IComponent�ւ̃|�C���^�ɃL���X�g
    auto componentBase = std::static_pointer_cast<IComponent>(newComponent);

    // ���L�҂�ݒ�
    componentBase->SetOwner(shared_from_this());

    // ���X�g�ɂ̂ݒǉ�
    m_components.push_back(componentBase);

    // ����Entity�����ł�Start�ς݂Ȃ�A�V�����R���|�[�l���g��Start�������ɌĂ�
    if (m_started)
    {
        newComponent->Start();
    }

    return newComponent;
}

template<typename T>
std::shared_ptr<T> Entity::GetComponent() const
{
    // �ێ����Ă���S�R���|�[�l���g�����[�v
    for (const auto& comp : m_components)
    {
        // dynamic_pointer_cast ���g���āA���S�ȃ_�E���L���X�g�����݂�
        auto casted = std::dynamic_pointer_cast<T>(comp);
        if (casted)
        {
            // �L���X�g�ɐ���������A���ꂪ�ړI�̃R���|�[�l���g
            return casted;
        }
    }
    // ������Ȃ���� nullptr ��Ԃ�
    return nullptr;
}

template<typename T>
bool Entity::HasComponent() const
{
    // GetComponent��nullptr�ȊO��Ԃ��΁A�R���|�[�l���g�������Ă���Ƃ�������
    return GetComponent<T>() != nullptr;
}