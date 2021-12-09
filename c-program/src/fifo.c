#include <stdio.h>
#include "../utils/process.h"
#include "../utils/helpers.h"

// ! manish mert7elo amel few tests, jew ma baadhom, je baado barsha, jew wra badhom

void fifo(process *tab, int processesNumber, int mode)
{
    data dataTab[processesNumber];
    int processedInTotal, outputIndex, ganttTimeIndex = 0;
    int output[100];
    int ganttTime[100];

    tab = sortProcesses(tab, processesNumber);

    dataTab[0].id = output[0] = tab[0].id;
    dataTab[0].started = tab[0].at;
    dataTab[0].burst = tab[0].ct;
    dataTab[0].finished = tab[0].at + tab[0].ct;
    processedInTotal = 1;
    outputIndex = 1;
    int currentTime = dataTab[0].finished;

    // the first and second value are always fixed
    ganttTime[ganttTimeIndex] = tab[0].at;
    ganttTimeIndex++;
    ganttTime[ganttTimeIndex] = dataTab[0].finished;
    ganttTimeIndex++;

    while (processedInTotal < processesNumber)
    {
        for (int i = 1; i < processesNumber; i++)
        {
            if (tab[i].at <= currentTime)
            {
                dataTab[i].id = tab[i].id;
                dataTab[i].started = tab[i].at;
                dataTab[i].burst = tab[i].ct;
                if (tab[i].at >= dataTab[i - 1].finished)
                {
                    dataTab[i].finished = tab[i].at + tab[i].ct;
                }
                else
                {
                    dataTab[i].finished = dataTab[i - 1].finished + tab[i].ct;
                }
                output[outputIndex] = tab[i].id;
                outputIndex++;
                ganttTime[ganttTimeIndex] = dataTab[i].finished;
                ganttTimeIndex++;
                processedInTotal++;
                currentTime = dataTab[i].finished;
            }
            else
            {
                ganttTime[ganttTimeIndex] = ganttTime[ganttTimeIndex - 1] + 1;
                ganttTimeIndex++;
                output[outputIndex] = -1;
                outputIndex++;
                currentTime++;
            }
        }
    }

    if (mode == 1)
    {
        displayForApp(outputIndex, output, processesNumber, dataTab, ganttTimeIndex, ganttTime);
    }
    else
    {
        displayForCLI(outputIndex, output, processesNumber, dataTab, ganttTimeIndex, ganttTime);
    }
}