// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GBNETWORK_H
#define GBNETWORK_H

#include "azure_c_shared_utility/umock_c_prod.h"

#ifdef __cplusplus
#include <cstddef>
#include <cstdlib>
#include <cstdint>
extern "C"
{
#else
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#endif

#ifdef WIN32
    #include <winsock2.h>
#else
    #include <sys/socket.h>
#endif

/* all translation units that need network measurement need to have GB_MEASURE_NETWORK_FOR_THIS defined */
/* GB_DEBUG_NETWORK is the switch that turns the measurement on/off, so that it is not on always */
#if defined(GB_DEBUG_NETWORK)

MOCKABLE_FUNCTION(, int, gbnetwork_init);
MOCKABLE_FUNCTION(, void, gbnetwork_deinit);

#ifdef WIN32
MOCKABLE_FUNCTION(, int, gbnetwork_send, SOCKET, sock, const char*, buf, int, len, int, flags);
#else
MOCKABLE_FUNCTION(, ssize_t, gbnetwork_send, int, sock, const void*, buf, size_t, len, int, flags);
#endif

MOCKABLE_FUNCTION(, uint64_t, gbnetwork_getBytesSent);
MOCKABLE_FUNCTION(, uint64_t, gbnetwork_getNumSends);

/* if GB_MEASURE_NETWORK_FOR_THIS is defined then we want to redirect network send functions to gbnetwork_xxx functions */
#ifdef GB_MEASURE_NETWORK_FOR_THIS
#define send gbnetwork_send
#endif

#else /* GB_DEBUG_NETWORK */

#define gbnetwork_init() 0
#define gbnetwork_deinit() ((void)0)
#define gbnetwork_getBytesSent() 0
#define gbnetwork_getNumSends() 0

#endif /* GB_DEBUG_NETWORK */

#ifdef __cplusplus
}
#endif

#endif /* GBNETWORK_H */