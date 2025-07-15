#include "UIImage.h"
#include "SimpleSpriteRenderer.h" // ���g�ɑ������镔�i
#include <memory>

UIImage::UIImage(const std::wstring& imagePath)
{
    // 1. ���g�́u�`��v�U�镑����S�����镔�i�𐶐�
    auto renderer = std::make_unique<SimpleSpriteRenderer>(imagePath);

    // 2. ���N���X�̋@�\���g���āA�����������i�����g�ɑ�������
    //    ����ȍ~�A����UIImage�C���X�^���X��Draw()���Ă΂��ƁA
    //    �����I�ɏ�Ő�������SimpleSpriteRenderer��Draw()�����s�����B
    SetRenderer(std::move(renderer));
}