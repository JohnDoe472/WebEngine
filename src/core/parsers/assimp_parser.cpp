#include "core/parsers/assimp_parser.hpp"

#include "resources/geometry/vertex.hpp"
#include "resources/objects/model.hpp"

#include <iostream>

namespace fs = std::filesystem;

namespace WebEngine::Core::Parsers
{
    AssimpParser::ModelPtr AssimpParser::loadModel( fs::path location, EAssimpParserFlags flags )
    {
        m_filePath = location;

        Assimp::Importer import;
        const aiScene* scene = import.ReadFile( location.string(), static_cast< unsigned >( flags ) );

        if ( !scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode )
        {
            std::cout << "Can't read model" << std::endl;
            throw std::runtime_error( "Can't read model" );
        }

        aiMatrix4x4 identity;
        std::map< std::string, MeshPtr > meshes = processNode( identity, scene->mRootNode, scene );

        ModelPtr newModel = std::make_unique< Resources::Objects::Model >( meshes );

        return std::move( newModel );
    }

    std::map< std::string, AssimpParser::MeshPtr > AssimpParser::processNode( aiMatrix4x4& transform, aiNode* node, const aiScene* scene )
    {
        aiMatrix4x4 nodeTransformation = transform * node->mTransformation;

        std::map< std::string, MeshPtr > newMeshes;

        // Process all the node's meshes (if any)
        for ( uint32_t i = 0; i < node->mNumMeshes; ++i )
        {
            aiMesh* mesh = scene->mMeshes[ node->mMeshes[ i ] ];
            std::string name = std::string( node->mName.C_Str() ) + "_" + mesh->mName.C_Str() + "_" +
                               std::to_string( i );
            name.erase( remove_if( name.begin(), name.end(), isspace ), name.end() );
            newMeshes[ name ] = processMesh( nodeTransformation, mesh, scene );
            newMeshes[ name ]->setName( node->mName.C_Str() );
        }

        // Then do the same for each of its children
        for ( uint32_t i = 0; i < node->mNumChildren; ++i )
        {
            newMeshes.merge( processNode( nodeTransformation, node->mChildren[ i ], scene ) );
        }

        return newMeshes;
    }

    AssimpParser::MeshPtr AssimpParser::processMesh( const aiMatrix4x4& transform, aiMesh* mesh, const aiScene* scene )
    {
        MeshPtr newMesh = nullptr;
        std::vector< Resources::Geometry::Vertex > newVertices;
        std::vector< uint32_t > newIndices;

        for ( uint32_t i = 0; i < mesh->mNumVertices; ++i )
        {
            aiVector3D position = transform * mesh->mVertices[ i ];
            aiVector3D texCoords = mesh->mTextureCoords[ 0 ] ? mesh->mTextureCoords[ 0 ][ i ] : aiVector3D( 0.0f, 0.0f, 0.0f );
            aiVector3D normal = transform * ( mesh->HasNormals() ? mesh->mNormals[ i ] : aiVector3D( 0.0f, 0.0f, 0.0f ) );
            aiVector3D tangent = transform * ( mesh->HasTangentsAndBitangents() ? mesh->mTangents[ i ] : aiVector3D( 0.0f, 0.0f, 0.0f ) );
            aiVector3D bitangent = transform * ( mesh->HasTangentsAndBitangents() ? mesh->mBitangents[ i ] : aiVector3D( 0.0f, 0.0f, 0.0f ) );

            newVertices.push_back
            ( {
                { position.x,  position.y, position.z },
                { texCoords.x, texCoords.y },
                { normal.x,    normal.y,    normal.z },
                { tangent.x,   tangent.y,   tangent.z },
                { bitangent.x, bitangent.y, bitangent.z }
            } );
        }

        for ( uint32_t faceID = 0; faceID < mesh->mNumFaces; ++faceID )
        {
            aiFace face = mesh->mFaces[ faceID ];

            for ( size_t indexID = 0; indexID < face.mNumIndices; ++indexID )
                newIndices.push_back( face.mIndices[ indexID ] );
        }

        std::shared_ptr< Resources::Geometry::Material > material = std::make_shared< Resources::Geometry::Material >();
        createMaterial( scene, material, mesh->mMaterialIndex );

        newMesh = std::make_unique< Resources::Geometry::Mesh >( newVertices, newIndices, material );

        return std::move( newMesh );
    }

    void AssimpParser::createMaterial( const aiScene* scene, std::shared_ptr< Resources::Geometry::Material >& newMaterial, int index )
    {
        aiMaterial* material = scene->mMaterials[ index ];
        
        if ( !material || material->GetTextureCount( aiTextureType_DIFFUSE ) == 0 )
        {
            newMaterial->loadAlbedo( "assets/textures/default_diff_texture.png" );
            return;
        }

        aiString diffuse;
        aiGetMaterialString( material, AI_MATKEY_TEXTURE_DIFFUSE( 0 ), &diffuse );
        fs::path diffusePath = m_filePath.parent_path() / diffuse.C_Str();
        newMaterial->loadAlbedo( diffusePath );

        if ( material->GetTextureCount( aiTextureType_NORMALS ) > 0 )
        {
            aiString normals;
            aiGetMaterialString( material, AI_MATKEY_TEXTURE_NORMALS( 0 ), &normals );
            fs::path normalsPath = m_filePath.parent_path() / normals.C_Str();
            newMaterial->loadNormal( normalsPath );
        }

        if ( material->GetTextureCount( aiTextureType_METALNESS ) > 0 )
        {
            aiString metallic;
            material->GetTexture( AI_MATKEY_METALLIC_TEXTURE, &metallic );
            fs::path metallicPath = m_filePath.parent_path() / metallic.C_Str();
            newMaterial->loadMetallic( metallicPath );
        }

        if ( material->GetTextureCount( aiTextureType_DIFFUSE ) > 0 )
        {
            aiString roughness;
            aiGetMaterialString( material, AI_MATKEY_TEXTURE_DIFFUSE( 0 ), &roughness );
            fs::path roughnessPath = m_filePath.parent_path() / roughness.C_Str();
            newMaterial->loadRougness( roughnessPath );
        }

        if ( material->GetTextureCount( aiTextureType_AMBIENT_OCCLUSION ) > 0 )
        {
            aiString ao;
            aiGetMaterialString( material, AI_MATKEY_TEXTURE_AMBIENT( 0 ), &ao );
            fs::path aoPath = m_filePath.parent_path() / ao.C_Str();
            newMaterial->loadRougness( aoPath );
        }
    }
}
