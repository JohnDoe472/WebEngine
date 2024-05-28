#include <string>

#include "house_scene.hpp"
#include "core/parsers/assimp_parser.hpp"
#include "core/services/service_locator.hpp"
#include "ui/material_selector.hpp"
#include "window/sdl2.hpp"

using namespace WebEngine;
using namespace WebEngine::Resources::Levels;

HouseScene::HouseScene() {
    initDefault();
}

void HouseScene::draw( float dt ) const{
    m_cameraMovement->handleInput( dt );
    m_defaultShader->bind();

    m_defaultShader->setMat4( "projection", m_camera->getProjectionMatrix() );
    m_defaultShader->setMat4( "view", m_camera->getViewMatrix() );
    m_defaultShader->setVec3( "viewPos", m_camera->getPosition() );
    m_defaultShader->setFloat( "material.shininess", 32.0f );

    m_defaultShader->setVec3( "dirLight.direction", m_directionalLight->getDirection() );
    m_defaultShader->setVec3( "dirLight.ambient", m_directionalLight->getAmbient() );
    m_defaultShader->setVec3( "dirLight.diffuse", m_directionalLight->getDiffuse() );
    m_defaultShader->setVec3( "dirLight.specular", m_directionalLight->getSpecular() );

    for ( size_t i = 0; i < m_pointLights.size(); ++i )
    {
        std::string name = "pointLights[" + std::to_string( i ) + "].";
        m_defaultShader->setVec3( name + "position", m_pointLights[ i ]->getPosition() );
        m_defaultShader->setVec3( name + "ambient", m_pointLights[ i ]->getAmbient() );
        m_defaultShader->setVec3( name + "diffuse", m_pointLights[ i ]->getDiffuse() );
        m_defaultShader->setVec3( name + "specular", m_pointLights[ i ]->getSpecular() );
        m_defaultShader->setVec3( name + "attenuation", m_pointLights[ i ]->getAttenuation() );
    }

    if ( m_model )
    {
        m_defaultShader->setMat4( "model", m_model->getModel() );
        m_model->draw( *m_defaultShader.get() );
    }

    m_defaultShader->unbind();

    m_lightSourceShader->bind();

    m_lightSourceShader->setMat4( "projection", m_camera->getProjectionMatrix() );
    m_lightSourceShader->setMat4( "view", m_camera->getViewMatrix() );

    for ( const PointLightPtr& ptr : m_pointLights )
        ptr->draw( *m_lightSourceShader.get() );

    m_lightSourceShader->unbind();
}

