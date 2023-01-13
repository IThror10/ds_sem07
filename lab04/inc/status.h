#ifndef __STATUS_H__
#define __STATUS_H__

    typedef enum
    {
        ok,
        argv_error,
        unknown_file,
        unknown_command,
        keys_read_error,
        small_keys_error,
        null_pointer_error,
    } status_t;

#endif //__STATUS_H__