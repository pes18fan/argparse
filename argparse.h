/* argparse: Argument parsing library inspired by the Python library of the same
 * name */

#ifndef argparse_h
#define argparse_h

#include <stdbool.h>

#define MAX_FLAGS 16
#define MAX_SUBPARSERS 16

// The type of the value held by an argument.
enum Argument_Kind {
    Ak_None,
    Ak_Int,
    Ak_String,
};

struct Argument {
    enum Argument_Kind kind;
    union {
        int _i;
        const char *_s;
    };
};

struct Flag {
    // Name of the flag.
    const char *name;

    // Short form of the flag. Can be NULL, if the flag does not have one.
    const char *short_name;

    // Description. Can be left NULL to not provide any of it.
    const char *description;

    // Argument taken by the flag.
    // It has some kind, referring to its data type. If the flag takes no
    // argument, the kind is is Ak_None.
    // It also holds a union which holds the actual argument data after parsing.
    // It is not safe to access this data directly; use `get_flag` instead.
    struct Argument arg;
};

// Parser for a command. Has a set of its own subparsers.
// and flags.
struct Argparser {
    // Name of the command.
    const char *name;

    // Description. Can be left NULL to not provide any of it.
    const char *description;

    // Subparsers to parse any subcommands.
    struct Argparser *subparsers[MAX_SUBPARSERS];
    int subparser_count;

    // Flags.
    struct Flag *flags[MAX_FLAGS];
    int flag_count;

    // Argument taken by the command.
    // It has some kind, referring to its data type. If the command takes no
    // argument, the kind is is Ak_None.
    // It also holds a union which holds the actual argument data after parsing.
    // It is not safe to access this data directly; use `get_arg` instead.
    struct Argument arg;
};

// Create an argument parser as the subparser of `parent`, with a subcommand
// name `name`, description `description` and an argument of kind `kind`.
// If the subcommand takes no argument, `kind` must be `Ak_None`.
// `description` can be left NULL to not provide any of it.
// If the parser is the root parser (has no parents), `parent` must be set
// to `NULL`.
// If the provided parser spec has any issues (e.g. attempt to add a duplicate
// subcommand, attempt to add a subparser for a parser that takes an argument,
// addition of too many subparsers), the function prints the error to stderr and
// exits the program with status 1.
struct Argparser *make_parser(struct Argparser *parent, const char *name,
                              const char *description, enum Argument_Kind kind);

// Deallocate an Argparser.
// Also deallocates all of its subparsers and flags; hence you should avoid
// running it for every single subparser; just destroy the root.
void destroy_parser(struct Argparser *parent);

// Add a flag to `parser`, with a `name` and optional `short_name` and
// `description`. The latter two can be left NULL if undesired. The type of the
// argument the flag takes is provided via `kind`; if it takes no argument
// `kind` must be `Ak_None`.
// If the provided flag spec has any issues (e.g. invalid flag name, attempt to
// add a duplicate flag, addition of too many flags), the function prints the
// error to stderr and exits the program with status 1.
void add_flag(struct Argparser *parser, const char *name,
              const char *short_name, const char *description,
              enum Argument_Kind kind);

// Parse arguments based on the spec in `parser`.
// Returns the number of arguments parsed on success (a non-negative integer),
// otherwise returns -1.
// If it encounters a problem with the setup of the arguments (for example an
// invalid argument kind, or invalid `argv`), it prints the issue to stderr and
// exits the program with status 1.
int parse(struct Argparser *parser, int argc, const char *argv[]);

#endif
