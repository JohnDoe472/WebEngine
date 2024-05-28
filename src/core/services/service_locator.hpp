#pragma once
#ifndef WEB_ENGINE_CORE_SERVICES_SERVICE_LOCATOR_HPP_
#define WEB_ENGINE_CORE_SERVICES_SERVICE_LOCATOR_HPP_

#include <memory>
#include <unordered_map>

#include "service_interface.hpp"

namespace WebEngine::Core::Services
{
    class ServiceLocator
    {
    public:
        template< typename T, typename... Args >
        static std::shared_ptr< T > provide( Args&&... args )
        {
            static_assert( std::is_base_of< IService, T >::value, "T must inherit from IService" );
            
            // size_t hash = typeid( T ).hash_code();
            std::type_index hash = std::type_index( typeid ( T ) );

            if ( !m_services.count( hash ) )
                m_services.emplace( hash, std::make_shared< T >( args... ) );

            return std::static_pointer_cast< T >( m_services.find( hash )->second );
        }

        template< typename T >
        static inline const std::shared_ptr< T > get()
        {
            static_assert( std::is_base_of< IService, T >::value, "T must inherit from IService" );

            auto instance = m_services.find( std::type_index( typeid ( T ) ) );

            if ( instance != m_services.end() )
                return std::static_pointer_cast< T >( instance->second );

            return nullptr;
        }

        template< typename T >
        void unregisterService()
        {
            static_assert( std::is_base_of< IService, T >::value, "T must inherit from IService" );

            // size_t hash = typeid( T ).hash_code();
            std::type_index hash = std::type_index( typeid ( T ) );

            if ( m_services.count( hash ) )
                m_services.erase( hash );
        }

        private:
            static inline std::unordered_map< std::type_index, std::shared_ptr< IService > > m_services;
    };
}

#endif // WEB_ENGINE_CORE_SERVICES_SERVICE_LOCATOR_HPP_
