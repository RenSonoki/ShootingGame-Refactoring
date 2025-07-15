#pragma once
#include <DxLib.h>
#include <string>

// NOTE: �V�������\�[�XEffect��ǉ��������ꍇ
//    1: ResourceTraits<EffectTag>���`
//    2: ResourceManager.h��AllCaches�Ƃ���tuple��Cache<EffectTag>����s�ǉ�
//    3: Get<EffectTag>(...)�������I�Ɏg����悤�ɂȂ�܂��B

// ---���\�[�X�̎�ނ����ʂ��邽�߂́u�^�O�v���` ---
// NOTE: ���g�͋�ŁA�^���̂��̂����ʎq�ɂȂ�܂��B
struct ModelTag {};
struct ImageTag {};
struct SoundTag {};

// ---���\�[�X���Ƃ̓������`����uTraits�v�N���X ---

// �f�t�H���g�̃e���v���[�g�i���g�͖���`�j
template<typename T>
struct ResourceTraits;

// ModelTag�ɑ΂�����ꉻ
template<>
struct ResourceTraits<ModelTag>
{
    using HandleType = int; // �n���h���̌^

    // ���\�[�X��ǂݍ��ސÓI���\�b�h
    static HandleType Load(const std::wstring& path) {
        return MV1LoadModel(path.c_str());
    }
    // ���\�[�X���������ÓI���\�b�h
    static void Unload(HandleType handle) {
        if (handle != -1) MV1DeleteModel(handle);
    }
};

// ImageTag�ɑ΂�����ꉻ
template<>
struct ResourceTraits<ImageTag>
{
    using HandleType = int;

    static HandleType Load(const std::wstring& path) {
        return LoadGraph(path.c_str());
    }
    static void Unload(HandleType handle) {
        if (handle != -1) DeleteGraph(handle);
    }
};

// SoundTag�ɑ΂�����ꉻ
template<>
struct ResourceTraits<SoundTag>
{
    using HandleType = int;

    static HandleType Load(const std::wstring& path) {
        return LoadSoundMem(path.c_str());
    }
    static void Unload(HandleType handle) {
        if (handle != -1) DeleteSoundMem(handle);
    }
};