void HouseScene::initDefault() {
    std::shared_ptr< Window::SDL2 > window = Core::Services::ServiceLocator::get< Window::SDL2 >();

    glm::i32vec2 size = window->getWindowSize();
    m_camera = std::make_unique< Cameras::Camera >( size.x, size.y );
    m_camera->setPosition( glm::vec3( -4.82832, -7.94764, -19.2811 ) );
    m_camera->setRotation( glm::vec3( -0.137431, -2.30418, 0 ) );
    
    m_cameraMovement =  std::make_unique< Cameras::CameraMovement >( *m_camera.get() );
    m_cameraMovement->setMouseSensitivity( 0.07f );
    m_cameraMovement->setCameraMoveSpeed( 0.05f );


    Shaders::ShaderLocation location;
    location.VertexShaderPath = "shaders/external_model_vertex.vs";
    location.FragmentShaderPath = "shaders/external_model_fragment.fs";

    m_defaultShader = std::make_unique< Shaders::Shader >( location );

    location.VertexShaderPath = "shaders/light_source_vertex.vs";
    location.FragmentShaderPath = "shaders/light_source_fragment.fs";
    m_lightSourceShader = std::make_unique< Shaders::Shader >( location );

    Core::Parsers::AssimpParser parser;
    Core::Parsers::EAssimpParserFlags parserFlags = Core::Parsers::EAssimpParserFlags::eAPF_Triangulate           |
                                                    Core::Parsers::EAssimpParserFlags::eAPF_CalcTangentSpace      |
                                                    Core::Parsers::EAssimpParserFlags::eAPF_JoinIdenticalVertices |
                                                    Core::Parsers::EAssimpParserFlags::eAPF_GenSmoothNormals      |
                                                    Core::Parsers::EAssimpParserFlags::eAPF_FlipUVs               |
                                                    Core::Parsers::EAssimpParserFlags::eAPF_ImproveCacheLocality  |
                                                    Core::Parsers::EAssimpParserFlags::eAPF_FindInvalidData       |
                                                    Core::Parsers::EAssimpParserFlags::eAPF_GenUVCoords           |
                                                    Core::Parsers::EAssimpParserFlags::eAPF_FindInstances         |
                                                    Core::Parsers::EAssimpParserFlags::eAPF_OptimizeMeshes        |
                                                    Core::Parsers::EAssimpParserFlags::eAPF_Debone                |
                                                    Core::Parsers::EAssimpParserFlags::eAPF_GlobalScale;

    m_model = parser.loadModel( "assets/models/house/Room/Room.fbx", parserFlags );
    m_model->move( glm::vec3( 0.0f, -10.0, -15.0f ) );

    initLights();

    UI::MaterialSelector::clearMeshesList();
    UI::MaterialSelector::addMeshes( m_model->getMeshes() );

    initMaterials();

    for ( const auto& material : m_materials )
    {
        for ( const auto& mesh : m_model->getMeshes() )
        {
            UI::MaterialSelector::addMaterialForMesh( mesh.first, material.first, material.second );
        }
    }

    m_materialUpdateListenerID = UI::MaterialSelector::MaterialUpdateEvent.addListener( 
        std::bind( &HouseScene::updateMaterial, this, std::placeholders::_1, std::placeholders::_2 ) );
}

void HouseScene::initLights()
{
    m_directionalLight = std::make_unique< Lights::DirectionalLight >();
    m_directionalLight->setDirection( glm::vec3( 0.4f, 1.0f, 0.4f ) );
    m_directionalLight->setDiffuse( glm::vec3( 1.0f ) );
    m_directionalLight->setSpecular( glm::vec3( 0.05f ) );
    m_directionalLight->setColor( glm::vec3( 4.0f, 4.0f, 4.0f ) );

    PointLightPtr pointLight1 = std::make_unique< Lights::PointLight >();
    pointLight1->setDiffuse( glm::vec3( 0.8f ) );
    pointLight1->setSpecular( glm::vec3( 1.0f ) );
    pointLight1->setAttenuation( glm::vec3( 0.04f, 0.3f, 0.9f ) );
    pointLight1->setColor( glm::vec3( 0.0f, 0.0f, 0.0f ) );
    pointLight1->setPosition( glm::vec3( -0.00661984, -6.37535, -14.2463 ) );
    pointLight1->setScale( glm::vec3( 0.01f ) );
    m_pointLights[0] = std::move( pointLight1 );

    PointLightPtr pointLight2 = std::make_unique< Lights::PointLight >();
    pointLight2->setDiffuse( glm::vec3( 0.8f ) );
    pointLight2->setSpecular( glm::vec3( 1.0f ) );
    pointLight2->setAttenuation( glm::vec3( 0.005f, 0.2f, 0.3f ) );
    pointLight2->setColor( glm::vec3( 0.9f, 1.0f, 0.95f ) );
    pointLight2->setPosition( glm::vec3( -2.5, -8.5, -14 ) );
    pointLight2->setScale( glm::vec3( 0.01f ) );
    m_pointLights[1] = std::move( pointLight2 );

    PointLightPtr pointLight3 = std::make_unique< Lights::PointLight >();
    pointLight3->setDiffuse( glm::vec3( 0.8f ) );
    pointLight3->setSpecular( glm::vec3( 1.0f ) );
    pointLight3->setAttenuation( glm::vec3( 0.005f, 0.2f, 0.3f ) );
    pointLight3->setColor( glm::vec3( 0.9f, 1.0f, 0.95f ) );
    pointLight3->setPosition( glm::vec3( 2.5, -8.5, -14 ) );
    pointLight3->setScale( glm::vec3( 0.01f ) );
    m_pointLights[2] = std::move( pointLight3 );
}

