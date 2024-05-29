#pragma once
#ifndef WEB_ENGINE_RESOURCES_OBJECTS_SKYBOX_HPP_
#define WEB_ENGINE_RESOURCES_OBJECTS_SKYBOX_HPP_

#include <map>
#include <memory>
#include <string>

#include "resources/geometry/mesh.hpp"
#include "resources/levels/base_object.hpp"
#include "resources/shaders/shader.hpp"

namespace WebEngine::Resources::Objects
{
    class Skybox : public Levels::BaseObject
    {
        using MeshPtr = std::unique_ptr< Geometry::Mesh >;
        
    public:
        Skybox( std::vector<std::filesystem::path> cubemapFacesPaths );
        ~Skybox();

        Skybox( const Skybox& other )             = delete;
        Skybox( Skybox&& other )                  = delete;
        Skybox& operator=( const Skybox& other )  = delete;
        Skybox& operator=( const Skybox&& other ) = delete;

        void draw( const Shaders::Shader& shader ) const;
        void loadCubemap( std::vector<std::filesystem::path> cubemapFacesPaths );

    private:
        void initVBO();

    private:
        std::unique_ptr<Textures::Texture> m_cubemap;
        GLuint m_vbo = 0;
    };
}

#endif // WEB_ENGINE_RESOURCES_OBJECTS_SKYBOX_HPP_
