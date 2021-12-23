#include <stdio.h>
#include <stdlib.h>
#include "../utils/process.h"
#include "../utils/helpers.h"

data *initDataTable(data *dataTab, int processesNumber)
{
    for (int i = 0; i < processesNumber; i++)
    {
        dataTab[i].burst = 0;
    }

    return dataTab;
}

void roundrobin(process *tab, int processesNumber, int quantum, int mode)
{
    int currentTime, processedInTotal, processedInTour, outputIndex, dataIndex, ganttTimeIndex;
    int output[100];
    int ganttTime[100];
    int tookTour;
    data dataTab[processesNumber];

    //currentTime = quantum;
    outputIndex = dataIndex = processedInTotal = 0;
    ganttTimeIndex = 1;

    // setting the burst to 0 so I can test if it was set or not
    initDataTable(dataTab, processesNumber);

    tab = sortProcesses(tab, processesNumber);
    processedInTour = tab[0].at;
    currentTime = processedInTour;
    ganttTime[0] = tab[0].at;
    while (processedInTotal < processesNumber)
    {
        tookTour = 0;
        for (int i = 0; i < processesNumber; i++)
        {
            if (tab[i].at <= currentTime && tab[i].ct > 0)
            {
                output[outputIndex] = tab[i].id;
                outputIndex++;
                if (tab[i].ct <= quantum)
                {
                    processedInTour = processedInTour + tab[i].ct;
                    ganttTime[ganttTimeIndex] = processedInTour;
                    ganttTimeIndex++;
                    dataTab[dataIndex].id = tab[i].id;
                    dataTab[dataIndex].finished = processedInTour;
                    dataTab[dataIndex].started = tab[i].le;
                    dataTab[dataIndex].burst = tab[i].ctc;
                    dataIndex++;
                    processedInTotal++;
                }
                else
                {
                    processedInTour = processedInTour + quantum;
                    ganttTime[ganttTimeIndex] = processedInTour;
                    ganttTimeIndex++;
                }
                tab[i].at = processedInTour;
                if (tab[i].ct <= quantum)
                {
                    tab[i].ct = 0;
                }
                else
                {
                    tab[i].ct = tab[i].ct - quantum;
                }
                tookTour++;
            }
        }
        if (tookTour == 0)
        {
            output[outputIndex] = -1;
            outputIndex++;
            currentTime++;
            ganttTime[ganttTimeIndex] = ganttTime[ganttTimeIndex - 1] + 1;
            ganttTimeIndex++;
            processedInTour = currentTime;
        }
        currentTime = processedInTour;
        tab = sortProcesses(tab, processesNumber);
    }

    // the display will depend on the mode
    // if the mode is set to 1 -> will be piped to the web app other wise, its the CLI display
    if (mode == 1)
    {
        displayForApp(outputIndex, output, dataIndex, dataTab, ganttTimeIndex, ganttTime);
    }
    else
    {
        system("/usr/bin/clear");
        printf("Scheduling Algorithm: \033[0;35mRound Robin\033[0m, Quantum: \033[0;35m%d\033[0m\n\n", quantum);
        displayForCLI(outputIndex, output, dataIndex, dataTab, ganttTimeIndex, ganttTime);
    }
}