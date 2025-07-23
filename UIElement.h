#pragma once
#include "IUIElement.h" // IUIElement��UpdateLogic���C�����K�v�ł�
#include <memory>
#include <string>

// �O���錾
class UIRenderer;
class UIInteractor;
class UIAnimator;
struct Transform2D; // Transform2D���O���錾���Ă����Ɨǂ��ł��傤
struct VECTOR2;     // VECTOR2���O���錾���Ă����Ɨǂ��ł��傤


class UIElement : public IUIElement
{
protected:
    Transform2D m_transform;
    bool m_isVisible = true;
    std::string m_name;
    int m_zOrder = 0;

    // �U�镑���𕔕i�Ƃ��ď��L
    std::unique_ptr<UIRenderer> m_renderer;
    std::unique_ptr<UIInteractor> m_interactor;
    std::unique_ptr<UIAnimator> m_animator;

public:
    UIElement();
    virtual ~UIElement();

    // --- IUIElement �C���^�[�t�F�[�X�̎��� ---
    void SetVisible(bool visible) override;
    bool IsVisible() const override;

    Transform2D& GetTransform() override;
    const Transform2D& GetTransform() const override;

    // �� �C���_: deltaTime �������Ƃ��Ď󂯎��悤�ɕύX
    // NOTE: ����IUIElement�������l�̏C�����K�v�ł�
    void UpdateLogic(float deltaTime) override;
    void Draw() const override;

    // --- UIElement �ŗL�̋@�\ ---
    virtual void UpdateInteraction();
    const std::string& GetName() const;
    void SetName(const std::string& name);

    void SetZOrder(int order);
    int GetZOrder() const;

    virtual VECTOR2 GetBoundingSize() const;

    bool HasRenderer() const;

    // �U�镑����ݒ肷�郁�\�b�h
    void SetRenderer(std::unique_ptr<UIRenderer> renderer);
    void SetInteractor(std::unique_ptr<UIInteractor> interactor);
    void SetAnimator(std::unique_ptr<UIAnimator> animator);
};