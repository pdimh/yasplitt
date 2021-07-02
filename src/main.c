#include <argp.h>
#include <err.h>
#include <file.h>
#include <limits.h>
#include <sodium.h>
#include <stdio.h>
#include <stdlib.h>

struct arguments {
    char *args[2];
    int split, max_size;
    char *input_file;
    char *output_file;
};

static int parse_opt(int key, char *arg, struct argp_state *state)
{
    struct arguments *arguments = state->input;
    unsigned int size;
    char modifier = 0;

    switch (key) {
    case 's':

        if (sscanf(arg, "%d%c", &size, &modifier) < 1)
            argp_failure(state, 1, 0, "Invalid MAXSIZE: %s", arg);

        if (modifier) {
            switch (modifier) {
            case 'b':
            case 'B':
                break;
            case 'k':
            case 'K':
                if (size <= UINT_MAX / 1024)
                    size <<= 10;

                else
                    argp_failure(state, EXIT_FAILURE, 0,
                                 "MAXSIZE must be smaller "
                                 "than %u%c",
                                 UINT_MAX / 1024 + 1, 'M');
                break;
            case 'm':
            case 'M':
                if (size <= UINT_MAX / 1024 / 1024)
                    size <<= 20;

                else
                    argp_failure(state, EXIT_FAILURE, 0,
                                 "MAXSIZE must be smaller "
                                 "than %u%c",
                                 UINT_MAX / 1024 + 1, 'M');
                break;
            case 'g':
            case 'G':
                if (size <= UINT_MAX / 1024 / 1024 / 1024)
                    size <<= 30;
                else
                    argp_failure(state, EXIT_FAILURE, 0,
                                 "MAXSIZE must be smaller "
                                 "than %u%c",
                                 UINT_MAX / 1024 / 1024 + 1, 'G');
                break;
            default:
                argp_failure(
                    state, EXIT_FAILURE, 0,
                    "MAXSIZE must be informed in B(default), KB, MB, or GB.");
                break;
            }
        }

        arguments->split = 1;
        arguments->max_size = size;
        break;
    case 'o':
        arguments->output_file = arg;
        break;
    case ARGP_KEY_ARG:
        if (state->arg_num >= 1)
            argp_usage(state);
        arguments->input_file = arg;
        break;
    case ARGP_KEY_END:
        if (state->arg_num < 1)
            argp_usage(state);
        break;
    }
    return 0;
}

int main(int argc, char **argv)
{
    struct arguments arguments;
    struct argp_option options[] = {
        {"output", 'o', "OUTPUT_PATH", 0, "Set output path"},
        {"split", 's', "MAXSIZE", 0,
         "Split file into files with size smaller than MAXSIZE"},
        {0}};
    struct argp argp = {options, parse_opt, "PATH", "teste"};

    if (sodium_init() < 0) {
        err(EXIT_FAILURE, "Error initing libsodium");
    }

    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    if (!arguments.output_file)
        arguments.output_file = arguments.input_file;

    if (arguments.split) {
        filenode *flist = split_file(arguments.input_file,
                                     arguments.output_file, arguments.max_size);
        gen_sha256sum(flist);
    }

    exit(0);
}
