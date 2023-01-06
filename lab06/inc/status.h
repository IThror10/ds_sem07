#ifndef __STATUS_H__
#define __STATUS_H__

    typedef enum
    {
        ok,
        wrong_args,
        memory_error,
        no_such_file,
        uknown_command,
        null_pointer_error,
    } status_t;

#endif //__STATUS_H__