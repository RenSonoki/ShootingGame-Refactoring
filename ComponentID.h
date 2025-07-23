#pragma once
#include <functional> // �� std::hash �̂��߂ɃC���N���[�h

// �v���W�F�N�g�ɑ��݂���R���|�[�l���g�̎�ނ����ׂė񋓂��܂��B
enum class ComponentID
{
    // ... (���e�͕ύX�Ȃ�)
    Transform,
    SpriteRenderer,
    ModelRenderer,
    PlayerController,
    AIController,
    Rigidbody,
    Collider,
    Camera,
    CameraController,
    Animator,
    Move,
    Life,
    Homing,
    Health,
    Shooting,
    Sphere,
	Capsule,
    ThirdPersonCamera
};


// --- std::hash for ComponentID ---
// std::unordered_map��ComponentID���L�[�Ƃ��Ďg����悤�ɁA�n�b�V���֐����`���܂�
namespace std
{
    template <>
    struct hash<ComponentID>
    {
        size_t operator()(const ComponentID& id) const
        {
            // enum class �̎��̂ł��鐮���l���A���̂܂܃n�b�V���l�Ƃ��ė��p���܂�
            return hash<std::underlying_type_t<ComponentID>>()(
                static_cast<std::underlying_type_t<ComponentID>>(id)
                );
        }
    };
}