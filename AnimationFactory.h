#pragma once

#include <unordered_map>
#include <string>
#include <DxLib.h>

// ���f���n���h���ƃA�j���[�V�����������ɃC���f�b�N�X�������E�L���b�V������t�@�N�g���[
class AnimationFactory
{
public:
    // �A�j���[�V�������ɑΉ�����C���f�b�N�X���擾�i���擾�Ȃ�MV1GetAnimIndex�Ŏ擾���ăL���b�V���j
    int GetIndex(int modelHandle, const std::wstring& animName);

    // �L���b�V���̑S�폜
    void Clear();

private:
    // �L�[�F���f���n���h���ƃA�j���[�V�������̑g�ݍ��킹
    using Key = std::pair<int, std::wstring>;

    struct KeyHash {
        std::size_t operator()(const Key& key) const {
            return std::hash<int>()(key.first) ^ std::hash<std::wstring>()(key.second);
        }
    };

    std::unordered_map<Key, int, KeyHash> m_cache;
};