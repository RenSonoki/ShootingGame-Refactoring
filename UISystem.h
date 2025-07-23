#pragma once
#include <vector>
#include <memory>

class UIElement; // UIElement�̑O���錾

// UIElement�̊K�w���Ǘ����A�X�V�E�`����s��UI���̃V�X�e��
class UISystem
{
public:
    UISystem();
    ~UISystem();

    UISystem(const UISystem&) = delete;
    UISystem& operator=(const UISystem&) = delete;

    void AddElement(std::unique_ptr<UIElement> element);
    void Update(float deltaTime);
    void Draw() const;
    void Clear();
    void SetLayerDepth(int depth);
    int GetLayerDepth() const;

private:
    void CollectRenderables(UIElement* element, std::vector<UIElement*>& renderList) const;

    std::vector<std::unique_ptr<UIElement>> m_rootElements;
    int m_layerDepth = 0;
};