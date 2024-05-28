#pragma once
#ifndef WEB_ENGINE_CORE_EVENTING_EVENT_HPP_
#define WEB_ENGINE_CORE_EVENTING_EVENT_HPP_

#include <functional>
#include <unordered_map>

#include <iostream>

namespace WebEngine::Core::Eventing
{
    using ListenerID = uint64_t;

    template<typename... ArgTypes>
    class Event
    {
    public:
        using Callback = std::function< void( ArgTypes... ) >;

        ListenerID operator+=( Callback callback )
        {
            return addListener( callback );
        }

        bool operator-=( ListenerID listenerID )
        {
            return removeListener( listenerID );
        }

        ListenerID addListener( Callback callback )
        {
            ListenerID listenerID = m_availableListenerID++;
            m_callbacks.emplace( listenerID, callback );
            return listenerID;
        }

        bool removeListener( ListenerID listenerID )
        {
            return m_callbacks.erase( listenerID ) != 0;
        }
        
        void removeAllListeners()
        {
            m_callbacks.clear();
        }

        uint64_t getListenerCount()
        {
            return m_callbacks.size();
        }

        void invoke( ArgTypes... args )
        {
            for ( auto const& [ key, value ] : m_callbacks )
                value( args... );
        }

    private:
        std::unordered_map< ListenerID, Callback > m_callbacks;
        ListenerID m_availableListenerID = 0;
    };
}

#endif // WEB_ENGINE_CORE_EVENTING_EVENT_HPP_
