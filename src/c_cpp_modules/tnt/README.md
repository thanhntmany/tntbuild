# tnt

# target:
# deps:
# rel:
# onchange:
# build:

## run process:

Optinal:
- Isolate scan zone:
  - limit the zone need to be scanned
- Mark file changed:
  -> mark state for all it's upper dep file
  -> no neeed to check state of them again

Main:
- Scans changes from lowest dep files in the isolated zones.
    - If there's any change, -> [Mark file changed]

- From chosen target, move down through dep tree, plan list script to run. (parallel running if needed)


## sample build file

```bash
cd path/to/build/directory/
tnt tar executable.out
tnt dep executable.c sub.c
tnt build-script "gcc -o \$(tnt target) \$(tnt dep)"
tnt status
```

target :  deps
    build script

 