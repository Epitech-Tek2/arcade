<h1 align="center">Documention Arcade</h1>

<h2 align="center">How to use and append libraries</h2>

<br/>
<br/>
<br/>

<h3>Hello and welcome to the document of the arcade project.</h3>

</br>

<h4>⚠️ This document explains how to create and add new libraries. If you want to know how the project works, I suggest you read this <a href="../README.md">README</a>.
</h4>

</br>
</br>

## Graphic Library

</br>

All of our methods are located in: **"Graphs/include/[<span style="color: #1a73e8"><u>libname</u></span>].hpp"**

All of them must be implemented in your library.

FIY: When you want to display something, don't forget to call the clear function.
It is important to avoid issues.
Also, think about the order or your calls functions

</br>
</br>

### The Constructor:

Will initialize the library and setup the type and name of the it.</br>
It takes no parameter.

</br>

ex:
```c
Graph::SDL2 *SDL2 = new Graph::SDL2();
```

</br>
</br>

### The Destructor:

</br>

Won't do anything.

</br>
</br>

### Open:

</br>
Will plays the role of the constructor. Create the window.</br>
It takes the title of the window and his icon.

</br>

ex:
```c
void open(std::string const &title = "", std::string const &icon = "");
```

</br>
</br>

### Close:

</br>
Will plays the role of the deconstructor. Will erase, delete, destroy the window and all memory allocated.</br>
It takes no parameter.

</br>

ex:
```c
void close() const;
```

</br>
</br>

### SetTitle:

</br>
Will changes the title of the window.</br>
It takes the title as only parameter.

</br>

ex:
```c
void setTitle(std::string const &title) noexcept;
```

</br>
</br>

### SetIcon:

</br>
Will changes the icon of the window.</br>
It takes the path to the image as only parameter.

</br>

ex:
```c
void setIcon(std::string const &icon);
```


</br>
</br>

### GetEvent:

</br>
Will retrieves the current event.</br>
It takes no parameter.

</br>

ex:
```c
Arcade::Events getEvent() noexcept;
```

</br>
</br>

### GetEventChar:

</br>
Will retrieves the letter key of the last event.</br>
It takes no parameter.

</br>

ex:
```c
char getEventChar() const noexcept;
```

</br>
</br>

### CheckCollision:

</br>
Will checks if there is a collision between two entities.</br>
It takes as parameters:
- Position of the first entity.
- Size of the first entity.
- Position of the second entity.
- Size of the second entity.

</br>

ex:
```c
int checkCollision(Position const &pos1, Size const &size1, Position const &pos2, Size const &size2) const noexcept;
```

</br>
</br>

### DisplayWindow:

</br>
Displays the window after clearing it.</br>
It takes no parameter;

</br>

ex:
```c
void displayWindow() noexcept;
```

</br>
</br>

### DisplayImage:

</br>
Will displays an image (= pixel array) according to its components.</br>
It takes as parameters:
- Position of the image.
- Form of the image.
- The color of the image.
- The Size of the image.

</br>

ex:
```c
void displayImage(Graph::Position &pos, Graph::Form &form, Arcade::ColorIdx &idx, Graph::Size &size);
```

### DrawRect:

</br>
Will draws a rectangle.</br>
It takes as parameters:
    Position of the rect.
    Color of the rect.
    Size of the rect.

ex:
```c
void drawRect(Graph::Position &pos, Arcade::ColorIdx &idx, Graph::Size &size) noexcept;
```

</br>
</br>

# Game Library

First of all, you need to have all of your game assets. Therefore, create a folder in: **"Ressources/Games/[<u>Game_name</u>]"**

You have to put your forms assets (characters, walls, items) in: **"Ressources/Games/[<u>Game_name</u>]/forms/"**

FIY: When you want to display something, don't forget to call the clear function.
It is important to avoid issues.
Also, think about the order or your calls functions

</br>
</br>

### GetType

</br>

Will gets the type of the library.</br>
It takes no parameter.

</br>

ex:
```c
Arcade::Type getType() const noexcept = 0;
```


</br>
</br>

### GetName

</br>

Will loads a scene and create all the components.</br>
It takes the requested library as parameter.

</br>

ex:
```c
void load(Graph::AGraph *lib) = 0;
```

</br>
</br>

### HandleEvents

</br>

Will reacts to the events related on the elapsed time and simulate the game.</br>
It takes the elapsed time as parameter.

</br>

ex:
```c
void handleUpdate(double elapsedTime) const noexcept = 0;
```

</br>
</br>

### Display

</br>

Will displays all the components.</br>
It takes no parameter.

</br>

ex:
```c
void display() const noexcept = 0;
```

</br>
</br>

# FIY

You can implement as many functions as you want, but keep in mind, these functions <strong>won't</strong> work with the others libraries.