This project implements a vanilla neural network in c++, which is useful for some types of classification.
By vanilla, I mean not deep or complicated. There's one activation function.

I'm looking back on this project now, six months after it began, and regretting my decisions. I could
restructure this but I don't have the time. It's not all bad as a first c++ project. Lesson learned:
Dependency Injection is important and it's better to get it right the first time rather than fixing
it later.

### Docs

- [using the program](docs/usage.md)
- [data file structure](docs/data_files.md)
- [example](docs/example.md)
- [issues with the program](docs/issues.md)
- [reasons for project structure](docs/discussion.md)
- [optimistic list of things to add](docs/to_add.md)

### Compile

On a Linux system, do: `make` at your terminal.

This project was made on a Linux system, and there's no plan to make sure it works in Windows or
Mac. Make a pull request if that's what you want.

### Tests

If you're missing permissions, do: `chmod +x bin/*`

Then do `./bin/tests`. Most of these tests are integration tests.
