#pragma once

#include <cstdint>
#include <string>

#include <mega/common/node_info_forward.h>

#include <mega/types.h>

namespace mega
{
namespace common
{

struct NodeInfo
{
    NodeHandle mHandle;
    bool mIsDirectory = false;
    m_time_t mModified = 0;
    std::string mName;
    NodeHandle mParentHandle;
    accesslevel_t mPermissions = ACCESS_UNKNOWN;
    m_off_t mSize = 0;
}; // NodeInfo

} // common
} // mega

