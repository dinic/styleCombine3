/*
 * sc_conjoin.c
 *
 *  Created on: Oct 24, 2013
 *      Author: zhiwenmizw
 */

#include "sc_conjoin.h"

#ifdef SC_HTTPD_PLATFORM
#include "apr_md5.h"

short sc_pool_create(sc_pool_t **newpool, sc_pool_t *parent) {
	return apr_pool_create_ex(newpool, parent, NULL, NULL);
}

void sc_pool_destroy(sc_pool_t *pool) {
	apr_pool_destroy(pool);
}

void *sc_palloc(sc_pool_t *pool, long size) {
	return apr_palloc(pool, size);
}

void *sc_pcalloc(sc_pool_t *pool, long size) {
	return apr_pcalloc(pool, size);
}

short sc_thread_mutex_create(sc_thread_mutex_t **mutex, unsigned int flags,
		sc_pool_t *pool) {
	return apr_thread_mutex_create(mutex, flags, pool);
}

short sc_thread_mutex_lock(sc_thread_mutex_t *mutex) {
	return apr_thread_mutex_lock(mutex);
}

short sc_thread_mutex_unlock(sc_thread_mutex_t *mutex) {
	return apr_thread_mutex_unlock(mutex);
}

short sc_md5(unsigned char digest[SC_MD5_DIGESTSIZE], const void *input,
		size_t inputLen) {
	return apr_md5(digest, input, inputLen);
}

#elif SC_NGINX_PLATFORM

inline short sc_pool_create(sc_pool_t **newpool, sc_pool_t *parent)
{
    short ret = -1;

    if ( NULL == newpool || NULL == parent)
        return ret;

    *newpool = ngx_create_pool(1024, parent->log);

    return 0;
}

inline void sc_pool_destroy(sc_pool_t *pool)
{
    if ( pool )
        ngx_destroy_pool(pool);
    return;
}

inline void *sc_palloc(sc_pool_t *pool, long size)
{
    if (NULL == pool || size < 0)
        return NULL;

    return ngx_palloc(pool, size);
}

inline void *sc_pcalloc(sc_pool_t *pool, long size)
{
    if ( NULL == pool || size < 0)
        return NULL;
    
    return ngx_pcalloc(pool,size);
}

inline short sc_md5(unsigned char digest[SC_MD5_DIGESTSIZE], const void *input,
                size_t inputLen) {
    ngx_md5_t ctx;

    ngx_md5_init(&ctx);
    ngx_md5_update(&ctx, input, inputLen);
    return ngx_md5_final(digest, &ctx);
}

#endif
