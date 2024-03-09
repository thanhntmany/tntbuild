# tnt

## Design philosophy
    - Building script should be stored into command-lines.
    - Add comment-lines as indicators then this tool will filter out the necessary segments, sort, run for you.
    - Deverloper should focous on their main languages.


Usage:
```bash
tnt <Command>

Command:
    tar <path>
    dep [<path>...] [--]  ||  dep+ [<path>...] [--]  ||  dep- [<path>...] [--]  ||  dep-all
    rel [<path>...] [--]  ||  rel+ [<path>...] [--]  ||  rel- [<path>...] [--]  ||  rel-all
    build-script <script>
    onchange-script <script>

    cd <path>
    status
    @  ||  @tar  ||  @dep  || @rel  || @build-script  ||  @onchange-script
    load
    clear
    graph
    ls
```


aaaaa

```
main.o: main.c /usr/include/stdc-predef.h hello-world.h print-line.h \
 /usr/include/stdio.h /usr/include/bits/libc-header-start.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/bits/wordsize.h /usr/include/bits/long-double.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-pc-linux-gnu/8.2.1/include/stddef.h \
 /usr/lib/gcc/x86_64-pc-linux-gnu/8.2.1/include/stdarg.h \
 /usr/include/bits/types.h /usr/include/bits/typesizes.h \
 /usr/include/bits/types/__fpos_t.h /usr/include/bits/types/__mbstate_t.h \
 /usr/include/bits/types/__fpos64_t.h /usr/include/bits/types/__FILE.h \
 /usr/include/bits/types/FILE.h /usr/include/bits/types/struct_FILE.h \
 /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
```
