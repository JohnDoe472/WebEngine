#pragma once
#ifndef WEB_ENGINE_CORE_SERVICES_SERVICE_INTERFACE_HPP_
#define WEB_ENGINE_CORE_SERVICES_SERVICE_INTERFACE_HPP_

#include <typeindex>

namespace WebEngine::Core::Services
{
    class IService
    {
    public:
        virtual ~IService() = default;
    };
}

#endif // WEB_ENGINE_CORE_SERVICES_SERVICE_INTERFACE_HPP_
