#include <stdio.h>
#include <stdlib.h>
#include "../utils/process.h"
#include "../utils/helpers.h"

int calculateGanttIndex(int *output, int outputIndex, int processesNumber)
{
    int ganttIndex = 0;

    if (processesNumber == 1)
    {
        return 1;
    }

    for (int i = 0; i < outputIndex; i++)
    {
        if (output[i] != output[i + 1] && i < outputIndex)
        {
            ganttIndex++;
        }
    }

    return ganttIndex;
}

void displayForSRT(int *ganttDiagram, int ganttIndex, data *dataTab, int dataIndex, int *output, int outputIndex)
{
    for (int i = 0; i < outputIndex; i++)
    {
        if (output[i] != output[i + 1])
        {
            printf("P%d|", output[i]);
        }
    }

    printf("\n---------\n");

    for (int i = 0; i <= ganttIndex; i++)
    {
        printf("%d ", ganttDiagram[i]);
    }

    printf("\n----------\n");
    for (int i = 0; i < dataIndex; i++)
    {
        printf("P%d, %d, %d, %d, %d, %d\n", dataTab[i].id, dataTab[i].started, dataTab[i].finished, dataTab[i].finished - dataTab[i].started, dataTab[i].burst, (dataTab[i].finished - dataTab[i].started) - dataTab[i].burst);
    }
}

void displayGanttDiagramSRT(int *ganttDiagram, int ganttIndex, int *output, int outputIndex, int processesNumber)
{
    printf("\033[0;32mGantt Diagram: \n\033[0m");
    printf("--");
    for (int i = 0; i < ganttIndex; i++)
    {
        printdashes(ganttDiagram[i + 1] - ganttDiagram[i]);
    }

    printf("\n|");

    int ganttIndexInLoop = 0;

    if (processesNumber == 1)
    {
        printf("P%d", output[0]);
        printtabs(ganttDiagram[ganttIndexInLoop + 1] - ganttDiagram[ganttIndexInLoop], output[0]);
    }
    else
    {
        for (int i = 0; i < outputIndex; i++)
        {
            if (output[i] != output[i + 1])
            {
                if (output[i] == -1)
                {
                    printf(" - ");
                }
                else
                {
                    printf("P%d", output[i]);
                }
                printtabs(ganttDiagram[ganttIndexInLoop + 1] - ganttDiagram[ganttIndexInLoop], output[i]);
                ganttIndexInLoop++;
            }
        }
    }

    printf("\n");
    printf("%d-", ganttDiagram[0]);

    for (int i = 0; i < ganttIndex; i++)
    {
        printaxis(ganttDiagram[i + 1] - ganttDiagram[i], ganttDiagram[i + 1]);
    }
    printf("\n");
}

int getTheProcessWithShortestTime(process *tab, int processesNumber, int currentTime)
{
    int processIndex = -1;
    int shortestTime = 1000;

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

int *constructGanttDiagram(int *output, int outputIndex, process *tab, int processesNumber)
{
    int *ganttDiagram;
    ganttDiagram = (int *)malloc(100 * sizeof(int));

    int ganttIndex = 0;
    int currentIndex = 0;
    int currentAxis = tab[0].at;

    if (processesNumber == 1)
    {
        ganttDiagram[ganttIndex] = currentAxis;
        ganttIndex++;

        for (int i = 0; i < outputIndex; i++)
        {
            currentAxis++;
        }

        ganttDiagram[ganttIndex] = currentAxis;
        ganttIndex++;

        return ganttDiagram;
    }

    while (currentIndex < outputIndex)
    {
        ganttDiagram[ganttIndex] = currentAxis;
        ganttIndex++;
        for (int i = currentIndex; i < outputIndex; i++)
        {
            if (output[i] == output[i + 1])
            {
                currentAxis++;
            }
            else
            {
                currentIndex = i + 1;
                currentAxis++;
                break;
            }
        }
    }
    ganttDiagram[ganttIndex] = currentAxis;
    ganttIndex++;
    return ganttDiagram;
}

void shortestRemainingTime(process *tab, int processesNumber, int mode)
{
    data dataTab[processesNumber];
    int processedInTotal = 0, currentTime, outputIndex = 0;
    int output[100];
    int processIndex = 0;
    int dataIndex = 0;

    int *ganttDiagram;
    int ganttIndex = 0;

    tab = sortProcesses(tab, processesNumber);
    currentTime = tab[0].at;

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
        }
    }

    ganttDiagram = constructGanttDiagram(output, outputIndex, tab, processesNumber);
    ganttIndex = calculateGanttIndex(output, outputIndex, processesNumber);

    if (mode == 1)
    {
        displayForSRT(ganttDiagram, ganttIndex, dataTab, dataIndex, output, outputIndex);
    }
    else
    {
        printf("Scheduling Algorithm: \033[0;35mShortest Time Remaining\033[0m\n\n");
        displayProcessesTable(dataIndex, dataTab);
        displaystats(dataIndex, dataTab);
        displayGanttDiagramSRT(ganttDiagram, ganttIndex, output, outputIndex, processesNumber);
        printf("\n\033[0;35mYou can always use the dedicated GUI by running 'scheduler <filename> --gui'\n\033[0m");
    }
}
