#include "ModelFactory.h"

// �f�X�g���N�^�̎���
ModelFactory::~ModelFactory()
{
    Clear();
}

int ModelFactory::Load(const std::wstring& path)
{
    auto it = m_cache.find(path);
    if (it != m_cache.end()) {
        return it->second;
    }

    int handle = MV1LoadModel(path.c_str());
    if (handle != -1) {
        m_cache[path] = handle;
    }
    // �G���[�n���h�����O�̕ʈāF
    // else {
    //     throw std::runtime_error("���f���̓ǂݍ��݂Ɏ��s���܂���: " + path);
    // }
    return handle;
}

void ModelFactory::Clear()
{
    for (auto& pair : m_cache) {
        MV1DeleteModel(pair.second);
    }
    m_cache.clear();
}