#include <stdio.h>
#include <stdlib.h>
#include "../utils/process.h"
#include "../utils/helpers.h"

// TODO: LECTURE MN FICHIER TA9RA AKTHER MN NOMBRE

data *initDataTable(data *dataTab, int processesNumber)
{
    for (int i = 0; i < processesNumber; i++)
    {
        dataTab[i].burst = 0;
    }

    return dataTab;
}

int roundrobin(process *tab, int processesNumber, int quantum, int mode)
{
    int currentTime, processedInTotal, processedInTour, outputIndex, dataIndex, ganttTimeIndex;
    int output[100];
    int ganttTime[100];
    int tookTour;
    data dataTab[processesNumber];

    currentTime = quantum;
    outputIndex = dataIndex = processedInTotal = 0;
    ganttTimeIndex = 1;

    if (validateProcesses(tab, processesNumber) != 0)
    {
        printf("Validate config file");
        return -1;
    }

    // setting the burst to 0 so I can test if it was set or not
    initDataTable(dataTab, processesNumber);

    tab = sortProcesses(tab, processesNumber);
    processedInTour = tab[0].at;
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
                    dataTab[dataIndex].burst = tab[i].ctc; // aaml execution manual khater manish merteh l hedhi, fi deux cas simple, ken cv khali, sinn rodha fonction wa7dha ismha setBurst()
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
                tab[i].ct = tab[i].ct - quantum;
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
        displayForCLI(outputIndex, output, dataIndex, dataTab, ganttTimeIndex, ganttTime);
    }
}