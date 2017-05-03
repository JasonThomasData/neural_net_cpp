This project implements a neural network in c++, which is useful for some types of classification.

### Compile

On a Linux system, do: `make` at your terminal.

This project was made on a Linux system, and there's no plan to make sure it works in Windows or
Mac. Make a pull request if that's what you want.

### Tests

If you're missing permissions, do: `chmod +x bin/*`

Then do `./bin/tests`

I have been unable to mock objects in C++ so far, so there are no unit tests for functions that have
side effects. Most tests are integration tests.

### Docs

- [using the program](docs/usage.md)
- [data file structure](docs/data_files.md)
- [issues with the program](docs/issues.md)
- [reasons for project structure](docs/discussion.md)
- [optimistic list of things to add](docs/to_add.md)

