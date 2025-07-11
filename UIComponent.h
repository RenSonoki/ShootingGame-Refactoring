#pragma once

#include "ComponentBase.h"
#include "IUIRenderable.h"
#include "IUITransformable.h"
#include "IUIVisible.h"
#include "Transform2D.h"
#include <string>

class Entity;


class UIComponent : public ComponentBase, public IUIRenderable, public IUITransformable, public IUIVisible
{
public:
    UIComponent();
    virtual ~UIComponent() = default;

    // --- ComponentBase�����ʋ@�\��񋟂��邽�߁A�ȉ��̎����͕s�v�ɂȂ� ---
    // void SetOwner(Entity* entity) override;
    // Entity* GetOwner() const override;
    // void SetActive(bool active) override;
    // bool IsActive() const override;

    // --- UI�ŗL�̋@�\ ---

    // �\������
    void SetVisible(bool visible) override;
    bool IsVisible() const override;

    // Transform
    Transform2D& GetTransform() override;
    const Transform2D& GetTransform() const override;

    // Z������
    void SetZOrder(int order);
    int GetZOrder() const;

    // ���O
    void SetName(const std::string& name);
    const std::string& GetName() const;

    // �`��i������p������N���X����̓I�ȕ`�揈������������j
    void Draw(int targetScreen = -1) override = 0;

protected:
    // m_owner, m_active �� ComponentBase �������Ă���̂ō폜
    bool m_visible = true;
    Transform2D m_transform;
    int m_zOrder = 0;
    std::string m_name;
};