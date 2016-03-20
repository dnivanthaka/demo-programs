#ifndef __PROCESS_DEF_H__
#define __PROCESS_DEF_H__
struct m_pcb {
    char pcb_info[128];
} m_pcb;
struct m_process {
    int          m_pid;
    char         m_stack[10][10];
    unsigned int m_stack_size;
    char         m_data[10][10];
    unsigned int m_data_size;
    char         m_txt[10][10];
    unsigned int m_txt_size;
    struct m_pcb *pcb;
} m_process;

struct m_process * new_process(char *);
int get_file_offsets(FILE *, struct m_process *);
#endif //__PROCESS_DEF_H__
