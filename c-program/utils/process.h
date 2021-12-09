#ifndef PROCESS_H
#define PROCESS_H

typedef struct process
{
    int id; // id
    int at; // arriving time
    int ct; // cpu time
    int priority;
    int le;  // to save arriving time
    int ctc; // to save cpu time
} process;

#endif /* PROCESS_H */

#ifndef DATA_H
#define DATA_H

typedef struct data
{
    int id;
    int started;
    int finished;
    int burst;
} data;

#endif /* DATA_H */
