#include "ResourceManager.h"
#include <functional> // std::apply�̂���

ResourceManager& ResourceManager::Instance()
{
    static ResourceManager instance;
    return instance;
}

ResourceManager::~ResourceManager()
{
    ClearAll();
}

void ResourceManager::ClearAll()
{
    std::lock_guard<std::mutex> lock(m_resourceMutex);

    // C++17��std::apply���g���Atuple���̑S�Ă�Cache�ɑ΂���Clear()���Ăяo��
    std::apply(
        [](auto&... cache) {
            (cache.Clear(), ...);
        },
        m_allCaches
    );
}