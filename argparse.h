/* argparse: Argument parsing library inspired by the Python library of the same
 * name */

#ifndef argparse_h
#define argparse_h

#define MAX_FLAGS 16
#define MAX_SUBPARSERS 16

enum Argument_Kind {
    Ak_None,
    Ak_Int,
    Ak_String,
};

struct Argument {
    // The type of the value held by the argument.
    enum Argument_Kind kind;

    // Pointer to the actual value of the arg.
    void *ptr;
};

struct Flag {
    // Name of the flag.
    const char *name;

    // Short form of the flag. Can be NULL, if the flag does not have one.
    const char *short_name;

    // Description. Can be left NULL to not provide any of it.
    const char *description;

    // Argument that the flag takes. If it takes no argument, the kind of arg
    // is Ak_None.
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

    // Argument. If no argument taken, kind is Ak_None.
    struct Argument arg;
};

// Create an argument parser as the subparser of `parent`, with a subcommand
// name `name`, description `description` and an argument of kind `kind`.
// If the subcommand takes no argument, `kind` must be `Ak_None`.
// `description` can be left NULL to not provide any of it.
// If the parser is the root parser (has no parents), `parent` must be set
// to `NULL`.
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
void add_flag(struct Argparser *parser, const char *name,
              const char *short_name, const char *description,
              enum Argument_Kind kind);

// Print a parser usage message.
// This is the output of the program when the --help or -h flag is invoked, and
// is also shown on argument parsing errors.
void print_usage(struct Argparser *parser);

// Parse arguments based on the spec in `parser`.
// Returns 0 on success, otherwise returns 1.
int parse(struct Argparser *parser, int argc, const char *argv[]);

#endif
