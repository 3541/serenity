/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include <AK/ByteBuffer.h>
#include <AK/DistinctNumeric.h>
#include <AK/String.h>
#include <AK/Types.h>

namespace Kernel {

class FS;
struct InodeMetadata;

TYPEDEF_DISTINCT_ORDERED_ID(unsigned, InodeIndex);

class InodeIdentifier {
public:
    InodeIdentifier() = default;
    InodeIdentifier(u32 fsid, InodeIndex inode)
        : m_fsid(fsid)
        , m_index(inode)
    {
    }

    bool is_valid() const { return m_fsid != 0 && m_index != 0; }

    u32 fsid() const { return m_fsid; }
    InodeIndex index() const { return m_index; }

    FS* fs();
    const FS* fs() const;

    bool operator==(const InodeIdentifier& other) const
    {
        return m_fsid == other.m_fsid && m_index == other.m_index;
    }

    bool operator!=(const InodeIdentifier& other) const
    {
        return m_fsid != other.m_fsid || m_index != other.m_index;
    }

    String to_string() const { return String::formatted("{}:{}", m_fsid, m_index); }

private:
    u32 m_fsid { 0 };
    InodeIndex m_index { 0 };
};

inline const LogStream& operator<<(const LogStream& stream, const InodeIdentifier& value)
{
    stream << value.fsid() << ':' << value.index().value();
    return stream;
}

}

template<>
struct AK::Formatter<Kernel::InodeIdentifier> : AK::Formatter<FormatString> {
    void format(FormatBuilder& builder, Kernel::InodeIdentifier value)
    {
        return AK::Formatter<FormatString>::format(builder, "{}:{}", value.fsid(), value.index());
    }
};

template<>
struct AK::Formatter<Kernel::InodeIndex> : AK::Formatter<FormatString> {
    void format(FormatBuilder& builder, Kernel::InodeIndex value)
    {
        return AK::Formatter<FormatString>::format(builder, "{}", value.value());
    }
};
