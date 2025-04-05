#pragma once

#include "Sample.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "Rectangle.h"

#include <memory>
/*
material模組化：
把shader, texture, uniform相關的程式碼包進去而已

model模組化：
1. 具有scale, rotate, position等屬性，有公開方法可以調整，會算出model matrix可以取得
2. 具有vertex array, vetex buffer, index buffer等屬性
3. 有各種範本(2D三角 2D方塊 3D方塊等)，裡面vertex資料會自己設定好

Camera類別：
1. 有view matrix和projection
2. 可以選擇要正交投影還是透視投影
*/

namespace Sample
{
    class SampleTexture2D : public Sample
    {
    private:
        std::unique_ptr<Renderer> renderer;
        std::unique_ptr<Shader> shader;
        std::unique_ptr<Texture> texture;
        std::unique_ptr<Model::Rectangle> rectangle;
        
        glm::mat4 proj;
        glm::mat4 view;
    public:
        SampleTexture2D();
        ~SampleTexture2D();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImguiRender() override;
    };
    
} // namespace Sample
