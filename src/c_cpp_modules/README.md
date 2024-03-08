# Directory structure

## c_cpp_modules
To make sure evetything work properly, please follow below instructions.

C/C++ code files will be linked together into programs. Any functions, variables, or data types that you declare will exist in the same global scope.

> Thus, **keep C/C++ code files in the same directory and follow naming convention to minimize conflict.**

> Each C/C++ module is placed in a separate directory. This makes the code easier to organize and maintain. Each could also has own build, test, doc, misc... If need, use git-submodule to detach, version controling and add external libraries.

> Add this directory in to includePath of your C/C++ extension.

vscode (settings.json)
```json
{
    "C_Cpp.default.includePath": [
        "${workspaceFolder}/src/c_cpp_modules"
    ]
}
```

> Use this directory as wokring folder or add is as directory of header files (`gcc -Idir`) when compiling.

This approach promotes better code organization, maintainability, and easier collaboration.