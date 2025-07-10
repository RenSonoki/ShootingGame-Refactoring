#pragma once//�C���ς�

#include "DrawComponent.h"
#include <DxLib.h>

// �J�����p�����[�^�ێ��p�̍\����
struct CameraParameters
{
    VECTOR position = VGet(0, 0, -10);
    VECTOR target = VGet(0, 0, 0);
    VECTOR up = VGet(0, 1, 0);
};

// �J�����ݒ�R���|�[�l���g�i�`�掞�ɃJ�������f�j
class CameraComponent : public DrawComponent
{
public:
    CameraComponent() = default;

    void SetPosition(const VECTOR& pos);
    void SetTarget(const VECTOR& target);
    void SetUpVector(const VECTOR& up);

    VECTOR GetPosition() const;
    VECTOR GetTarget() const;
    VECTOR GetUpVector() const;

    // �`��n�����iEntitySystem����Ă΂��j
	// �����I��ApplyToDxLibCamera()���Ă΂��悤�ɂ���
    void Draw() override;

    // DxLib�ɃJ�������f
    void ApplyToDxLibCamera() const;

private:
    CameraParameters m_params;
};