#ifndef __SNTP_H__
#define __SNTP_H__

#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

void sntp_init(void);
void sntp_stop(void);

/* Realtek added */
void sntp_get_lasttime(long *sec, long *usec, unsigned int *tick);
time_t sntp_gen_system_time(int timezone);
void sntp_set_server(char *servername); // NB! Don't pass local pointers here
char *sntp_get_server(void); // Only first server supported now. Multiple server config not implemented

#ifdef __cplusplus
}
#endif

#endif /* __SNTP_H__ */
