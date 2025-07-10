#pragma once

#include <unordered_map>
#include <string>
#include <DxLib.h>

// ���f�����\�[�X���Ǘ�����V���O���g���N���X
class ModelFactory
{
public:
    // �B��̃C���X�^���X���擾����
    static ModelFactory& GetInstance()
    {
        static ModelFactory instance; // C++11�ȍ~�A�X���b�h�Z�[�t�ȏ��������ۏ؂����
        return instance;
    }

    // ���f���̓ǂݍ���
    int Load(const std::wstring& path);

private:
    // �V���O���g���̂��߂̐ݒ�
    ModelFactory() = default;  // �R���X�g���N�^
    ~ModelFactory(); // �f�X�g���N�^�Ń��\�[�X���������

    // �R�s�[�ƃ��[�u���֎~����
    ModelFactory(const ModelFactory&) = delete;
    ModelFactory& operator=(const ModelFactory&) = delete;
    ModelFactory(ModelFactory&&) = delete;
    ModelFactory& operator=(ModelFactory&&) = delete;

    void Clear(); // ��������̓v���C�x�[�g��

    std::unordered_map<std::wstring, int> m_cache;
};