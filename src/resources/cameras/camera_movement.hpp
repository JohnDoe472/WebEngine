#pragma once
#ifndef WEB_ENGINE_RESOURCES_CAMERAS_CAMERA_MOVEMENT_HPP_
#define WEB_ENGINE_RESOURCES_CAMERAS_CAMERA_MOVEMENT_HPP_

#include <map>
#include <memory>

#include <glm/glm.hpp>

#include "core/eventing/event.hpp"
#include "resources/cameras/camera.hpp"
#include "window/input/key.hpp"
#include "window/input/key_state.hpp"
#include "window/input/mouse_button.hpp"

namespace WebEngine::Resources::Cameras
{
    class CameraMovement
    {
    public:
        CameraMovement( Camera& camera );
        ~CameraMovement();

        CameraMovement( const CameraMovement& other )             = delete;
        CameraMovement( CameraMovement&& other )                  = delete;
        CameraMovement& operator=( const CameraMovement& other )  = delete;
        CameraMovement& operator=( const CameraMovement&& other ) = delete;

        void handleInput( float dt );

        void setCameraMoveSpeed( float speed ) { m_cameraMoveSpeed = speed; }
        void setMouseSensitivity( float sensitivity ) { m_mouseSensitivity = sensitivity; }

    private:
        void onMouseButtonPressed( Window::Input::EMouseButton button );
        void onMouseButtonReleased( Window::Input::EMouseButton button );
        bool checkKeyState( Window::Input::EKey key, Window::Input::EKeyState state );

        Camera& m_camera;

        Core::Eventing::ListenerID m_keyPressedListener = 0;
        Core::Eventing::ListenerID m_keyReleasedListener = 0;
        Core::Eventing::ListenerID m_mouseButtonPressedListener;
        Core::Eventing::ListenerID m_mouseButtonReleasedListener;

        std::unordered_map< Window::Input::EKey, Window::Input::EKeyState > m_keyEvents;
        bool m_leftButtonPressed = false;
        glm::i32vec2 m_mouseLastPos = glm::vec2( -1 );

        float m_cameraMoveSpeed = 0.15f;
        float m_mouseSensitivity = 0.1f;
    };
}

#endif // WEB_ENGINE_RESOURCES_CAMERAS_CAMERA_MOVEMENT_HPP_
