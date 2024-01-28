
#pragma once

#include <memory>
#include <string>
#include "nettools/UnixDataSocket.hh"

namespace nettools {
    std::shared_ptr<nettools::UnixDataSocket> connectToSocket(std::string const& path);
}

