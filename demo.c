#include <string.h>

#include "argparse.h"

int main(int argc, const char *argv[])
{
    struct Argparser *p = make_parser(NULL, argv[0], "little test", Ak_None);

    add_flag(p, "--fuq", "-f", "just a test", Ak_None);
    add_flag(p, "--coq", "-c", "just another test", Ak_None);

    struct Argparser *another =
        make_parser(p, "hewwo", "another test", Ak_None);

    add_flag(another, "--heh", "-j", "just another another test", Ak_None);

    int status = parse(p, argc, argv);

    destroy_parser(p);

    return status;
}
