<h1 align="center">Arcade</h1>

<br/>

<h3>Arcade is a gaming platform: a program that lets the user choose a game to play and keeps a register of player scores.
To be able to deal with the elements of your gaming plateform at run-time, your graphics libraries and your games
must be implemented as dynamic libraries, loaded at runtime.
</h3>

<br/>
<br/>

# Graphical libraries implemented

|             |   Libraries   |            |
|:-----------:|:-------------:|:----------:|
|   Ncurses   |      SFML     |    SDL2    |

</br>
</br>

# Game Libraries implemented

|             Games|      |
|:-----------:|:-------------:|
|   Pacman   |      Nibbler     |

<br/>
<br/>

# How to use it

You can compile the entire project by taping:

```bash
$ make
```

</br>

## Compile separately

You can only compile the core by taping:

```bash
$ make core
```

You can only compile the games libraries by taping:

```bash
$ make games
```

You can also only compile the graphical libraries by taping:

```bash
$ make graphicals
```

</br>
</br>

# After compilation

To launch the project, you have first to choose the library you want.

```bash
$ ./arcade ./lib_arcade_[NAME_OF_THE_LIBRARY]
```

</br>

## Menu keys

</br>

|     Keys    |      Action					|
|:-----------:|:-----------------------------------------------:|
|   L         |      Next Lib					|
|   K         |      Prev Lib					|
|   G         |      Next Game					|
|   F         |      Prev Game					|
|   T         |      Start changing your pseudo / Stop it     	|
|   M         |      Load the game				|

</br>

## How to play

</br>


|     Keys    |      Action      |
|:-----------:|:----------------:|
|   Z         |      Move Up     |
|   S         |      Move Down   |
|   Q         |      Move Left   |
|   D         |      Move Right  |
|   L         |      Next Lib    |
|   K         |      Prev Lib    |
|   G         |      Next Game   |
|   F         |      Prev Game   |
|   T         |      Restart     |
|   M         |      Menu        |