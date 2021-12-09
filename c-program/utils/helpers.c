#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "process.h"

int countProcesses(char *filename)
{
    FILE *fp;
    char ch, previous;
    int processCount = 0, step = 0;
    fp = fopen(filename, "r");
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch != '\n' && isdigit(ch) != 0)
        {
            step++;
        }
        if (step == 4)
        {
            processCount++;
            step = 0;
        }
    }
    fclose(fp);
    return processCount;
}

// Optimize
process *fillProcesses(char *filename)
{
    int size, step = 0, i = 0;
    process *tab;
    FILE *fp;
    char ch;

    size = countProcesses(filename);
    tab = (process *)malloc((size + 1) * sizeof(process));

    fp = fopen(filename, "r");

    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch != '\n')
        {
            if (isdigit(ch) != 0)
            {
                if (step == 0)
                {
                    tab[i].id = ch - '0';
                }
                else if (step == 1)
                {
                    tab[i].at = ch - '0';
                    tab[i].le = ch - '0';
                }
                else if (step == 2)
                {
                    tab[i].ct = ch - '0';
                    tab[i].ctc = ch - '0';
                }
                else if (step == 3)
                {
                    tab[i].priority = ch - '0';
                }
                step++;
            }
        }
        else
        {
            if (step == 4)
            {
                i++;
            }
            step = 0;
        }
    }
    fclose(fp);
    return tab;
}

int validateProcesses(process *tab, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (tab[i].at < 0 || tab[i].ct < 1 || tab[i].priority < 0)
        {
            return -1;
        }
    }

    return 0;
}

process *sortProcesses(process *tab, int size)
{
    process aux;
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (tab[i].at >= tab[j].at)
            {
                aux = tab[i];
                tab[i] = tab[j];
                tab[j] = aux;
            }
        }
    }

    return tab;
}

void printtabs(int tabs, int working)
{
    if (working == -1)
    {
        printf("|");
        return;
    }

    for (int i = 0; i < tabs; i++)
        printf("  ");

    printf("|");
}

void printsimpledashes(int dashes)
{
    for (int i = 0; i < dashes; i++)
    {
        printf("-");
    }
    printf("\n");
}

void printdashes(int dashes)
{
    printf("-");
    for (int i = 0; i < dashes; i++)
    {
        printf("--");
    }
    if (dashes >= 2)
    {
        printf("-");
    }
    printf("-");
}

void printaxis(int dashes, int value)
{
    printf("-");
    for (int i = 0; i < dashes; i++)
    {
        printf("--");
    }
    if (dashes >= 2 && value < 10)
    {
        printf("-");
    }
    printf("%d", value);
}

void printheader(int stars, char *name)
{
    for (int i = 0; i < stars; i++)
    {
        if (stars / i == 2)
        {
            printf(" %s ", name);
        }
        else
        {
            printf("*");
        }
    }
}

void displayProcessesTable(int dataIndex, data *dataTab)
{
    printf("\033[0;32mProcesses Infos: \n\033[0m");
    // Constructing the table header - start
    printsimpledashes(111);
    printf("|Process");
    printtabs(3, 1);
    printf("Arrival Time");
    printtabs(3, 1);
    printf("Burst Time");
    printtabs(3, 1);
    printf("Finish Time");
    printtabs(3, 1);
    printf("\033[1;31mTurn Around Time\033[0m");
    printtabs(3, 1);
    printf("\033[0;36mWaiting Time\033[0m");
    printtabs(3, 1);
    printf("\n");
    printsimpledashes(111);
    // Constructing the table header - end

    // Constructing the body - start
    for (int i = 0; i < dataIndex; i++)
    {
        printf("|%d", dataTab[i].id);
        printtabs(6, 1);
        printf("%d", dataTab[i].started);
        printf(" ");
        printtabs(8, 1);
        printf("%d", dataTab[i].burst);
        printf(" ");
        printtabs(7, 1);
        printf("%d", dataTab[i].finished);
        if (dataTab[i].finished >= 10)
        {
            printf(" ");
            printtabs(7, 1);
        }
        else
        {
            printtabs(8, 1);
        }
        printf("\033[1;31m%d\033[0m", dataTab[i].finished - dataTab[i].started);
        printf(" ");
        printtabs(10, 1);
        printf("\033[0;36m%d\033[0m", (dataTab[i].finished - dataTab[i].started) - dataTab[i].burst);
        printf(" ");
        printtabs(8, 1);
        printf("\n");
        printsimpledashes(111);
    }
}

