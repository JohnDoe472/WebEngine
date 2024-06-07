#pragma once

#include <list>
#include <memory>
#include <array>

#include <glm/gtc/quaternion.hpp>

#include "resources/cameras/camera.hpp"
#include "resources/cameras/camera_movement.hpp"
#include "resources/lights/point_light.hpp"
#include "resources/objects/model.hpp"
#include "resources/objects/light_source.hpp"
#include "resources/objects/skybox.hpp"
#include "resources/shaders/shader.hpp"

namespace WebEngine::Resources::Levels
{
    class HouseScene
    {
        using CameraPtr           = std::unique_ptr< WebEngine::Resources::Cameras::Camera >;
        using CameraMovementPtr   = std::unique_ptr< WebEngine::Resources::Cameras::CameraMovement >;
        using ModelPtr            = std::unique_ptr< WebEngine::Resources::Objects::Model >;
        using PointLightPtr       = std::unique_ptr< WebEngine::Resources::Lights::PointLight >;
        using ShaderPtr           = std::unique_ptr< WebEngine::Resources::Shaders::Shader >;
        using SkyboxPtr           = std::unique_ptr< WebEngine::Resources::Objects::Skybox >;

    public:
        HouseScene();
        ~HouseScene() = default;

        HouseScene( const HouseScene& other )             = delete;
        HouseScene( HouseScene&& other )                  = delete;
        HouseScene& operator=( const HouseScene& other )  = delete;
        HouseScene& operator=( const HouseScene&& other ) = delete;

        void draw( float dt ) const;

    private:
        void initDefault();
        void initLights();
        void initMaterials();
        void initSkybox();

        void updateMaterial( std::string mesh, std::string material );
    
    private:
        CameraPtr m_camera = nullptr;
        CameraMovementPtr m_cameraMovement = nullptr;
        ModelPtr m_model = nullptr;
        ShaderPtr m_defaultShader = nullptr;
        ShaderPtr m_lightSourceShader = nullptr;

        // Skybox
        ShaderPtr m_skyboxShader = nullptr;
        SkyboxPtr m_skybox = nullptr;

        // Lihgting
        std::array< PointLightPtr, 3 > m_pointLights;

        // Materials
        std::map< std::string, std::shared_ptr< Geometry::Material > > m_materials;
        Core::Eventing::ListenerID m_materialUpdateListenerID = 0;
    };
}
