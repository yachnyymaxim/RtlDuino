#include "Arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "wiring_os.h"
#include "cmsis_os.h"

uint32_t os_thread_create( void (*task)(const void *argument), void *argument, int priority, uint32_t stack_size ) {

    osThreadDef_t thread_def;

    thread_def.pthread = task;
    thread_def.tpriority = (osPriority)priority;
    // the underlying freertos implementation on cmsis os divide stack size by 4
    thread_def.stacksize = stack_size * 4;
    thread_def.name = "ARDUINO";

    return (uint32_t)osThreadCreate(&thread_def, argument);
}

uint32_t os_thread_get_id( void ) {
    return (uint32_t)osThreadGetId();
}

uint32_t os_thread_terminate( uint32_t thread_id ) {
    return (uint32_t)osThreadTerminate((osThreadId)thread_id);
}

uint32_t os_thread_yield( void ) {
    return (uint32_t)osThreadYield();
}

uint32_t os_thread_set_priority( uint32_t thread_id, int priority ) {
    return (uint32_t)osThreadSetPriority((osThreadId)thread_id, (osPriority)priority);
}

int os_thread_get_priority( uint32_t thread_id ) {
    return (int)osThreadGetPriority((osThreadId)thread_id);
}

int32_t os_signal_set( uint32_t thread_id, int32_t signals ) {
    return osSignalSet((osThreadId)thread_id, signals);
}

int32_t os_signal_clear( uint32_t thread_id, int32_t signals ) {
    return osSignalClear((osThreadId)thread_id, signals);
}

os_event_t os_signal_wait( int32_t signals, uint32_t millisec ) {

    osEvent evt;
    os_event_t ret;

    evt = osSignalWait(signals, millisec);
    ret.status = (uint32_t)evt.status;
    ret.value.signals = evt.value.signals;
    ret.def.message_id = evt.def.message_id;

    return ret;
}

typedef void (*os_ptimer) (void const *argument);

typedef struct{
    osTimerDef_t cmsis_os_timer_def;
    osTimerId    cmsis_os_timer_id;
} os_timer_t;

uint32_t os_timer_create(void (*callback)(void const *argument), uint8_t isPeriodic, void *argument) {

    os_timer_t* p_timer = malloc(sizeof(os_timer_t));

    if (!p_timer)
        return 0;

    p_timer->cmsis_os_timer_def.ptimer = callback;
    p_timer->cmsis_os_timer_def.custom = (struct os_timer_custom *) malloc ( sizeof (struct os_timer_custom) );

    if (!p_timer->cmsis_os_timer_def.custom)
    {
        free(p_timer);
        return 0;
    }

    p_timer->cmsis_os_timer_id = osTimerCreate(&p_timer->cmsis_os_timer_def, (isPeriodic ? osTimerPeriodic : osTimerOnce), argument);

    if (!p_timer->cmsis_os_timer_id)
    {
        free(p_timer->cmsis_os_timer_def.custom);
        free(p_timer);
        return 0;
    }

    return (uint32_t)p_timer;
}

uint32_t os_timer_start (uint32_t timer_id, uint32_t millisec) {


    return osTimerStart (((os_timer_t*)timer_id)->cmsis_os_timer_id, millisec);
}

uint32_t os_timer_stop (uint32_t timer_id) {
    return osTimerStop(((os_timer_t*)timer_id)->cmsis_os_timer_id);
}

uint32_t os_timer_delete(uint32_t timer_id) {

    os_timer_t* p_timer = (os_timer_t*)timer_id;
    osTimerDelete(p_timer->cmsis_os_timer_id);

    free(p_timer->cmsis_os_timer_def.custom);
    free(p_timer);

    return 0;
}

uint32_t os_semaphore_create(int32_t count) {
    return (uint32_t)osSemaphoreCreate(NULL, count);
}

int32_t os_semaphore_wait(uint32_t semaphore_id, uint32_t millisec) {
    if (osSemaphoreWait((osSemaphoreId)semaphore_id, millisec) == 0) {
        return 1;
    } else {
        return 0;
    }
}

uint32_t os_semaphore_release(uint32_t semaphore_id) {
    return (uint32_t)osSemaphoreRelease((osSemaphoreId)semaphore_id);
}

uint32_t os_semaphore_delete(uint32_t semaphore_id) {
    return (uint32_t)osSemaphoreDelete((osSemaphoreId)semaphore_id);
}

#ifdef __cplusplus
}
#endif