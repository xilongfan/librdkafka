/*
 * librdkafka - Apache Kafka C library
 *
 * Copyright (c) 2015, Magnus Edenhill
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met: 
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#pragma once

/* This header file is to be used by .c files needing access to the
 * rd_kafka_transport_t struct internals. */

#if WITH_SASL
#include <sasl/sasl.h>
#include "rdkafka_sasl.h"
#endif

#if WITH_SSL
#include <openssl/ssl.h>
#include <openssl/err.h>
#endif

struct rd_kafka_transport_s {	
	int rktrans_s;
	
	rd_kafka_broker_t *rktrans_rkb;

#if WITH_SSL
	SSL *rktrans_ssl;
#endif

#if WITH_SASL
	struct {
		sasl_conn_t *conn;

		int           complete;    /* Auth was completed early
					    * from the client's perspective
					    * but we must still wait for
					    * reply from server. */
		struct msghdr msg;
		struct iovec  iov[2];

		char          *recv_buf;
		int            recv_of;    /* Received byte count */
		int            recv_len;   /* Expected receive length for
					    * current frame. */
	} rktrans_sasl;
#endif

	rd_kafka_buf_t *rktrans_recv_buf;  /* Used with framed_recvmsg */
	
#ifndef _MSC_VER
	struct pollfd rktrans_pfd;
#else
	WSAPOLLFD rktrans_pfd;
#endif
};

