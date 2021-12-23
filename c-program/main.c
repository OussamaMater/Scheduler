#define KEY "ZnJvbUFwcAo="

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils/process.h"
#include "utils/helpers.h"
#include "headers/fifo.h"
#include "headers/rr.h"
#include "headers/sjf.h"
#include "headers/srt.h"
#include "headers/pnp.h"

typedef void (*Algorithm)(process *tab, int processesNumber, int mode);
typedef void (*RR)(process *tab, int processesNumber, int quantum, int mode);

typedef struct menuOptions
{
    int id;
    char name[50];
    Algorithm algo;
    RR rr;

} menuOptions;

int executeAlgorithm(menuOptions *options, int optionsIndex, int choice)
{
    for (int i = 0; i < optionsIndex; i++)
    {
        if (options[i].id == choice)
        {
            return i;
        }
    }

    return -1;
}

void displayMenu(menuOptions *options, int optionsIndex)
{
    printf("\e[4mAvailable algorithms:\033[0m\n\n");
    for (int i = 0; i < optionsIndex; i++)
    {
        printf("   %d. %s", options[i].id, options[i].name);
    }

    printf("\n\033[0;32mPlease enter an option\033[0m\n");
}

void renderDynamicMenu(process *tab, int processesNumber, int mode)
{
    FILE *fp;
    char path[1035];
    menuOptions options[100];
    int optionsIndex = 0;
    int choice;
    int algoToExecute;

    fp = popen("/bin/ls ~/Desktop/Code/scheduler/c-program/bin/", "r");
    if (fp == NULL)
    {
        printf("Failed to run command\n");
        exit(1);
    }

    while (fgets(path, sizeof(path), fp) != NULL)
    {
        if (strcmp(path, "fifo\n") == 0)
        {
            options[optionsIndex].id = optionsIndex;
            strcpy(options[optionsIndex].name, path);
            options[optionsIndex].algo = fifo;
        }

        if (strcmp(path, "pnp\n") == 0)
        {
            options[optionsIndex].id = optionsIndex;
            strcpy(options[optionsIndex].name, path);
            options[optionsIndex].algo = pnp;
        }

        if (strcmp(path, "rr\n") == 0)
        {
            options[optionsIndex].id = optionsIndex;
            strcpy(options[optionsIndex].name, path);
            options[optionsIndex].rr = roundrobin;
        }

        if (strcmp(path, "sjf\n") == 0)
        {
            options[optionsIndex].id = optionsIndex;
            strcpy(options[optionsIndex].name, path);
            options[optionsIndex].algo = sjf;
        }

        if (strcmp(path, "srt\n") == 0)
        {
            options[optionsIndex].id = optionsIndex;
            strcpy(options[optionsIndex].name, path);
            options[optionsIndex].algo = shortestRemainingTime;
        }

        optionsIndex++;
    }

    pclose(fp);

    displayMenu(options, optionsIndex);

    do
    {
        printf("=> ");
        scanf("%d", &choice);
    } while (choice < 0 || choice > optionsIndex - 1);

    if ((algoToExecute = executeAlgorithm(options, optionsIndex, choice)) != -1)
    {
        system("/usr/bin/clear");
        if (strcmp(options[algoToExecute].name, "rr\n") == 0)
        {
            options[algoToExecute].rr(tab, processesNumber, readQuantum(), mode);
        }
        else
        {
            options[algoToExecute].algo(tab, processesNumber, mode);
        }
    }
}

int main(int argc, char *argv[])
{
    process *tab;

    if (argc < 2)
    {
        printError();
        return -1;
    }

    // ? Checking wether the binary was executed manually or via the web app

    if (strcmp(argv[1], KEY) == 0)
    {
        // * Being called from the app so I need to display the App version
        // * ./scheduler KEY config fifo (quantum)

        // ! counting the processes number first in case anything goes wrong, for the Web App
        if (countProcesses(argv[2]) == 0)
        {
            printf("There must be at least one process!\n");
            return -1;
        }

        tab = fillProcesses(argv[2]);

        // ! Making sure the input is valid, so web app dont crash
        if (validateProcesses(tab, countProcesses(argv[2])) == -1)
        {
            printf("Validate the config file please!\n");
            return -1;
        }

        if (strcmp(argv[3], "fifo") == 0)
        {
            fifo(tab, countProcesses(argv[2]), 1);
        }

        if (strcmp(argv[3], "sjf") == 0)
        {
            sjf(tab, countProcesses(argv[2]), 1);
        }

        if (strcmp(argv[3], "srt") == 0)
        {
            shortestRemainingTime(tab, countProcesses(argv[2]), 1);
        }

        if (strcmp(argv[3], "pnp") == 0)
        {
            pnp(tab, countProcesses(argv[2]), 1);
        }

        if (strcmp(argv[3], "rr") == 0)
        {
            roundrobin(tab, countProcesses(argv[2]), atoi(argv[4]), 1); //gcc main.c utils/helpers.c src/rr.c -o final
        }

        return 0;
    }

    // ? we are sure that he passed at least one parameter.
    if (strcmp(argv[1], "--help") == 0) // * assuming that he asked for help
    {
        printHelp();
        return 0;
    }

    if (argc >= 3) // * checking that might want to pass an optional parameter
    {
        // I wrapped it in an if, in case the list goes on
        if (strcmp(argv[2], "--gui") != 0)
        {
            printError();
            return -1;
        }

        launchWebServer();
    }

    // ! counting the processes number first in case anything goes wrong, for the CLI
    if (countProcesses(argv[1]) == 0)
    {
        printf("\033[1;31mThere must be at least one process!\n\033[0m");
        return -1;
    }

    // ! validating the input first
    tab = fillProcesses(argv[1]);

    if (validateProcesses(tab, countProcesses(argv[1])) == -1)
    {
        printf("\033[1;31mValidate the config file please!\n\033[0m");
        return -1;
    }

    renderDynamicMenu(tab, countProcesses(argv[1]), 2);

    return 0;
}