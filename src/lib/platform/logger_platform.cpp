/*
 *  Copyright (c) 2026, The OpenThread Authors.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of the copyright holder nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 *   Default weak implementation of the OpenThread lib/ platform logging hooks.
 *   Forwards calls to the OpenThread logging subsystem so that existing users
 *   see no behavior change.
 *
 *   Both functions are declared `OT_TOOL_WEAK` so that an application using the
 *   Spinel library or posix platform without OpenThread (or with a custom
 *   logging backend) can simply provide a non-weak definition with the same
 *   prototype and the linker will pick the application's implementation.
 */

#include "lib/platform/logger_platform.h"

#include <openthread/logging.h>
#include <openthread/platform/logging.h>

OT_TOOL_WEAK void PlatformLog(PlatformLogLevel aLogLevel, const char *aModuleName, const char *aFormat, va_list aArgs)
{
#if OPENTHREAD_CONFIG_LOG_PLATFORM
    otLogPlatArgs(static_cast<otLogLevel>(aLogLevel), aModuleName, aFormat, aArgs);
#else
    (void)aLogLevel;
    (void)aModuleName;
    (void)aFormat;
    (void)aArgs;
#endif
}

OT_TOOL_WEAK PlatformLogLevel PlatformGetLogLevel(void)
{
#if OPENTHREAD_CONFIG_LOG_PLATFORM
    return static_cast<PlatformLogLevel>(otLoggingGetLevel());
#else
    return PLATFORM_LOG_LEVEL_NONE;
#endif
}
