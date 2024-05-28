#pragma once
#ifndef WEB_ENGINE_CORE_PARSERS_ASSIMP_PARSER_HPP_
#define WEB_ENGINE_CORE_PARSERS_ASSIMP_PARSER_HPP_

#include <filesystem>
#include <map>
#include <memory>

#include <assimp/Importer.hpp>
#include <assimp/matrix4x4.h>
#include <assimp/scene.h>

#include "assimp_flags.hpp"
#include "resources/geometry/mesh.hpp"

namespace WebEngine::Resources::Objects  { class Model; }
namespace WebEngine::Resources::Textures { class Texture; }

namespace WebEngine::Core::Parsers
{
    class AssimpParser
    {
        using MeshPtr = std::unique_ptr< Resources::Geometry::Mesh >;
        using ModelPtr = std::unique_ptr< Resources::Objects::Model >;
        using TexturePtr = std::unique_ptr< Resources::Textures::Texture >;

    public:
        ModelPtr loadModel( std::filesystem::path location, EAssimpParserFlags flags );

    private:
        std::map< std::string, MeshPtr > processNode( aiMatrix4x4& transform, struct aiNode* node, const struct aiScene* scene );
        MeshPtr processMesh( const aiMatrix4x4& transform, struct aiMesh* mesh, const struct aiScene* scene );
        void createMaterial( const aiScene* scene, std::shared_ptr< Resources::Geometry::Material >& newMaterial, int index );

        std::filesystem::path m_filePath = "";
    };
}

#endif // WEB_ENGINE_CORE_PARSERS_ASSIMP_PARSER_HPP_