void displaystats(int dataIndex, data *dataTab)
{
    float avgTurnAroundTime = 0;
    float avgWaitingTime = 0;
    for (int i = 0; i < dataIndex; i++)
    {
        avgTurnAroundTime = (dataTab[i].finished - dataTab[i].started) + avgTurnAroundTime;
        avgWaitingTime = ((dataTab[i].finished - dataTab[i].started) - dataTab[i].burst) + avgWaitingTime;
    }

    printf("\e[4mAverage Turn Around Time:\033[0m %.2f\033[0m, ", avgTurnAroundTime / dataIndex);
    printf("\e[4mAverage Waiting Time:\033[0m %.2f\n\n", avgWaitingTime / dataIndex);
}

void displayGanttDiagram(int outputIndex, int *output, int ganttTimeIndex, int *ganttTime)
{
    // ________________________
    // |P1   |P2        |P3    |
    // |_____|__________|______|
    // 2     1          5

    printf("\033[0;32mGantt Diagram: \n\033[0m");
    printf("--");
    for (int i = 0; i < outputIndex; i++)
    {
        printdashes(ganttTime[i + 1] - ganttTime[i]);
    }

    printf("\n|");
    for (int i = 0; i < outputIndex; i++)
    {
        if (output[i] == -1)
        {
            printf(" - ");
        }
        else
        {
            printf("P%d", output[i]);
        }
        printtabs(ganttTime[i + 1] - ganttTime[i], output[i]);
    }
    printf("\n");
    printf("%d-", ganttTime[0]);
    for (int i = 0; i < outputIndex; i++)
    {
        printaxis(ganttTime[i + 1] - ganttTime[i], ganttTime[i + 1]);
    }
    printf("\n");
}

void displayForCLI(int outputIndex, int *output, int dataIndex, data *dataTab, int ganttTimeIndex, int *ganttTime)
{
    displayProcessesTable(dataIndex, dataTab);
    displaystats(dataIndex, dataTab);
    displayGanttDiagram(outputIndex, output, ganttTimeIndex, ganttTime);

    printf("\n\033[0;35mYou can always use the dedicated GUI by running 'scheduler gui'\n\033[0m");
}

void displayForApp(int outputIndex, int *output, int dataIndex, data *dataTab, int ganttTimeIndex, int *ganttTime)
{

    for (int i = 0; i < outputIndex; i++)
    {
        printf("P%d|", output[i]);
    }

    printf("\n----------\n");
    for (int i = 0; i < ganttTimeIndex; i++)
    {
        printf("%d ", ganttTime[i]);
    }

    printf("\n----------\n");
    for (int i = 0; i < dataIndex; i++)
    {
        printf("P%d, %d, %d, %d, %d, %d\n", dataTab[i].id, dataTab[i].started, dataTab[i].finished, dataTab[i].finished - dataTab[i].started, dataTab[i].burst, (dataTab[i].finished - dataTab[i].started) - dataTab[i].burst);
    }
}

void launchWebServer()
{
    system("php ~/Desktop/Code/scheduler/web-interface/artisan serve");
}

void printHelp()
{
    printf("\033[0;32mUSAGE:\n\033[0m");
    printf("\tscheduler [--help] [FILE] [FLAGS]\n\n");

    printf("\033[0;32m--help:\n\033[0m");
    printf("\tPrints help informations.\n\n");

    printf("\033[0;32mFILE:\n\033[0m");
    printf("\tA file that must respect the pattern Px, Y, Z, W where\n");
    printf("\tx refers to the process index\n");
    printf("\tY refers to the arrival time\n");
    printf("\tZ refres to burst time\n");
    printf("\tW refres to the priority (lower is higher).\n\n");

    printf("\033[0;32mFLAGS:\n\033[0m");
    printf("\t--gui \tLaunches the Web GUI.\n");
}

void printError()
{
    printf("\033[1;31mInvalid arguments, use --help for usage!\n\033[0m");
}