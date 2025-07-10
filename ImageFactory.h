#pragma once

#include <unordered_map>
#include <string>
#include <DxLib.h>

// �摜���\�[�X�̓ǂݍ��݂ƃL���b�V���Ǘ����s���t�@�N�g���[
class ImageFactory {
public:
    // �摜��ǂݍ��݁i�L���b�V������Ă���΍ė��p�j
    int Load(const std::wstring& path);

    // �S�摜�̉��
    void Clear();

private:
    std::unordered_map<std::wstring, int> m_cache; // �p�X�ƃn���h���̑Ή��\
};