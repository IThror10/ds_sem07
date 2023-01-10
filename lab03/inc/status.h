#ifndef __STATUS_H__
#define __STATUS_H__

    typedef enum
    {
        ok,
        argv_error,
        unknown_file,
        key_read_error,
        unknown_command,
        null_pointer_error,
    } status_t;

#endif //__STATUS_H__