#pragma once
#include "DxLib.h"
#include <memory>

// �O���錾
class CameraEntity;

/**
 * @class CameraBuilder
 * @brief CameraEntity�̍\�z����ɍs���r���_�[�N���X
 */
class CameraBuilder
{
public:
    CameraBuilder();

    // �J�����̏����ʒu��ݒ肵�܂�
    CameraBuilder& SetPosition(const VECTOR& pos);

    // �����I��LookAt�⎋��p(FoV)�Ȃǂ̐ݒ胁�\�b�h��ǉ��ł��܂�
    // CameraBuilder& SetLookAt(const VECTOR& target);
    // CameraBuilder& SetFieldOfView(float fov);

    // �ŏI�I�ɐݒ������CameraEntity���\�z���ĕԂ��܂�
    std::shared_ptr<CameraEntity> Build() const;

private:
    VECTOR m_position; // �\�z���ɐݒ肷��J�����̏����ʒu
};