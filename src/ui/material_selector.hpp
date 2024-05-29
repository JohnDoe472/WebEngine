#pragma once
#ifndef WEB_ENGINE_UI_MATERIAL_SELECTOR_HPP_
#define WEB_ENGINE_UI_MATERIAL_SELECTOR_HPP_

#include <memory>
#include <vector>
#include <string>

#include "core/eventing/event.hpp"
#include "resources/geometry/material.hpp"
#include "resources/objects/model.hpp"

namespace WebEngine::UI
{
    class MaterialSelector
    {
    public:
        static inline Core::Eventing::Event< std::string, std::string > MaterialUpdateEvent;

        static void addMeshes( const std::map< std::string, std::unique_ptr< Resources::Geometry::Mesh > >& meshes );
        static void addMesh( const std::string& id, const std::unique_ptr< Resources::Geometry::Mesh >& mesh );
        static void addMaterialForMesh( const std::string& meshID, const std::string& materialID, const std::shared_ptr< Resources::Geometry::Material >& material );
        static void setMaterial( std::string mesh, std::string material );
        static void clearMeshesList();
    };
}

#endif // WEB_ENGINE_UI_MATERIAL_SELECTOR_HPP_
