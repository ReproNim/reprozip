#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tracer.h"
#include <getopt.h>

const int EXIT_CODE_OFFSET=128;

static char const short_options[] =
    "l:d:h";

static struct option const long_options[] =
{
  {"logfile", required_argument, NULL, 'l'},
  {"dbfile", required_argument, NULL, 'd'},
  {"help", no_argument, NULL, 'h'},
  {0, 0, 0, 0}
};

void print_usage(FILE* out) {
    fprintf(out, "Usage: rztracer [--logfile FILE] [--dbfile FILE] -- CMD [ARGS ...]\n");
}


int main(const int argc, char **argv) {
    /** Could be overridden in cmdline option **/
    char *logfile_path = "reprozip.log";
    char *database_path = "trace.sqlite3";
    /** Details for the actual command invocation */
    char *cmd = NULL;
    char **cmd_argv = NULL;
    int cmd_argc = 0;
    int exit_code;
    int c = 0;

    while (1)
    {
        c = getopt_long (argc, (char **) argv, short_options,
                         long_options, NULL);
        if (c == -1)
            break;

        switch (c)
        {
        case 'd':
            database_path = optarg;
            break;
        case 'l':
            logfile_path = optarg;
            break;
        case 'h':
            print_usage(stdout);
            exit(0);
        case '?':
            /* getopt_long already printed an "unrecognized option" error message. */
            print_usage(stderr);
            exit(EXIT_CODE_OFFSET + 1);
            break;
        default:
            abort ();
        }
    }
    cmd = argv[optind];
    cmd_argv = &argv[optind];
    cmd_argc = argc - optind;
    if (cmd_argc < 1) {
        fprintf(stderr, "RZTRACER: You must specify the command to be ran/traced\n");
        print_usage(stderr);
        return EXIT_CODE_OFFSET + 1;
    }
    fork_and_trace(cmd, cmd_argc, cmd_argv, database_path, logfile_path, &exit_code);
    return exit_code;
}
