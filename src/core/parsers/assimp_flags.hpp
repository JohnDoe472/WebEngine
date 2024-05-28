#pragma once
#ifndef WEB_ENGINE_CORE_PARSERS_PARSER_FLAGS_HPP_
#define WEB_ENGINE_CORE_PARSERS_PARSER_FLAGS_HPP_

#include <stdint.h>

namespace WebEngine::Core::Parsers
{
    enum class EAssimpParserFlags : uint32_t
    {
        eAPF_None                     = 0x0,
        eAPF_CalcTangentSpace         = 0x1,
        eAPF_JoinIdenticalVertices    = 0x2,
        eAPF_MakeLeftHanded           = 0x4,
        eAPF_Triangulate              = 0x8,
        eAPF_RemoveComponent          = 0x10,
        eAPF_GenNormals               = 0x20,
        eAPF_GenSmoothNormals         = 0x40,
        eAPF_SplitLargeMeshes         = 0x80,
        eAPF_PreTransformVertices     = 0x100,
        eAPF_LimitBoneWeights         = 0x200,
        eAPF_ValidateDataStructure    = 0x400,
        eAPF_ImproveCacheLocality     = 0x800,
        eAPF_RemoveRedundantMaterials = 0x1000,
        eAPF_FixInfacingNormals       = 0x2000,
        eAPF_SortByPtype              = 0x8000,
        eAPF_FindDegenerates          = 0x10000,
        eAPF_FindInvalidData          = 0x20000,
        eAPF_GenUVCoords              = 0x40000,
        eAPF_TransformUVCoords        = 0x80000,
        eAPF_FindInstances            = 0x100000,
        eAPF_OptimizeMeshes           = 0x200000,
        eAPF_OptimizeGraph            = 0x400000,
        eAPF_FlipUVs                  = 0x800000,
        eAPF_FlipWindingOrder         = 0x1000000,
        eAPF_SplitByBoneCount         = 0x2000000,
        eAPF_Debone                   = 0x4000000,
        eAPF_GlobalScale              = 0x8000000,
        eAPF_EmbedTextures            = 0x10000000,
        eAPF_ForceGenNormals          = 0x20000000,
        eAPF_DropNormals              = 0x40000000,
        eAPF_GenBoundingBoxes         = 0x80000000
    };

    inline EAssimpParserFlags operator~   (EAssimpParserFlags  a) { return (EAssimpParserFlags)~(int)a; }
    inline EAssimpParserFlags operator|   (EAssimpParserFlags  a, EAssimpParserFlags b) { return (EAssimpParserFlags)((int)a | (int)b); }
    inline EAssimpParserFlags operator&   (EAssimpParserFlags  a, EAssimpParserFlags b) { return (EAssimpParserFlags)((int)a & (int)b); }
    inline EAssimpParserFlags operator^   (EAssimpParserFlags  a, EAssimpParserFlags b) { return (EAssimpParserFlags)((int)a ^ (int)b); }
    inline EAssimpParserFlags& operator|= (EAssimpParserFlags& a, EAssimpParserFlags b) { return (EAssimpParserFlags&)((int&)a |= (int)b); }
    inline EAssimpParserFlags& operator&= (EAssimpParserFlags& a, EAssimpParserFlags b) { return (EAssimpParserFlags&)((int&)a &= (int)b); }
    inline EAssimpParserFlags& operator^= (EAssimpParserFlags& a, EAssimpParserFlags b) { return (EAssimpParserFlags&)((int&)a ^= (int)b); }
}

#endif // WEB_ENGINE_CORE_PARSERS_PARSER_FLAGS_HPP_
