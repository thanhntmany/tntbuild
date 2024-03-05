# TNT build system

Usage:
```bash
tnt [Options] <Command> [<args>]

Options:
  -v | --version
    Display version information.
  -h | --help
    Display this information.
  -d <working-directory> | --working-directory=<working-directory>
    Set working directory (the current directory by default)

Command:
  load [<pathspec>...]
    Load building code
  ls
    List information about the pathspec (the current directory by default).
  stat [<pathspec>...]
    Retrieve information about the files
  graph [<pathspec>...]
    Generate dependency graph of files
  make [Options] [<pathspec>...]
    Build listed files.
```

tntbuild main

```
#@target:prerequisite
[<command>...]
```


tnt load build.bi.sh
tnt load -r somedir
tnt load

"abc sdafds" | tnt load

tnt ls .
tnt ls -r .

tnt stat file
tnt stat -r .

tnt make .


tnt graph ...

