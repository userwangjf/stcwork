

#ifndef __MCU_PRINTF__
#define __MCU_PRINTF__

#ifdef __cplusplus
extern "C" {
#endif


#ifndef __STDARG_H__
#define __STDARG_H__

#ifndef NULL
 #define NULL ((void *) 0)
#endif

#ifndef _VA_LIST_DEFINED
typedef char *va_list;
#define _VA_LIST_DEFINED
#endif

#define va_start(ap,v) ap = (va_list)&v + sizeof(v)
#define va_arg(ap,t) (((t *)ap)++[0])
#define va_end(ap)

#endif

//int mini_vsnprintf(char* buffer, unsigned int buffer_len, const char *fmt, va_list va);
//int mini_snprintf(char* buffer, unsigned int buffer_len, const char *fmt, ...);
u8 printk(const u8 *fmt, ...);

#ifdef __cplusplus
}
#endif

#define vsnprintf mini_vsnprintf
#define snprintf mini_snprintf

#endif