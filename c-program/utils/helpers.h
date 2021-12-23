#include "process.h"

int countProcesses(char *filename);
int validateProcesses(process *tab, int size);
process *fillProcesses(char *filename);
process *sortProcesses(process *tab, int size);
void printtabs(int tabs, int working);
void printsimpledashes(int dashes);
void printdashes(int dashes);
void printaxis(int dashes, int value);
void printheader(int stars, char *name);
void displayProcessesTable(int dataIndex, data *dataTab);
void displaystats(int dataIndex, data *dataTab);
void displayGanttDiagram(int outputIndex, int *output, int ganttTimeIndex, int *ganttTime);
void displayForCLI(int outputIndex, int *output, int dataIndex, data *dataTab, int ganttTimeIndex, int *ganttTime);
void displayForApp(int outputIndex, int *output, int dataIndex, data *dataTab, int ganttTimeIndex, int *ganttTime);
void launchWebServer();
void printHelp();
void printError();
int readQuantum();
