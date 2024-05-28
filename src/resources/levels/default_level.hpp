#pragma once
#ifndef WEB_ENGINE_RESOURCES_LEVELS_DEFAULT_LEVEL_HPP_
#define WEB_ENGINE_RESOURCES_LEVELS_DEFAULT_LEVEL_HPP_

#include <list>
#include <map>
#include <memory>

#include <glm/gtc/quaternion.hpp>

#include "resources/cameras/camera.hpp"
#include "resources/cameras/camera_movement.hpp"
#include "resources/lights/directional_light.hpp"
#include "resources/objects/model.hpp"
#include "resources/lights/point_light.hpp"
#include "resources/objects/light_source.hpp"
#include "resources/shaders/shader.hpp"

namespace WebEngine::Resources::Levels
{
    class DefaultLevel
    {
        using CameraPtr           = std::unique_ptr< WebEngine::Resources::Cameras::Camera >;
        using CameraMovementPtr   = std::unique_ptr< WebEngine::Resources::Cameras::CameraMovement >;
        using DirectionalLightPtr = std::unique_ptr< WebEngine::Resources::Lights::DirectionalLight >;
        using ModelPtr            = std::unique_ptr< WebEngine::Resources::Objects::Model >;
        using PointLightPtr       = std::unique_ptr< WebEngine::Resources::Lights::PointLight >;
        using ShaderPtr           = std::unique_ptr< WebEngine::Resources::Shaders::Shader >;

    public:
        DefaultLevel();
        ~DefaultLevel();

        DefaultLevel( const DefaultLevel& other )             = delete;
        DefaultLevel( DefaultLevel&& other )                  = delete;
        DefaultLevel& operator=( const DefaultLevel& other )  = delete;
        DefaultLevel& operator=( const DefaultLevel&& other ) = delete;

        void draw( float dt ) const;

    private:
        void initDefault();
        void initLights();
        void initMaterials();

        void updateMaterial( std::string mesh, std::string material );

        CameraPtr m_camera = nullptr;
        CameraMovementPtr m_cameraMovement = nullptr;
        ModelPtr m_model = nullptr;
        ShaderPtr m_defaultShader = nullptr;
        ShaderPtr m_lightSourceShader = nullptr;

        // Lihgting
        DirectionalLightPtr m_directionalLight = nullptr;
        std::array< PointLightPtr, 3 > m_pointLights;
        
        // Materials
        std::map< std::string, std::shared_ptr< Geometry::Material > > m_materials;
        Core::Eventing::ListenerID m_materialUpdateListenerID = 0;
    };
}

#endif // WEB_ENGINE_RESOURCES_LEVELS_DEFAULT_LEVEL_HPP_