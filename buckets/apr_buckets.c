/* ====================================================================
 * The Apache Software License, Version 1.1
 *
 * Copyright (c) 2000-2001 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Apache" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */

#include "apr.h"
#include "apr_lib.h"
#include "apr_pools.h"
#include "apr_tables.h"
#include "apr_errno.h"

#include <stdlib.h>
#if APR_HAVE_STRINGS_H
#include <strings.h>
#endif
#if APR_HAVE_SYS_UIO_H
#include <sys/uio.h>
#endif

#include "apr_buckets.h"

static apr_array_header_t *bucket_types;

APU_DECLARE(void) apr_bucket_init_types(apr_pool_t *p)
{
    bucket_types = apr_array_make(p, 8, sizeof(apr_bucket_type_t));

    apr_bucket_insert_type(&apr_bucket_type_eos);
    apr_bucket_insert_type(&apr_bucket_type_file);
    apr_bucket_insert_type(&apr_bucket_type_heap);
#if APR_HAS_MMAP
    apr_bucket_insert_type(&apr_bucket_type_mmap);
#endif
    apr_bucket_insert_type(&apr_bucket_type_pipe);
    apr_bucket_insert_type(&apr_bucket_type_immortal);
    apr_bucket_insert_type(&apr_bucket_type_transient);
    apr_bucket_insert_type(&apr_bucket_type_socket);
}

APU_DECLARE(int) apr_bucket_insert_type(const apr_bucket_type_t *type)
{
    const apr_bucket_type_t **newone;

    newone = (const apr_bucket_type_t **)apr_array_push(bucket_types);
    newone = &type;

    return bucket_types->nelts - 1;
}

APU_DECLARE_NONSTD(apr_status_t) apr_bucket_setaside_notimpl(apr_bucket *data)
{
    return APR_ENOTIMPL;
}

APU_DECLARE_NONSTD(apr_status_t) apr_bucket_split_notimpl(apr_bucket *data, apr_off_t point)
{
    return APR_ENOTIMPL;
}
APU_DECLARE_NONSTD(apr_status_t) apr_bucket_copy_notimpl(apr_bucket *e, apr_bucket **c)
{
    return APR_ENOTIMPL;
}
APU_DECLARE_NONSTD(void) apr_bucket_destroy_notimpl(void *data)
{
    return;
}
