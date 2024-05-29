#pragma once
#ifndef WEB_ENGINE_RESOURCES_GEOMETRY_MESH_HPP_
#define WEB_ENGINE_RESOURCES_GEOMETRY_MESH_HPP_

#include <memory>
#include <vector>

#include "resources/buffers/index_buffer.hpp"
#include "resources/buffers/vertex_buffer.hpp"
#include "resources/geometry/material.hpp"
#include "resources/geometry/vertex.hpp"
#include "resources/shaders/shader.hpp"
#include "resources/textures/texture.hpp"

namespace WebEngine::Resources::Geometry
{
    class Mesh
    {
        using IndexBuffer = Buffers::IndexBuffer;
        using VertexBuffer = Buffers::VertexBuffer< Vertex >;
        
    public:
        Mesh( const std::vector< Vertex >& vertices, const std::vector< uint32_t >& indices, std::shared_ptr< Material >& material );
        ~Mesh();

        Mesh( const Mesh& other )             = delete;
        Mesh( Mesh&& other )                  = delete;
        Mesh& operator=( const Mesh& other )  = delete;
        Mesh& operator=( const Mesh&& other ) = delete;

        void bind( const Shaders::Shader& shader ) const;
        void unbind(const Shaders::Shader& shader ) const;

        void draw( const Shaders::Shader& shader ) const;

        const std::shared_ptr< Material >& getMaterial() const;

        void setDefaultMaterial() { m_currentMaterial = nullptr; }
        void setMaterial( std::shared_ptr< Material > material ) { m_currentMaterial = material;}

        const std::string& getName() const { return m_name; }
        void setName( std::string name ) { m_name = name; }

    private:
        void createBuffers( const std::vector< Vertex >& vertices, const std::vector< uint32_t >& indices );

        std::unique_ptr< VertexBuffer > m_vertexBuffer = nullptr;
        std::unique_ptr< IndexBuffer > m_indexBuffer = nullptr;

        std::shared_ptr< Material > m_currentMaterial = nullptr;
        std::shared_ptr< Material > m_defaultMaterial = nullptr;

        uint64_t m_vertexCount = 0;
        uint64_t m_indexCount = 0;

        std::string m_name = "";
    };
}

#endif // WEB_ENGINE_RESOURCES_GEOMETRY_MESH_HPP_