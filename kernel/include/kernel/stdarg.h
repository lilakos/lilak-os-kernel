#ifndef VA_LIST_H
#define VA_LIST_H

typedef const char* va_list;

#define va_argiz(t) \
    (((sizeof(t) + sizeof(int) - 1) / sizeof(int)) * sizeof(int))

#define va_start(ap, pN)    \
    ((ap) = ((va_list) (&pN)+va_argiz(pN)))

#define va_end(ap) ((void)0)

#define va_arg(ap,t)    \
    (((ap)=(ap)+va_argiz(t)),   \
    *((t*)(void*)((ap)-va_argiz(t))))

#endif