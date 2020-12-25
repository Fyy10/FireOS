# Usage

On Linux, run the following commands:

```shell
cmake .
make
./TestShell
```

For a quick test, run the `test.sh` shell script to get the output:

`./test.sh`

An output file `output.txt` will be in the same folder as `TestShell`.

Alternatively, the program can be built on Windows with `MinGW` installed using the following command:

```shell
g++ *.cpp -o TestShell
```
