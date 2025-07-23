#include "MoveComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include <cassert>

// �ÓI�����o�ϐ��̎��̂��`
const VECTOR MoveComponent::DEFAULT_DIRECTION = VGet(0.0f, 0.0f, 1.0f);

MoveComponent::MoveComponent()
// �����o�ϐ������������X�g�ŏ��������܂��B
// ���N���X(ComponentBase)�̃f�t�H���g�R���X�g���N�^�͈ÖٓI�ɌĂяo����܂��B
    : m_transform(nullptr)
    , m_normalizedDirection(DEFAULT_DIRECTION)
    , m_speed(DEFAULT_SPEED)
{
    // �R���X�g���N�^�{�̂͋��OK�ł��B
    // �I�[�i�[�̐ݒ�́A���̃R���|�[�l���g�𐶐����鑤�̐ӔC�ł��B
}

ComponentID MoveComponent::GetID() const
{
    // ComponentID�񋓌^��Move�Ȃǂ�ǉ����Ă�������
    return ComponentID::Move;
}

void MoveComponent::Start()
{
    // ���̃R���|�[�l���g���@�\���邽�߂ɂ�TransformComponent���K�{�ł��B
    // GetOwner()�́A���O��SetOwner()���Ă΂�Ă��邱�Ƃ�O��Ƃ��܂��B
    m_transform = GetOwner()->GetComponent<TransformComponent>();

    // �ˑ��R���|�[�l���g��������Ȃ��ꍇ�́A�J�����ɑ��������ł���悤assert�Œ�~�����܂��B
    assert(m_transform != nullptr && "MoveComponent requires a TransformComponent on the same Entity.");
}

void MoveComponent::Update(float deltaTime)
{
    // TransformComponent���Ȃ��A�܂��͑��x��0�ȉ��̏ꍇ�͉������܂���B
    if (!m_transform || m_speed <= 0.0f)
    {
        // ��~���Ă���ꍇ�́A�O�̂��ߑ��x�𖾎��I��0�ɂ��܂��B
        if (m_transform)
        {
            m_transform->SetVelocity(VGet(0.0f, 0.0f, 0.0f));
        }
        return;
    }

    // �����Ƒ��x���瑬�x�x�N�g�����Z�o���ATransformComponent�ɓn���܂��B
    // �����I�Ȉړ��̐Ӗ���TransformComponent�������܂��B
    const VECTOR velocity = VScale(m_normalizedDirection, m_speed);
    m_transform->SetVelocity(velocity);
}

void MoveComponent::SetDirection(const VECTOR& direction)
{
    // �����͏�ɐ��K���i������1�Ɂj���ĕێ����܂��B
    m_normalizedDirection = VNorm(direction);
}

void MoveComponent::SetSpeed(float speed)
{
    m_speed = speed;
}

const VECTOR& MoveComponent::GetDirection() const
{
    return m_normalizedDirection;
}

float MoveComponent::GetSpeed() const
{
    return m_speed;
}