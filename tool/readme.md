Terra Launcher
=

Table of Contents
=

1. [Usage](https://github.com/majestic53/terra/tree/master/tool#usage) -- How to use the project

Usage
=

### Interface

Launch from the project root directory:

```
$ ./bin/terra [ARGS]
```

#### Arguments

The following arguments are available:

```
terra [args] seed

-h|--help                       Display help information
-v|--version                    Display version information
```

#### Examples

The following example shows how to launch terra with a randomly generated seed:

```
$ ./bin/terra
```

The following example shows how to launch terra with a specified seed:

```
$ ./bin/terra 12345
```

#### Controls

The following keys allow the user to control terra during runtime:

|Key    |Action     |
|-------|-----------|
|W/Up   |Move up    |
|A/Left |Move left  |
|S/Down |Move down  |
|D/Right|Move right |
|+/-    |Zoom in/out|
|Space  |Reset      |
|R      |Regenerate |
