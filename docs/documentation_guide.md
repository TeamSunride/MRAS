# Technical Guide to Documentation

Documentation for this project is located in the `docs` folder and in the source code. The documentation is generated
using [Doxygen](http://www.doxygen.nl/) and [Graphviz](http://www.graphviz.org/). The documentation is generated using
the `Doxyfile` in the project root. The `Doxyfile` is configured to generate documentation for the `lib` folder for
markdown files located in the `docs` folder.

## How to install Doxygen and Graphviz on Windows

1. Download and install [Graphviz](http://www.graphviz.org/Download_windows.php) (tested with v7.0.6)
2. Download and install [Doxygen](http://www.doxygen.nl/download.html) (v1.9.6 recommended)
3. Add the `bin` folder of Graphviz to your `PATH` environment variable
4. Add the `bin` folder of Doxygen to your `PATH` environment variable

## How to generate documentation

1. Open a command prompt
2. Navigate to the project root
3. Run `doxygen`

## How to view documentation

Open [`docs\html\index.html`](index.html) in a browser

## Hosted documentation:

Documentation is hosted online at the URL [mras.sunride.space](https://mras.sunride.space/)

When the documentation is updated, the hosted documentation is updated automatically.

Commits to the main branch trigger a GitHub Actions workflow. The workflow generates the documentation and pushes it to
the `gh-pages` branch. GitHub charges organizations for hosting Pages sites from private repositories. To get around 
this, Vercel is used to deploy the files committed to the `gh-pages` branch.

## Creating graphs and diagrams

Graphs and diagrams can be created using the [dot](https://www.graphviz.org/pdf/dotguide.pdf) tool.

Example:

```md
@dot
digraph G {
size ="4,4";
main [shape=box]; /* this is a comment */
main -> parse [weight=8];
parse -> execute;
main -> init [style=dotted];
main -> cleanup;
execute -> { make_string; printf}
init -> make_string;
edge [color=red]; // so is this
main -> printf [style=bold,label="100 times"];
make_string [label="make a\nstring"];
node [shape=box,style=filled,color=".7 .3 1.0"];
execute -> compare;
}
@enddot
```

Output:

@dot
digraph G {
size ="4,4";
main [shape=box]; /* this is a comment */
main -> parse [weight=8];
parse -> execute;
main -> init [style=dotted];
main -> cleanup;
execute -> { make_string; printf}
init -> make_string;
edge [color=red]; // so is this
main -> printf [style=bold,label="100 times"];
make_string [label="make a\nstring"];
node [shape=box,style=filled,color=".7 .3 1.0"];
execute -> compare;
}
@enddot
