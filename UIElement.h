#pragma once
#include "IUIElement.h"
#include <memory>
#include <string>

// �O���錾
class UIRenderer;
class UIInteractor;

class UIElement : public IUIElement
{
protected:
    Transform2D m_transform;
    bool m_isVisible = true;
    std::string m_name;

    // �U�镑���𕔕i�Ƃ��ď��L
    std::unique_ptr<UIRenderer> m_renderer;
    std::unique_ptr<UIInteractor> m_interactor;

public:
    UIElement() = default;
    virtual ~UIElement() = default;

    // --- IUIElement �C���^�[�t�F�[�X�̎��� ---
    void SetVisible(bool visible) override;
    bool IsVisible() const override;

    Transform2D& GetTransform() override;
    const Transform2D& GetTransform() const override;

    void UpdateLogic() override;
    void Draw() override;

    // --- UIElement �ŗL�̋@�\ ---
    void UpdateInteraction();
    const std::string& GetName() const;
    void SetName(const std::string& name);

    // �����蔻��p�̃T�C�Y��Ԃ����z�֐�
    // �f�t�H���g�ł̓T�C�Y0�B�h���N���X�����g�̃T�C�Y��Ԃ��悤�Ɏ�������B
    virtual VECTOR2 GetBoundingSize() const { return { 0.0f, 0.0f }; }

    // �U�镑����ݒ肷�郁�\�b�h
    void SetRenderer(std::unique_ptr<UIRenderer> renderer);
    void SetInteractor(std::unique_ptr<UIInteractor> interactor);
};