#pragma once
#include <memory>
#include <vector>

// �O���錾
class EntitySystem;
class EnemyPrototype;
class TransformComponent;

/**
 * @class EnemySpawner
 * @brief �G�̏o�����W�b�N����ɒS������N���X
 */
class EnemySpawner
{
public:
    // �K�v�Ȉˑ��֌W���R���X�g���N�^�Ŏ󂯎��
    EnemySpawner(
        EntitySystem* entitySystem,
        std::shared_ptr<EnemyPrototype> prototype,
        std::weak_ptr<TransformComponent> playerTransform
    );

    // ���t���[���Ă΂��X�V����
    void Update(float deltaTime);

    // �O������p�����[�^��ύX�ł���悤�ɃZ�b�^�[��p��
    void SetSpawnInterval(float seconds);
    void SetSpawnDistance(float distance);

private:
    // ���ۂ̏o������
    void Spawn();

    // �O������^����ꂽ�u����v�ւ̃|�C���^
    EntitySystem* m_entitySystem;
    std::shared_ptr<EnemyPrototype> m_prototype;
    std::weak_ptr<TransformComponent> m_playerTransform;

    // �����̏�ԕϐ�
    float m_spawnInterval;
    float m_spawnDistance;
    float m_timer;
};