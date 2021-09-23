## Contributing to Mistral

### Prerequisites

- A working up-to-date Mistral installation
- C++ knowledge
- Git knowledge
- Ability to ask for help (Feel free to create empty pull-request)

### Setting up Mistral

Mistral reduces its git repository size automatically by using a "shallow repository". This makes developing difficult
by not providing branches and omitting the commit history.

The easiest way to undo this is by running the `developer` script located in `scripts`.

### Pull requests and Branches

In order to send code back to the official Mistral repository, you must first create a copy of Mistral on your github
account ([fork](https://help.github.com/articles/creating-a-pull-request-from-a-fork/)) and
then [create a pull request](https://help.github.com/articles/creating-a-pull-request-from-a-fork/) back to Mistral.

Mistral developement is performed on multiple branches. Changes are then pull requested into master. By default, changes
merged into master will not roll out to stable build users unless the `stable` tag is updated.

### Code-Style

The code-style can be found in `code-style.md`.

### Building

Mistral has already created the directory `build` where cmake files are located. By default, you can build Mistral by
running `./toolbox.sh -b` in the source directory. You can then test your changes by using `./toolbox.sh -l`.
