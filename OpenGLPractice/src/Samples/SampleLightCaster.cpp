#include "SampleLightCaster.h"
#include "Cube.h"
#include "UIManager.h"

namespace Sample
{
    SampleLightCaster::SampleLightCaster()
    {
        camera = std::make_unique<Camera>(CameraType::PERSPECTIVE, 960, 540);

        DirLightProperties dirLightProperties;
        dirLightProperties.direction = glm::vec3(-0.2f, -1.0f, -0.3f);
        dirLightProperties.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
        dirLightProperties.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
        dirLightProperties.specular = glm::vec3(1.0f, 1.0f, 1.0f);
        dirLight = std::make_unique<Light<DirLightProperties>>(LightType::DIRECTIONAL, dirLightProperties);

        PointLightProperties pointLightProperties;
        pointLightProperties.position = glm::vec3(0.12f, 1.0f, 0.2f);
        pointLightProperties.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
        pointLightProperties.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
        pointLightProperties.specular = glm::vec3(1.0f, 1.0f, 1.0f);
        pointLightProperties.constant = 1.0f;
        pointLightProperties.linear = 0.09f;
        pointLightProperties.quadratic = 0.032f;
        pointLight = std::make_unique<Light<PointLightProperties>>(LightType::POINT, pointLightProperties);

		SpotLightProperties spotLightProperties;
		spotLightProperties.position = camera->GetPosition();
		spotLightProperties.direction = camera->GetForward();
		spotLightProperties.cutOff = glm::cos(glm::radians(6.25f));
		spotLightProperties.outerCutOff = glm::cos(glm::radians(8.75f));
		spotLightProperties.ambient = glm::vec3(0.1f, 0.1f, 0.1f);
		spotLightProperties.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
		spotLightProperties.specular = glm::vec3(1.0f, 1.0f, 1.0f);
        spotLightProperties.constant = 1.0f;
        spotLightProperties.linear = 0.09f;
        spotLightProperties.quadratic = 0.032f;
		spotLight = std::make_unique<Light<SpotLightProperties>>(LightType::SPOT, spotLightProperties);
            
        CreateCube(dirCube, LightType::DIRECTIONAL);
        CreateCube(pointCube, LightType::POINT);
		CreateCube(spotCube, LightType::SPOT);
        currentLightType = LightType::SPOT;
    }

    SampleLightCaster::~SampleLightCaster()
    {
    }

    void SampleLightCaster::OnUpdate(float deltaTime)
    {
		RotateCube(*dirCube, deltaTime);
		RotateCube(*pointCube, deltaTime);
        RotateCube(*spotCube, deltaTime);
    }

    void SampleLightCaster::OnRender()
    {
        switch (currentLightType)
        {
        case LightType::DIRECTIONAL:
            dirCube->GetMaterial().UpdateDirLightUniforms(dirLight->GetLightProperties(), camera->GetPosition(), dirCube->GetTransform().GetNormalMatrix());
            dirCube->OnRender(camera->GetProjectionMatrix(), camera->GetViewMatrix());
            break;
        case LightType::POINT:
            pointCube->GetMaterial().UpdatePointLightUniforms(pointLight->GetLightProperties(), camera->GetPosition(), pointCube->GetTransform().GetNormalMatrix());
            pointCube->OnRender(camera->GetProjectionMatrix(), camera->GetViewMatrix());
            break;
        case LightType::SPOT:
			spotCube->GetMaterial().UpdateSpotLightUniforms(spotLight->GetLightProperties(), camera->GetPosition(), spotCube->GetTransform().GetNormalMatrix());
			spotCube->OnRender(camera->GetProjectionMatrix(), camera->GetViewMatrix());
            break;
        default:
            break;
        }

        pointLight->OnRender(camera->GetProjectionMatrix(), camera->GetViewMatrix());
    }

    void SampleLightCaster::OnImguiRender()
    {

        if (ImGui::Begin("Light Type"))
        {
            if (ImGui::Combo("Light Type", (int*)&currentLightType, lightTypes, IM_ARRAYSIZE(lightTypes)))
            {
                std::cout << "Current Light Type: " << lightTypes[(int)currentLightType] << std::endl;
            }
        }
        
        ImGui::End();
    }


    void SampleLightCaster::CreateCube(std::unique_ptr<GameObject> &cube, LightType type)
    {
        std::shared_ptr<Material> cubeMaterial;

        switch(type)
        {
            case LightType::DIRECTIONAL:
                cubeMaterial = std::make_shared<Material>("res/shaders/LightCaster/DirLight.shader");
                break;
            case LightType::POINT:
                cubeMaterial = std::make_shared<Material>("res/shaders/LightCaster/PointLight.shader");
                break;
            case LightType::SPOT:
                cubeMaterial = std::make_shared<Material>("res/shaders/LightCaster/SpotLight.shader");
				break;
        }

        cubeMaterial->AddTexture("res/textures/container2.png", 0, "material.diffuse");
        cubeMaterial->AddTexture("res/textures/container2_specular.png", 1, "material.specular");
        cubeMaterial->BindTextures();
        cubeMaterial->SetMaterialShininess(64.0f);
        cube = std::make_unique<GameObject>(std::make_shared<Mesh::Cube>(1.0f, 1.0f, 1.0f), cubeMaterial);
        cube->GetTransform().SetScale(0.8f, 0.8f, 0.8f);
    }

    void SampleLightCaster::RotateCube(GameObject &cube, float deltaTime)
    {
        cube.GetTransform().GetRotation().x += 6 * deltaTime;
        cube.GetTransform().GetRotation().y += 10 * deltaTime;
        cube.GetTransform().GetRotation().z += 8 * deltaTime;
	}
}
