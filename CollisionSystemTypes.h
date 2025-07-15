#pragma once
#include <functional>
#include <utility>      // std::pair�̂���
#include "CollisionShapeType.h"
#include <DxLib.h>      // VECTOR�̂���

// �O���錾
class ICollisionComponent;

// �Փˏ���ێ����邽�߂̍\����
struct CollisionInfo
{
    VECTOR normal; // �����o�������i���K���ς݃x�N�g���j
    float depth;   // �߂荞�݂̐[��
};

// �Փ˔���֐��̌^��`���ACollisionInfo��Ԃ��悤�ɏC��
using CollisionFunc = std::function<bool(const ICollisionComponent&, const ICollisionComponent&, CollisionInfo&)>;

// �Փˌ`��̃y�A���`����\���� (�}�b�v�̃L�[�Ƃ��Ďg�p)
// ��������Ȃ��悤�ɁA�K��ShapeType�̒l������������first�Ɋi�[����
struct CollisionPair
{
    CollisionShapeType first;
    CollisionShapeType second;

    CollisionPair(CollisionShapeType t1, CollisionShapeType t2) {
        if (t1 < t2) {
            first = t1;
            second = t2;
        }
        else {
            first = t2;
            second = t1;
        }
    }

    // std::map �̃L�[�Ƃ��Ďg����悤�ɁA��r���Z�q���I�[�o�[���[�h
    bool operator<(const CollisionPair& other) const {
        if (first < other.first) return true;
        if (first > other.first) return false;
        return second < other.second;
    }
};