#pragma once

// �v���W�F�N�g�ɑ��݂���R���|�[�l���g�̎�ނ����ׂė񋓂��܂��B
// NOTE: �V�����R���|�[�l���g��ǉ�������A�����ɂ��ǉ����Ă��������B
enum class ComponentID
{
    // ��{�R���|�[�l���g
    Transform,

    // �`��R���|�[�l���g
    SpriteRenderer,
    ModelRenderer,

    // ���W�b�N�E�����R���|�[�l���g
    PlayerController,
    AIController,
    Rigidbody,
    Collider,

    // ���̑�
    Animator
};