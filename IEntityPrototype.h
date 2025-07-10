#pragma once// �C���ς�

#include <memory>
#include <string>
#include "Entity.h"
#include "TransformComponent.h"

// Entity �𕡐����邽�߂̃C���^�[�t�F�[�X�iPrototype �p�^�[���Ő������W�b�N�𕪗��j
class IEntityPrototype
{
public:
    virtual ~IEntityPrototype() = default;

    // ���S�����i�f�t�H���g�ʒu�j
    virtual std::shared_ptr<Entity> Clone() const = 0;

    // �ʒu�t�������i���� Transform ���w��j
    virtual std::shared_ptr<Entity> CloneWithTransform(const VECTOR& position) const = 0;

    // �v���g�^�C�v���iUI�ł̕\���⎯�ʂɎg�p�j
    virtual std::wstring GetName() const = 0;

    // �J�e�S�����i�G/�e/�A�C�e���Ȃǂŕ��ށj
    virtual std::wstring GetCategory() const = 0;
};