#pragma once

static inline
void unimplemented()
{
    extern void abort();
    abort();
}

static inline
int pthread_attr_init(pthread_attr_t *)
{
    return 0;
}

static inline
int pthread_attr_setstacksize(pthread_attr_t *, size_t)
{
    return 0;
}

static inline
int pthread_attr_destroy(pthread_attr_t *)
{
    return 0;
}

static inline
int pthread_detach(pthread_t)
{
    unimplemented();
    return -1;
}

#ifdef __GNUC__
__attribute__((const))
#endif
static inline
pthread_t pthread_self(void)
{
    return (pthread_t)1;
}

static inline
_Noreturn void pthread_exit(void *)
{
    // After  the last thread in a process terminates, the process terminates as
    // by calling exit(3) with an exit status of zero;
    //
    exit(0);
}

static inline
int pthread_mutex_init(pthread_mutex_t *__restrict, const pthread_mutexattr_t *__restrict){
    return 0;
}

static inline
int pthread_mutex_lock(pthread_mutex_t *){
    return 0;
}

static inline
int pthread_mutex_unlock(pthread_mutex_t *){
    return 0;
}

static inline
int pthread_mutex_trylock(pthread_mutex_t *){
    return 0;
}

static inline
int pthread_mutex_timedlock(pthread_mutex_t *__restrict, const struct timespec *__restrict){
    return 0;
}

static inline
int pthread_mutex_destroy(pthread_mutex_t *){
    return 0;
}

static inline
int pthread_mutex_consistent(pthread_mutex_t *){
    return 0;
}

static inline
int pthread_cond_init(pthread_cond_t *__restrict, const pthread_condattr_t *__restrict){
    return 0;
}

static inline
int pthread_cond_destroy(pthread_cond_t *){
    return 0;
}

static inline
int pthread_cond_wait(pthread_cond_t *__restrict, pthread_mutex_t *__restrict){
    return 0;
}

static inline
int pthread_cond_timedwait(pthread_cond_t *__restrict, pthread_mutex_t *__restrict, const struct timespec *__restrict){
    return 0;
}

static inline
int pthread_cond_broadcast(pthread_cond_t *){
    return 0;
}

static inline
int pthread_cond_signal(pthread_cond_t *){
    return 0;
}

static inline
int pthread_create(pthread_t *__restrict, const pthread_attr_t *__restrict, void *(*)(void *), void *__restrict)
{
    unimplemented();
    return -1;
}

#define PTHREAD_MAX_KEYS 256
extern void* __pthread_key_values[PTHREAD_MAX_KEYS];
extern size_t __pthread_key_next_slot;

static inline
int pthread_key_create(pthread_key_t *out, void (*destructor)(void *)){
    if (destructor != NULL)
    {
        unimplemented();
    }

    void** key = &__pthread_key_values[__pthread_key_next_slot++];
    if (__pthread_key_next_slot > PTHREAD_MAX_KEYS)
    {
        unimplemented();
    }

    _Static_assert(sizeof(pthread_key_t) == sizeof(key), "pthread_key_t needs to be able to store a pointer.");
    *out = (pthread_key_t) key;
    return 0;
}

static inline
int pthread_key_delete(pthread_key_t){
    return 0;
}

static inline
void *pthread_getspecific(pthread_key_t key){
    _Static_assert(sizeof(pthread_key_t) == sizeof(key), "pthread_key_t needs to be able to store a pointer.");
    return *(void**) key;
}

static inline
int pthread_setspecific(pthread_key_t key, const void *value){
    _Static_assert(sizeof(pthread_key_t) == sizeof(key), "pthread_key_t needs to be able to store a pointer.");
    *(void**)key = value;
    return 0;
}
