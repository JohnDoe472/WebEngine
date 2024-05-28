#include <iostream>
#include <stdexcept>

#include "core/engine.hpp"

int main( int argc, char* argv[] )
{
    try
    {
        WebEngine::Core::Engine engine;
        engine.run();
    }
    catch( std::exception& ex )
    {
        std::cout << "ERROR: " << ex.what() << std::endl;
        return -1;
    }

    return 0;
}
