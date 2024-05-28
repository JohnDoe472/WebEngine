#pragma once
#ifndef WEB_ENGINE_RESOURCES_GEOMETRY_VERTEX_HPP_
#define WEB_ENGINE_RESOURCES_GEOMETRY_VERTEX_HPP_

#include <array>

namespace WebEngine::Resources::Geometry
{
    struct Vertex
    {
        std::array< float, 3 > Position;
        std::array< float, 2 > TexCoords;
        std::array< float, 3 > Normals;
        std::array< float, 3 > Tangent;
        std::array< float, 3 > Bitangent;
    };
}

#endif // WEB_ENGINE_RESOURCES_GEOMETRY_VERTEX_HPP_