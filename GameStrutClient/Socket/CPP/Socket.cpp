#include "Socket.hpp"
#include "../../../Blob/CPP/Blob.hpp"

namespace NumbatLogic
{
    bool Socket::Send(Blob* pBlob)
    {
        // Base class implementation - should be overridden by derived classes
        return false;
    }

    Blob* Socket::Receive()
    {
        // Base class implementation - should be overridden by derived classes
        return NULL;
    }
}
