#pragma once

#include "DrawComponent.h"
#include <memory>
#include <string>

// �O���錾
class TransformComponent; 

// ���f���`���S������ DrawComponent
class RenderModelComponent : public DrawComponent
{
public:
    explicit RenderModelComponent(const std::wstring& modelPath);

    // ����������
    void Start() override;

    // �`�揈��
    void Draw() override;

    // ���f���̍����ւ�
    void SetModel(const std::wstring& modelPath);

    // ���f���n���h���擾
    int GetModelHandle() const;

private:
    int m_modelHandle = -1;
    std::wstring m_modelPath;

    // �ˑ�����R���|�[�l���g�ւ̃|�C���^
    std::shared_ptr<TransformComponent> m_transform = nullptr;
};