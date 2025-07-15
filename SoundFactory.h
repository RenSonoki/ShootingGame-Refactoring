#pragma once

#include <unordered_map>
#include <string>
#include <DxLib.h>

// �T�E���h���\�[�X�iWAV/MP3/BGM/SE�j���Ǘ�����t�@�N�g���[�N���X
class SoundFactory {
public:
    // �T�E���h�̓ǂݍ��݁i�L���b�V������Ă���΍ė��p�j
    int Load(const std::wstring& path);

    // �S�T�E���h�̉���iDeleteSoundMem�j
    void Clear();

private:
    std::unordered_map<std::wstring, int> m_cache; // �p�X�ƃn���h���̃}�b�v
};