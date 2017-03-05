# Iterable Enums
This is a proof of concept that iterating through enums and converting them to strings should be easy and not complicated.

Visit http://www.yosoygames.com.ar/wp/?p=1376 for more information.

# How to compile
There's two parts: The C++ part and the Python script.

## Python
The Python script requires Python 2.6 (yes, it's rather old). Just run "Run.py" that can be found in PythonScript/Run.py
It will recursively parse all the .h and .hpp files in that folder. The folder is hardcoded in the first line:
```
rootFolder = "./"
```
You can edit it to suit your needs.
This script will generate one .h file for each enum, and one cpp file called "AmalgamationEnum.cpp"

EnumIterator.py does the actual magic, using a template C++ header to generate the final output.

## C++
There's not much to it. The generated files can be compiled in your own project.
As an example, running CMake on CMakeLists.txt will compile the example files in src and include.

# Liability
I'm not responsible for whatever you do with this. Use it at your own risk.

# License
See LICENSE file.

# I get errors when parsing my own headers
It's possible, I developed this as a proof of concept. It's not mature.
It may generate invalid code given complex C++ syntax, or if CppHeaderParser (our dependency)
is unable to parse your C++ syntax properly.
I won't give support, but if you want to improve it, I accept pull requests.
