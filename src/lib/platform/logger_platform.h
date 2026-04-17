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
 *   Platform logging abstraction for the OpenThread library layer.
 *
 *   This header defines the logging interface used by `lib/platform/exit_code.h`
 *   and is shared by all consumers of the lib/ layer (spinel, posix, etc.).
 *
 *   A default weak implementation (`logger_platform.cpp`) forwards calls to
 *   OpenThread's `otLogPlatArgs()` / `otLoggingGetLevel()`. Applications that
 *   do not depend on the OpenThread logging subsystem can override `PlatformLog`
 *   and `PlatformGetLogLevel` with their own non-weak implementations.
 */

#ifndef OT_LIB_PLATFORM_LOGGER_PLATFORM_H_
#define OT_LIB_PLATFORM_LOGGER_PLATFORM_H_

#include <stdarg.h>
#include <stdint.h>

#include <openthread/platform/toolchain.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup lib-platform-logging
 *
 * @brief
 *   Platform logging abstraction for the OpenThread lib/ layer.
 *
 * @{
 */

/** Log level: no logging.    */
#define PLATFORM_LOG_LEVEL_NONE 0
/** Log level: critical.      */
#define PLATFORM_LOG_LEVEL_CRIT 1
/** Log level: warning.       */
#define PLATFORM_LOG_LEVEL_WARN 2
/** Log level: notice.        */
#define PLATFORM_LOG_LEVEL_NOTE 3
/** Log level: informational. */
#define PLATFORM_LOG_LEVEL_INFO 4
/** Log level: debug.         */
#define PLATFORM_LOG_LEVEL_DEBG 5

/**
 * Represents the log level used by the OpenThread lib/ platform logging layer.
 *
 * The numeric values intentionally match OpenThread's `OT_LOG_LEVEL_*` so a
 * platform may forward the value directly to `otLogPlatArgs()` without
 * translation.
 */
typedef int PlatformLogLevel;

/**
 * Emits a log message from the OpenThread lib/ layer.
 *
 * A default weak implementation is provided in `logger_platform.cpp` that
 * forwards the call to OpenThread's `otLogPlatArgs()`. Applications that want
 * to use the Spinel library or posix platform without the OpenThread logging
 * subsystem can override this function (non-weak) with their own backend.
 *
 * @param[in] aLogLevel     The log level (one of `PLATFORM_LOG_LEVEL_*`).
 * @param[in] aModuleName   The module name, NUL-terminated.
 * @param[in] aFormat       The printf-style format string.
 * @param[in] aArgs         Arguments for @p aFormat.
 */
void PlatformLog(PlatformLogLevel aLogLevel, const char *aModuleName, const char *aFormat, va_list aArgs)
    OT_TOOL_PRINTF_STYLE_FORMAT_ARG_CHECK(3, 0);

/**
 * Returns the current maximum log level for the OpenThread lib/ layer.
 *
 * A default weak implementation is provided that returns the current OpenThread
 * log level via `otLoggingGetLevel()`. Applications that override `PlatformLog`
 * should typically override this function as well.
 *
 * @returns The current platform log level threshold.
 */
PlatformLogLevel PlatformGetLogLevel(void);

/**
 * @}
 */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // OT_LIB_PLATFORM_LOGGER_PLATFORM_H_
