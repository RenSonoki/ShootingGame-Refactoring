#pragma once
#include "ComponentBase.h"
#include <string>
#include <memory>

class TransformComponent;

class RenderModelComponent : public ComponentBase
{
public:
    // �� �C���_: �f�t�H���g�R���X�g���N�^�ɕύX
    RenderModelComponent();
    // �� �C���_: ���f������̂��߂̃f�X�g���N�^��ǉ�
    virtual ~RenderModelComponent();

    void Start() override;
    void Draw() const override;
    ComponentID GetID() const override;

    // ���f����ݒ肷��B��̃C���^�[�t�F�[�X
    bool SetModel(const std::wstring& modelPath);
    int GetModelHandle() const;

private:
    std::wstring m_modelPath;
    int m_modelHandle;
    std::weak_ptr<TransformComponent> m_transform;
};