#ifndef __MESSAGE_PROTO__
#define __MESSAGE_PROTO__

#define 1   "Hello"
#define 101 "Give me file"
#define 201 "Permission Denied"
#define 202 "File not found"
#define 203 "Internal error"
#define 204 "Unrecognized command"
#define 205 "Path is a directory"
#define 301 "Here it is"

struct message {
    int m_length;
    short m_code;
    void *m_param;
};

#endif
