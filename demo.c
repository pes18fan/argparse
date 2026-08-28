#include <stdio.h>
#include <string.h>

#include "argparse.h"

int main(int argc, const char *argv[])
{
    struct Argparser *p =
        ap_make_parser(NULL, argv[0], "little test", 'n', NULL);

    ap_add_flag(p, "--test", "-t", "just a test", 'n', NULL);
    ap_add_flag(p, "--test2", "-d", "just another test", 'n', NULL);

    char *a;
    struct Argparser *another =
        ap_make_parser(p, "hewwo", "another test", 's', &a);

    ap_add_flag(another, "--heh", "-j", "just another another test", 'n', NULL);

    int parsed = ap_parse(p, argc, argv);
    ap_destroy_parser(p);

    if (parsed == -1) {
        return 1;
    } else {
        printf("got: %s", a);
        return 0;
    }
}
