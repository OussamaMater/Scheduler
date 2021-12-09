#define KEY "ZnJvbUFwcAo="

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils/process.h"
#include "utils/helpers.h"
#include "src/fifo.h"
#include "src/rr.h"
#include "src/sjf.h"
#include "src/srt.h"
#include "src/pnp.h"

typedef void (*Algorithm)(process *tab, int processesNumber, int mode);

typedef struct menuOptions
{
    int id;
    char name[50];
    Algorithm algo;

} menuOptions;

void renderDynamicMenu()
{
    FILE *fp;
    char path[1035];
    char menuItems[6][100];
    int lineIndex = 0;
    int charInLineIndex = 0;
    menuOptions options[6]; // max algos,
    int index = 0;

    fp = popen("/bin/ls ~/Desktop/Code/scheduler/c-program/bin/", "r");
    if (fp == NULL)
    {
        printf("Failed to run command\n");
        exit(1);
    }

    while (fgets(path, sizeof(path), fp) != NULL)
    {
        // well so far this is going as planed here, l fonction yaarfha w kol donc nkaml feha, w baad el Makefile naamlha hasb gcc w akhw
        printf("%s", path);
        options[index].id = index + 1;
        strcpy(options[index].name, path);
        if (strcmp(path, "fifo"))
        {
            options[index].algo = fifo;
        }
        printf("%d", options[index].id);
        printf("%s", options[index].name);

        return;

        charInLineIndex = 0;
        while (path[charInLineIndex] != '\n')
        {
            menuItems[lineIndex][charInLineIndex] = path[charInLineIndex];
            charInLineIndex++;
        }

        menuItems[lineIndex][charInLineIndex] = '\0';
        lineIndex++;
    }
    pclose(fp);

    char ch;
    for (int lineIndex = 0; lineIndex < 6; lineIndex++)
    {
        charInLineIndex = 0;
        do
        {
            ch = menuItems[lineIndex][charInLineIndex];
            printf("%c", ch);
            charInLineIndex++;
        } while (ch != '\0');
        printf("\n");
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

    // Checking wether the binary was executed manually or via the web app

    if (strcmp(argv[1], KEY) == 0)
    {
        // Being called from the app so I need to display the App version
        // ./scheduler KEY config fifo (quantum)
        tab = fillProcesses(argv[2]);

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

        // SRT coming soon

        return 0;
    }

    // we are sure that he passed at least one parameter.

    if (strcmp(argv[1], "--help") == 0) // assuming that he asked for help
    {
        printHelp();
        return 0;
    }

    if (argc >= 3) // checking that might want to pass an optional parameter
    {
        // I wrapped it in an if, in case the list goes on

        if (strcmp(argv[2], "--gui") != 0)
        {
            printError();
            return -1;
        }

        launchWebServer();
    }

    tab = fillProcesses(argv[1]);
    // CLI version is here

    renderDynamicMenu();

    // tab = sortProcesses(tab, countProcesses(argv[1]));
    return 0;
}