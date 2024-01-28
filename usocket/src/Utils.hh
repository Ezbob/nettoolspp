
#pragma once

#include <sys/un.h>
#include <string>

namespace nettools {

    struct sockaddr_un make_address(std::string const &path);

}

