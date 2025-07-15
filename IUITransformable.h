#pragma once
#include "Transform2D.h"

// Transform��������UI�p�C���^�[�t�F�[�X
class IUITransformable
{
public:
    virtual ~IUITransformable() = default;
    virtual Transform2D& GetTransform() = 0;
    virtual const Transform2D& GetTransform() const = 0;
};