void HouseScene::initMaterials()
{
    std::shared_ptr< Geometry::Material > artDeco = std::make_shared< Geometry::Material >( "Art Deco" );
    artDeco->loadAlbedo( "assets/materials/ArtDeco/ArtDeco_Albedo.png" );
    artDeco->loadNormal( "assets/materials/ArtDeco/ArtDeco_Normal.png" );
    artDeco->loadMetallic( "assets/materials/ArtDeco/ArtDeco_Metallic.png" );
    artDeco->loadRougness( "assets/materials/ArtDeco/ArtDeco_Roughness.png" );
    artDeco->loadAO( "assets/materials/ArtDeco/ArtDeco_AO.png" );
    m_materials[ "art_deco" ] = std::move( artDeco );

    std::shared_ptr< Geometry::Material > blackWood = std::make_shared< Geometry::Material >( "Black Wood" );
    blackWood->loadAlbedo( "assets/materials/BlackWood/BlackWood_Albedo.png" );
    blackWood->loadNormal( "assets/materials/BlackWood/BlackWood_Normal.png" );
    blackWood->loadRougness( "assets/materials/BlackWood/BlackWood_Roughness.png" );
    blackWood->loadAO( "assets/materials/BlackWood/BlackWood_AO.png" );
    m_materials[ "black_wood" ] = std::move( blackWood );

    std::shared_ptr< Geometry::Material > blueShibori = std::make_shared< Geometry::Material >( "Blue Shibori" );
    blueShibori->loadAlbedo( "assets/materials/BlueShibori/BlueShibori_Albedo.png" );
    blueShibori->loadNormal( "assets/materials/BlueShibori/BlueShibori_Normal.png" );
    m_materials[ "blue_shibori" ] = std::move( blueShibori );

    std::shared_ptr< Geometry::Material > brownWood = std::make_shared< Geometry::Material >( "Brown Wood" );
    brownWood->loadAlbedo( "assets/materials/BrownWood/BrownWood_Albedo.png" );
    brownWood->loadNormal( "assets/materials/BrownWood/BrownWood_Normal.png" );
    brownWood->loadMetallic( "assets/materials/BrownWood/BrownWood_Metallic.png" );
    brownWood->loadRougness( "assets/materials/BrownWood/BrownWood_Roughness.png" );
    brownWood->loadAO( "assets/materials/BrownWood/BrownWood_AO.png" );
    m_materials[ "brown_wood" ] = std::move( brownWood );

    std::shared_ptr< Geometry::Material > emeraldPeaks = std::make_shared< Geometry::Material >( "Emerald Peaks" );
    emeraldPeaks->loadAlbedo( "assets/materials/EmeraldPeaks/EmeraldPeaks_Albedo.png" );
    emeraldPeaks->loadNormal( "assets/materials/EmeraldPeaks/EmeraldPeaks_Normal.png" );
    emeraldPeaks->loadMetallic( "assets/materials/EmeraldPeaks/EmeraldPeaks_Metallic.png" );
    emeraldPeaks->loadRougness( "assets/materials/EmeraldPeaks/EmeraldPeaks_Roughness.png" );
    m_materials[ "emerald_peaks" ] = std::move( emeraldPeaks );

    std::shared_ptr< Geometry::Material > whiteWood = std::make_shared< Geometry::Material >( "White Wood" );
    whiteWood->loadAlbedo( "assets/materials/WhiteWood/WhiteWood_Albedo.png" );
    whiteWood->loadNormal( "assets/materials/WhiteWood/WhiteWood_Normal.png" );
    whiteWood->loadRougness( "assets/materials/WhiteWood/WhiteWood_Roughness.png" );
    whiteWood->loadAO( "assets/materials/WhiteWood/WhiteWood_AO.png" );
    m_materials[ "white_wood" ] = std::move( whiteWood );
}

void HouseScene::updateMaterial( std::string mesh, std::string material )
{
    Resources::Geometry::Mesh& meshRef = m_model->getMesh( mesh );
    meshRef.setMaterial( m_materials[ material ] );
}
