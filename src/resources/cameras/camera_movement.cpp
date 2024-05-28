#include "resources/cameras/camera_movement.hpp"
#include "core/services/service_locator.hpp"
#include "window/sdl2.hpp"

#include <glm/gtc/quaternion.hpp>

namespace WebEngine::Resources::Cameras
{
    CameraMovement::CameraMovement( Camera& camera )
        : m_camera { camera }
    {
        std::shared_ptr< Window::SDL2 > window = Core::Services::ServiceLocator::get< Window::SDL2 >();

        if ( window )
        {
            m_keyPressedListener = window->keyPressedEvent.addListener( [ this ]( Window::Input::EKey key )
            {
                m_keyEvents[ key ] = Window::Input::EKeyState::eKS_Pressed;
            } );

            m_keyReleasedListener = window->keyReleasedEvent.addListener( [ this ]( Window::Input::EKey key )
            {
                m_keyEvents[ key ] = Window::Input::EKeyState::eKS_Released;
            } );

            m_mouseButtonPressedListener = window->mouseButtonPressedEvent.addListener( std::bind( &CameraMovement::onMouseButtonPressed, this, std::placeholders::_1 ) );
            m_mouseButtonReleasedListener = window->mouseButtonReleasedEvent.addListener( std::bind( &CameraMovement::onMouseButtonReleased, this, std::placeholders::_1 ) );
        }
    }

    CameraMovement::~CameraMovement()
    {
        std::shared_ptr< Window::SDL2 > window = Core::Services::ServiceLocator::get< Window::SDL2 >();

        if ( window )
        {
            window->keyPressedEvent.removeListener( m_keyPressedListener );
            window->keyReleasedEvent.removeListener( m_keyReleasedListener );
            window->mouseButtonPressedEvent.removeListener( m_mouseButtonPressedListener );
            window->mouseButtonReleasedEvent.removeListener( m_mouseButtonReleasedListener );
        }
    }
    
    bool CameraMovement::checkKeyState( Window::Input::EKey key, Window::Input::EKeyState state )
    {
        return m_keyEvents.count( key ) && ( m_keyEvents[ key ] == state );
    }

    void CameraMovement::handleInput( float dt )
    {
        if ( m_leftButtonPressed )
        {
            std::shared_ptr< Window::SDL2 > window = Core::Services::ServiceLocator::get< Window::SDL2 >();

            glm::i32vec2 mousePos = window->getMousePosition();

            if ( m_mouseLastPos.x > -1 && m_mouseLastPos.y > -1 )
            {
                glm::vec2 mouseOffset = mousePos - m_mouseLastPos;
                mouseOffset *= m_mouseSensitivity;
                m_camera.rotate( glm::vec3( -glm::radians( mouseOffset.y ), -glm::radians( mouseOffset.x ), 0.0f ) );
            }

            m_mouseLastPos = mousePos;
        }

        const glm::vec3& rotation = m_camera.getRotation();
        float velocity = m_cameraMoveSpeed * ( checkKeyState( Window::Input::EKey::eK_LShift, Window::Input::EKeyState::eKS_Pressed ) ? 2.0f : 1.0f );

        if ( checkKeyState( Window::Input::EKey::eK_W, Window::Input::EKeyState::eKS_Pressed ) )
            m_camera.move( glm::quat( rotation ) * glm::vec3( 0.0f, 0.0f, -velocity ) );
        if ( checkKeyState( Window::Input::EKey::eK_S, Window::Input::EKeyState::eKS_Pressed ) )
            m_camera.move( glm::quat( rotation ) * glm::vec3( 0.0f, 0.0f, velocity ) );
        if ( checkKeyState( Window::Input::EKey::eK_A, Window::Input::EKeyState::eKS_Pressed ) )
            m_camera.move( glm::quat( rotation ) * glm::vec3( -velocity, 0.0f, 0.0f ) );
        if ( checkKeyState( Window::Input::EKey::eK_D, Window::Input::EKeyState::eKS_Pressed ) )
            m_camera.move( glm::quat( rotation ) * glm::vec3( velocity, 0.0f, 0.0f ) );
        if ( checkKeyState( Window::Input::EKey::eK_E, Window::Input::EKeyState::eKS_Pressed ) )
            m_camera.move( glm::quat( rotation ) * glm::vec3( 0.0f, velocity, 0.0f ) );
        if ( checkKeyState( Window::Input::EKey::eK_Q, Window::Input::EKeyState::eKS_Pressed ) )
            m_camera.move( glm::quat( rotation ) * glm::vec3( 0.0f, -velocity, 0.0f ) );

        //std::cout << "Camera position: " << m_camera.getPosition().x << ", " << m_camera.getPosition().y << ", " << m_camera.getPosition().z << std::endl;
        //std::cout << "Camera rotation: " << m_camera.getRotation().x << ", " << m_camera.getRotation().y << ", " << m_camera.getRotation().z << std::endl;
    }

    void CameraMovement::onMouseButtonPressed( Window::Input::EMouseButton button )
    {
        std::shared_ptr< Window::SDL2 > window = Core::Services::ServiceLocator::get< Window::SDL2 >();

        if ( button == Window::Input::EMouseButton::eMB_Left )
            m_leftButtonPressed = true;

        m_mouseLastPos = window->getMousePosition();
    }

    void CameraMovement::onMouseButtonReleased( Window::Input::EMouseButton button )
    {
        std::shared_ptr< Window::SDL2 > window = Core::Services::ServiceLocator::get< Window::SDL2 >();

        if ( button == Window::Input::EMouseButton::eMB_Left )
            m_leftButtonPressed = false;
    }
}
