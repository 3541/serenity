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

#include <AK/Debug.h>
#include <LibCore/NetworkJob.h>
#include <LibCore/NetworkResponse.h>

namespace Core {

NetworkJob::NetworkJob(OutputStream& output_stream)
    : m_output_stream(output_stream)
{
}

NetworkJob::~NetworkJob()
{
}

void NetworkJob::start()
{
}

void NetworkJob::shutdown()
{
}

void NetworkJob::did_finish(NonnullRefPtr<NetworkResponse>&& response)
{
    // NOTE: We protect ourselves here, since the on_finish callback may otherwise
    //       trigger destruction of this job somehow.
    NonnullRefPtr<NetworkJob> protector(*this);

    m_response = move(response);
    dbgln_if(CNETWORKJOB_DEBUG, "{} job did_finish", *this);
    VERIFY(on_finish);
    on_finish(true);
    shutdown();
}

void NetworkJob::did_fail(Error error)
{
    // NOTE: We protect ourselves here, since the on_finish callback may otherwise
    //       trigger destruction of this job somehow.
    NonnullRefPtr<NetworkJob> protector(*this);

    m_error = error;
    dbgln_if(CNETWORKJOB_DEBUG, "{}{{{:p}}} job did_fail! error: {} ({})", class_name(), this, (unsigned)error, to_string(error));
    VERIFY(on_finish);
    on_finish(false);
    shutdown();
}

void NetworkJob::did_progress(Optional<u32> total_size, u32 downloaded)
{
    // NOTE: We protect ourselves here, since the callback may otherwise
    //       trigger destruction of this job somehow.
    NonnullRefPtr<NetworkJob> protector(*this);

    if (on_progress)
        on_progress(total_size, downloaded);
}

const char* to_string(NetworkJob::Error error)
{
    switch (error) {
    case NetworkJob::Error::ProtocolFailed:
        return "ProtocolFailed";
    case NetworkJob::Error::ConnectionFailed:
        return "ConnectionFailed";
    case NetworkJob::Error::TransmissionFailed:
        return "TransmissionFailed";
    case NetworkJob::Error::Cancelled:
        return "Cancelled";
    default:
        return "(Unknown error)";
    }
}

}
