#pragma once

// �Փˌ`��̎��ʗp�񋓌^
enum class CollisionShapeType
{
    Sphere,     // ����
    Box,        // AABB��OBB�Ȃǂ̒�����
    Capsule,    // �J�v�Z���^
    Ray,        // ���C�i�I�v�V�����j
    Mesh,       // ���p�` or �O�p�`���b�V���i�����g���p�j
    Unknown     // ���ݒ�܂��͕s��
};