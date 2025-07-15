#pragma once
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include "ComponentBase.h"

// Entity���g��shared_ptr�ŊǗ�����邱�Ƃ�z�肵�A
// ���S�Ɏ��g��shared_ptr���擾�ł���悤�ɂ���
class Entity : public std::enable_shared_from_this<Entity>
{
public:
    Entity();
    virtual ~Entity() = default;

    // --- �R���|�[�l���g�Ǘ� ---

    // �R���|�[�l���g���^�ƃR���X�g���N�^�������w�肵�āAEntity�����Ő����E�ǉ�����
    template<typename T, typename... Args>
    std::shared_ptr<T> AddComponent(Args&&... args);

    // �����ȃ}�b�v�����ŃR���|�[�l���g���擾����
    template<typename T>
    std::shared_ptr<T> GetComponent() const;

    // �w�肵���^�̃R���|�[�l���g�������Ă��邩�m�F����
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
    // Entity�̃��j�[�NID�����p
    static int s_nextID;
    int m_entityID;

    bool m_active = true;
    bool m_started = false;
    std::wstring m_tag;

    // �S�ẴR���|�[�l���g��ێ����郊�X�g�i�X�V���[�v�p�j
    std::vector<std::shared_ptr<IComponent>> m_components;

    // ���������p�̃}�b�v (ComponentID -> Component)
    std::unordered_map<ComponentID, std::shared_ptr<IComponent>> m_componentMap;
};

// --- �e���v���[�g���� ---
template<typename T, typename... Args>
std::shared_ptr<T> Entity::AddComponent(Args&&... args)
{
    // �w�肳�ꂽ�^�̃R���|�[�l���g�����łɒǉ�����Ă��Ȃ����`�F�b�N�i�C�Ӂj
    // assert(!HasComponent<T>() && "Component type already exists.");

    // �V�����R���|�[�l���g�𐶐�
    // std::forward�ň��������S�ɓ]��
    auto newComponent = std::make_shared<T>(std::forward<Args>(args)...);

    // IComponent�ւ̃|�C���^�ɃL���X�g
    auto componentBase = std::static_pointer_cast<IComponent>(newComponent);

    // ���L�҂�ݒ� (enable_shared_from_this ���g���Ĉ��S�Ƀ|�C���^��n��)
    componentBase->SetOwner(shared_from_this());

    // ���X�g�ƍ��������p�}�b�v�̗����ɒǉ�
    m_components.push_back(componentBase);
    m_componentMap[newComponent->GetID()] = componentBase;

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
    // �e�R���|�[�l���g�N���X�Œ�`���ꂽ�ÓIID���g���ă}�b�v������
    auto it = m_componentMap.find(T::ID);
    if (it != m_componentMap.end())
    {
        // ����������A�����h���N���X�̌^(T)�Ɉ��S�ɃL���X�g���ĕԂ�
        return std::static_pointer_cast<T>(it->second);
    }
    return nullptr;
}

template<typename T>
bool Entity::HasComponent() const
{
    // count���g���΁A�L�[�̑��݂������Ƀ`�F�b�N�ł���
    return m_componentMap.count(T::ID) > 0;
}