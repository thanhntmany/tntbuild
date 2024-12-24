# tnt

## Design philosophy
    - Building script should be stored into command-lines.
    - Add comment-lines as indicators then this tool will filter out the necessary segments, sort, run for you.
    - Deverloper should focous on their main languages.


Usage:
```bash
tnt <Command>

Command:
    require-version <version>
    dst <path>
    dep [<path>...] [--]  ||  de- [<path>...] [--]  ||  de-all
    rel [<path>...] [--]  ||  re- [<path>...] [--]  ||  re-all
    build-script <script>
    onchange-script <script>

    track-branch
    scan [<path>...] [--]
    build [<path>...] [--]
    mark-changed [<path>...] [--]

    cd <path>
    pwd
    status
    @  ||  @dst  ||  @dep  || @rel  || @build-script  ||  @onchange-script
    load
    clear
    graph
    ls
```


aaaaa

```
#!/bin/bash

tnt \
dst e3--test \
dep e3-test.c \
build-script "gcc -o \$(tnt @dst) \$(tnt @dep)"


tnt -> scan, sort and run all needed scripts for build/trigger onchange for 
all tracked directories/files in working directory and it's children.


```
