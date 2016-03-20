#ifndef __PROTO_H__
#define __PROTO_H__

#define SERVICE_PORT 2000

// message codes start
#define PERM_DEN 201
#define FILE_NOT 202
#define INTE_ERR 203
#define UNREC_CO 204
#define PATH_DIR 205
#define HERE_FIL 301
#define SEND_FIL 101
#define HELLOMSG 1
// message code end
struct msg_packet{
    int   length;
    short code;
    char  *param;
};
#endif //__PROTO_H__
