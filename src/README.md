# TNT build system

Usage:
```bash
tnt [Options] <Command> [<args>]

Options:
  -h | --help
    Display this information.
  -v | --version
    Display version information.

Command:
  load [<pathspec>...]
    Load building code
  build [<pathspec>...]
    Build listed files.
  ls
    List information about the files (the current directory by default).
  info [<pathspec>...]
    Display information about pathspec
  graph [<pathspec>...]
    Generate dependency graph of files
```