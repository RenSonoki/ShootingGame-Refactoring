#pragma once

#include "ResourceTraits.h"
#include <unordered_map>
#include <string>
#include <memory>
#include <tuple>
#include <mutex>
#include <Windows.h> // OutputDebugStringW

// �ėp���\�[�X�}�l�[�W���[
// NOTE: �V���O���g���p�^�[�����g�p���āA�A�v���P�[�V�����S�̂ň�̃C���X�^���X�����L
// NOTE: �t���C�E�F�C�g�p�^�[�����g�p���āA�������\�[�X�̏d�����[�h��h��
class ResourceManager
{
public:
    static ResourceManager& Instance();

    // �e���v���[�g�����ꂽ���\�[�X�擾���\�b�h
    template<typename T>
    typename ResourceTraits<T>::HandleType Get(const std::wstring& path)
    {
        // �Ή�����L���b�V�����擾
        auto& cache = getCache<T>();

        std::lock_guard<std::mutex> lock(m_mutex);

        // �L���b�V�����ɑ��݂��邩����
        auto it = cache.find(path);
        if (it != cache.end())
        {
            return it->second; // ����΂����Ԃ�
        }

        // �Ȃ���΃��[�h
        auto handle = ResourceTraits<T>::Load(path);
        if (handle == -1) {
            OutputDebugStringW((L"[Resource Load Failed] " + path + L"\n").c_str());
        }
        else {
            cache[path] = handle; // ����������L���b�V���ɓo�^
        }
        return handle;
    }

    void ClearAll();

private:
    ResourceManager() = default;
    ~ResourceManager();

	// �V���O���g���C���X�^���X��ێ�
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    // �e���\�[�X�̃L���b�V�����`
    template<typename T>
    using Cache = std::unordered_map<std::wstring, typename ResourceTraits<T>::HandleType>;

    // �S��ނ̃L���b�V�����^�v���ŕێ�
	// NOTE: �^�v���Ƃ͈قȂ�^�̃L���b�V������̃I�u�W�F�N�g�ŊǗ����邽�߂Ɏg�p
	// NOTE: �^�v���̗v�f�͏��Ԃ� ModelTag, ImageTag, SoundTag �̃L���b�V����ێ�
    std::tuple<Cache<ModelTag>, Cache<ImageTag>, Cache<SoundTag>> m_caches;

    std::mutex m_mutex;

    // �^�ɉ������L���b�V�����^�v������擾����w���p�[
    template<typename T>
    Cache<T>& getCache()
    {
        return std::get<Cache<T>>(m_caches);
    }

    // �^�v���̑S�v�f�ɏ�����K�p���邽�߂̃w���p�[ (������ .cpp ��)
    template<size_t I = 0, typename Func>
    void for_each_in_tuple(Func f);
};