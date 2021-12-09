#include <stdio.h>
#include <stdlib.h>
#include "../utils/process.h"
#include "../utils/helpers.h"

int getTheProcessWithShortestTime(process *tab, int processesNumber, int currentTime)
{
    int processIndex = -1;
    int shortestTime = 1000; // okay might change this to a better solution, but for now assuming that no process will take longer than a 1000

    for (int i = 0; i < processesNumber; i++)
    {
        if (tab[i].ct < shortestTime && tab[i].ct > 0 && tab[i].at <= currentTime)
        {
            shortestTime = tab[i].ct;
            processIndex = i;
        }
    }

    return processIndex;
}

void constructGanttDiagram(data *dataTab, int dataIndex)
{
    int ganttDiagram[100];

    ganttDiagram[0] = dataTab[0].started;
    int ganttTimeIndex = 1;

    for (int i = 0; i < dataIndex; i++)
    {
        if (ganttDiagram[ganttTimeIndex - 1] != dataTab[i].started && ganttTimeIndex != 0)
        {
            ganttDiagram[ganttTimeIndex] = dataTab[i].started;
            ganttTimeIndex++;
        }

        if (dataTab[i].finished != dataTab[i + 1].started)
        {
            ganttDiagram[ganttTimeIndex] = dataTab[i].finished;
            ganttTimeIndex++;
        }

        if (dataTab[i].finished < dataTab[i + 1].started)
        {
            ganttDiagram[ganttTimeIndex] = ganttDiagram[ganttTimeIndex] + 1;
        }
    }

    for (int i = 0; i < ganttTimeIndex; i++)
    {
        printf("%d ", ganttDiagram[i]);
    }
}

void shortestRemainingTime(process *tab, int processesNumber, int mode)
{
    data dataTab[processesNumber];
    int processedInTotal = 0, currentTime, ganttTimeIndex, outputIndex = 0;
    int output[100];
    int ganttTime[100];
    int processIndex = 0;
    int dataIndex = 0;

    ganttTimeIndex = 1;

    tab = sortProcesses(tab, processesNumber);
    currentTime = tab[0].at;

    ganttTime[0] = currentTime;

    while (processedInTotal < processesNumber)
    {
        processIndex = getTheProcessWithShortestTime(tab, processesNumber, currentTime);
        if (processIndex != -1)
        {
            dataTab[dataIndex].id = tab[processIndex].id;
            dataTab[dataIndex].started = tab[processIndex].at;
            dataTab[dataIndex].burst = tab[processIndex].ctc;
            currentTime++;
            tab[processIndex].ct--;
            ganttTime[ganttTimeIndex] = currentTime;
            ganttTimeIndex++;
            if (tab[processIndex].ct == 0)
            {
                dataTab[dataIndex].finished = currentTime;
                dataIndex++;
                processedInTotal++;
            }
            output[outputIndex] = tab[processIndex].id;
            outputIndex++;
        }
        else
        {
            output[outputIndex] = -1;
            outputIndex++;
            currentTime++;
            ganttTime[ganttTimeIndex] = currentTime;
            ganttTimeIndex++;
        }
    }

    if (mode == 1)
    {
        for (int i = 0; i < outputIndex; i++)
        {
            if (output[i] != output[i + 1])
            {
                printf("P%d|", output[i]);
            }
        }

        printf("\n----------\n");

        constructGanttDiagram(dataTab, dataIndex);

        printf("\n----------\n");
        for (int i = 0; i < dataIndex; i++)
        {
            printf("P%d, %d, %d, %d, %d, %d\n", dataTab[i].id, dataTab[i].started, dataTab[i].finished, dataTab[i].finished - dataTab[i].started, dataTab[i].burst, (dataTab[i].finished - dataTab[i].started) - dataTab[i].burst);
        }
    }
    else
    {
        // todo, affichage ll SRT kifhom, custom khater el gantt mahlouk
        displayForCLI(outputIndex, output, dataIndex, dataTab, ganttTimeIndex, ganttTime);
    }
}

// int main(int argc, char *argv[])
// {
//     process *tab;
//     int *output;
//     int index;

//     if (argc != 2)
//     {
//         printf("Please check your arguments");
//         return -1;
//     }

//     tab = fillProcesses(argv[1]);
//     shortestRemainingTime(tab, countProcesses(argv[1]), 1);

//     return 0;
// }