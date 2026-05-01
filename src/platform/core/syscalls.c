#include <sys/stat.h>
#include <errno.h>
#include <stdint.h>

// -----------------------------
// Required by newlib
// -----------------------------
void _init(void) {}
void _fini(void) {}

void _exit(int status)
{
    (void)status;
    while (1) {}
}

// -----------------------------
// Syscalls (minimal stubs)
// -----------------------------
int _write(int file, char *ptr, int len)
{
    (void)file;
    (void)ptr;
    return len;
}

int _read(int file, char *ptr, int len)
{
    (void)file;
    (void)ptr;
    return 0;
}

int _close(int file)
{
    (void)file;
    return -1;
}

int _lseek(int file, int ptr, int dir)
{
    (void)file;
    (void)ptr;
    (void)dir;
    return 0;
}

int _fstat(int file, struct stat *st)
{
    (void)file;
    st->st_mode = S_IFCHR;
    return 0;
}

int _isatty(int file)
{
    (void)file;
    return 1;
}

void* _sbrk(ptrdiff_t incr)
{
    extern uint8_t _end;
    static uint8_t *heap_end;
    uint8_t *prev_heap_end;

    if (heap_end == 0)
        heap_end = &_end;

    prev_heap_end = heap_end;
    heap_end += incr;

    return (void*)prev_heap_end;
}