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

void HouseScene::draw( float dt ) const
{
    m_cameraMovement->handleInput( dt );
    m_defaultShader->bind();

    m_defaultShader->setMat4( "projection", m_camera->getProjectionMatrix() );
    m_defaultShader->setMat4( "view", m_camera->getViewMatrix() );
    m_defaultShader->setVec3( "camPos", m_camera->getPosition() );

    for ( size_t i = 0; i < m_pointLights.size(); ++i )
    {
        std::string name = "lights[" + std::to_string( i ) + "].";
        m_defaultShader->setVec3( name + "position", m_pointLights[ i ]->getPosition() );
        m_defaultShader->setVec3( name + "color", m_pointLights[ i ]->getColor() );
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

    glDepthFunc( GL_LEQUAL ); // change depth function so depth test passes when values are equal to depth buffer's content
    m_skyboxShader->bind();

    m_skyboxShader->setMat4( "projection", m_camera->getProjectionMatrix() );
    glm::mat4 view = glm::mat4( glm::mat3( m_camera->getViewMatrix() ) );
    m_skyboxShader->setMat4( "view", view);

    m_skybox->draw( *m_skyboxShader.get() );

    m_skyboxShader->unbind();
    glDepthFunc( GL_LESS ); // set depth function back to default
}

void HouseScene::initDefault()
{
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
    
    for ( const auto& mesh : m_model->getMeshes() )
    {
        if ( mesh.first.find( "Wall" ) != std::string::npos ||
             mesh.first.find( "Ceiling" ) != std::string::npos || 
             mesh.first.find( "Floor" ) != std::string::npos )
        {
            UI::MaterialSelector::addMesh( mesh.first, mesh.second );
        }
    }

    initMaterials();

    for ( const auto& mesh : m_model->getMeshes() )
    {
        if ( mesh.first.find( "Wall" ) != std::string::npos ||
             mesh.first.find( "Ceiling" ) != std::string::npos )
        {
            UI::MaterialSelector::addMaterialForMesh( mesh.first, "art_deco", m_materials[ "art_deco" ] );
            UI::MaterialSelector::addMaterialForMesh( mesh.first, "emerald_peaks", m_materials[ "emerald_peaks" ] );
            UI::MaterialSelector::addMaterialForMesh( mesh.first, "plaster_paint_light", m_materials[ "plaster_paint_light" ] );
            UI::MaterialSelector::addMaterialForMesh( mesh.first, "plaster_paint_beige", m_materials[ "plaster_paint_beige" ] );
            UI::MaterialSelector::addMaterialForMesh( mesh.first, "dark_gold_marble", m_materials[ "dark_gold_marble" ] );
        }
        else if ( mesh.first.find( "Floor" ) != std::string::npos )
        {
            UI::MaterialSelector::addMaterialForMesh( mesh.first, "brown_wood", m_materials[ "brown_wood" ] );
            UI::MaterialSelector::addMaterialForMesh( mesh.first, "white_wood", m_materials[ "white_wood" ] );
            UI::MaterialSelector::addMaterialForMesh( mesh.first, "dark_tiles", m_materials[ "dark_tiles" ] );
            UI::MaterialSelector::addMaterialForMesh( mesh.first, "white_tiles", m_materials[ "white_tiles" ] );
            UI::MaterialSelector::addMaterialForMesh( mesh.first, "dark_light_tiles", m_materials[ "dark_light_tiles" ] );
        }
    }

    m_materialUpdateListenerID = UI::MaterialSelector::MaterialUpdateEvent.addListener( 
        std::bind( &HouseScene::updateMaterial, this, std::placeholders::_1, std::placeholders::_2 ) );

    initSkybox();
}

void HouseScene::initLights()
{
    PointLightPtr backLight = std::make_unique< Lights::PointLight >();
    backLight->setAttenuation( glm::vec3( 0.0f, 0.022f, 1.0019f ) );
    backLight->setColor( glm::vec3( 15.0f, 15.0f, 15.0f ) );
    backLight->setPosition( glm::vec3( -0.0f, -6.8, -17.0f ) );
    backLight->setScale( glm::vec3( 0.00001f ) );
    m_pointLights[0] = std::move( backLight );

    PointLightPtr rightLamp = std::make_unique< Lights::PointLight >();
    rightLamp->setAttenuation( glm::vec3( 0.0f, 0.022f, 0.5019f ) );
    rightLamp->setColor( glm::vec3( 10.0f, 10.0f, 10.0f ) );
    rightLamp->setPosition( glm::vec3( -2.34, -8.73, -13.78f ) );
    rightLamp->setScale( glm::vec3( 0.00001f ) );
    m_pointLights[1] = std::move( rightLamp );

    PointLightPtr leftLamp = std::make_unique< Lights::PointLight >();
    leftLamp->setAttenuation( glm::vec3( 0.0f, 0.022f, 0.5019f ) );
    leftLamp->setColor( glm::vec3( 10.0f, 10.0f, 10.0f ) );
    leftLamp->setPosition( glm::vec3( 2.34, -8.73, -13.78f ) );
    leftLamp->setScale( glm::vec3( 0.00001f ) );
    m_pointLights[2] = std::move( leftLamp );
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

    // DarkLightTiles
    std::shared_ptr< Geometry::Material > darkLightTiles = std::make_shared< Geometry::Material >( "Dark Light Tiles" );
    darkLightTiles->loadAlbedo( "assets/materials/DarkLightTiles/DarkLightTiles_Albedo.jpg" );
    darkLightTiles->loadNormal( "assets/materials/DarkLightTiles/DarkLightTiles_Normal.jpg" );
    darkLightTiles->loadRougness( "assets/materials/DarkLightTiles/DarkLightTiles_Roughness.jpg" );
    darkLightTiles->loadAO( "assets/materials/DarkLightTiles/DarkLightTiles_AO.jpg" );
    m_materials[ "dark_light_tiles" ] = std::move( darkLightTiles );
    
    // PlasterPaintLight
    std::shared_ptr< Geometry::Material > plasterPaintLight = std::make_shared< Geometry::Material >( "Plaster Paint Light" );
    plasterPaintLight->loadAlbedo( "assets/materials/PlasterPaintLight/PlasterPaintLight_Albedo.jpg" );
    plasterPaintLight->loadNormal( "assets/materials/PlasterPaintLight/PlasterPaintLight_Normal.jpg" );
    plasterPaintLight->loadRougness( "assets/materials/PlasterPaintLight/PlasterPaintLight_Roughness.jpg" );
    plasterPaintLight->loadAO( "assets/materials/PlasterPaintLight/PlasterPaintLight_AO.jpg" );
    m_materials[ "plaster_paint_light" ] = std::move( plasterPaintLight );

    // PlasterPaintBeige
    std::shared_ptr< Geometry::Material > plasterPaintBeige = std::make_shared< Geometry::Material >( "Plaster Paint Beige" );
    plasterPaintBeige->loadAlbedo( "assets/materials/PlasterPaintBeige/PlasterPaintBeige_Albedo.jpg" );
    plasterPaintBeige->loadNormal( "assets/materials/PlasterPaintBeige/PlasterPaintBeige_Normal.jpg" );
    plasterPaintBeige->loadRougness( "assets/materials/PlasterPaintBeige/PlasterPaintBeige_Roughness.jpg" );
    plasterPaintBeige->loadAO( "assets/materials/PlasterPaintBeige/PlasterPaintBeige_AO.jpg" );
    m_materials[ "plaster_paint_beige" ] = std::move( plasterPaintBeige );

    // DarkGoldMarble
    std::shared_ptr< Geometry::Material > darkGoldMarble = std::make_shared< Geometry::Material >( "Dark Gold Marble" );
    darkGoldMarble->loadAlbedo( "assets/materials/DarkGoldMarble/DarkGoldMarble_Albedo.jpg" );
    darkGoldMarble->loadNormal( "assets/materials/DarkGoldMarble/DarkGoldMarble_Normal.jpg" );
    darkGoldMarble->loadRougness( "assets/materials/DarkGoldMarble/DarkGoldMarble_Roughness.jpg" );
    darkGoldMarble->loadMetallic( "assets/materials/DarkGoldMarble/DarkGoldMarble_Metallic.jpg" );
    darkGoldMarble->loadAO( "assets/materials/DarkGoldMarble/DarkGoldMarble_AO.jpg" );
    m_materials[ "dark_gold_marble" ] = std::move( darkGoldMarble );

    // DarkTiles
    std::shared_ptr< Geometry::Material > darkTiles = std::make_shared< Geometry::Material >( "Dark Tiles" );
    darkTiles->loadAlbedo( "assets/materials/DarkTiles/DarkTiles_Albedo.jpg" );
    darkTiles->loadNormal( "assets/materials/DarkTiles/DarkTiles_Normal.jpg" );
    darkTiles->loadRougness( "assets/materials/DarkTiles/DarkTiles_Roughness.jpg" );
    darkTiles->loadAO( "assets/materials/DarkTiles/DarkTiles_AO.jpg" );
    m_materials[ "dark_tiles" ] = std::move( darkTiles );

    // WhiteTiles
    std::shared_ptr< Geometry::Material > whiteTiles = std::make_shared< Geometry::Material >( "White Tiles" );
    whiteTiles->loadAlbedo( "assets/materials/WhiteTiles/WhiteTiles_Albedo.jpg" );
    whiteTiles->loadNormal( "assets/materials/WhiteTiles/WhiteTiles_Normal.jpg" );
    whiteTiles->loadRougness( "assets/materials/WhiteTiles/WhiteTiles_Roughness.jpg" );
    whiteTiles->loadAO( "assets/materials/WhiteTiles/WhiteTiles_AO.jpg" );
    m_materials[ "white_tiles" ] = std::move( whiteTiles );
}

void HouseScene::updateMaterial( std::string mesh, std::string material )
{
    Resources::Geometry::Mesh& meshRef = m_model->getMesh( mesh );
    meshRef.setMaterial( m_materials[ material ] );
}

void HouseScene::initSkybox()
{
    m_skyboxShader = std::make_unique< Shaders::Shader >( Shaders::ShaderLocation{"shaders/skybox_vertex.vs", "shaders/skybox_fragment.fs"} );

    std::vector< std::filesystem::path > faces
    {
        "assets/skyboxes/skybox1/right.jpg",
        "assets/skyboxes/skybox1/left.jpg",
        "assets/skyboxes/skybox1/top.jpg",
        "assets/skyboxes/skybox1/bottom.jpg",
        "assets/skyboxes/skybox1/front.jpg",
        "assets/skyboxes/skybox1/back.jpg"
    };

    m_skybox = std::make_unique< Objects::Skybox >( faces );
}