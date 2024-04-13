tnt \
cd path/to/build/directory/ \
tar executable.out \
dep executable.c sub.c -- \
rel executable.c sub.c rel1.c rel1.c rel2. -- \
build-script "gcc -o \$(tnt target) \$(tnt dep) \$(tnt rel)" \
onchanged-script "tnt rel \$(gcc -M \$(tnt -target))" \
status
