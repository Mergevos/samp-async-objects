# samp-async-objects

[![Mergevos](https://img.shields.io/badge/Mergevos-samp--async--objects-2f2f2f.svg?style=for-the-badge)](https://github.com/Mergevos/samp-async-objects)

## Installation

Simply install to your project:

```bash
sampctl package install Mergevos/samp-async-objects
```

Include in your code and begin using the library:

```pawn
#include <async-objects>
```

## Usage 

Let's look at the following example:

```c
YCMD:test(playerid, params[], help)
{ 
    if(help) {
        return 0;
    }
    SelectObject(playerid);

    return 1;
}

public OnPlayerSelectObject(playerid, type, objectid, modelid, Float:fX, Float:fY, Float:fZ)
{
    new obj_res[e_OBJECT_INFO];
    await_arr(obj_res) AsyncObject_Edit(playerid, objectid);
    print("Response awaited");
    if(obj_res[E_OBJECT_Response] == EDIT_RESPONSE_FINAL) {
        print("Response final, player clicked on save icon.");
    } else if(obj_res[E_OBJECT_Response] == EDIT_RESPONSE_CANCEL) {
        print("Canceled");
    }
    return 1;
}
```

The `/test` command executes the SelectObject function which allows you to select an object you would like to edit. When you select the object it calls `OnPlayerSelectObject`, GUI is going to show up and allows you to edit, move, rotate and save the object changes. If you hit a cancel or the save button, it awaits task response and when it finishes, it returns task results in an array, thus, you can check, save and modify the object. In the code above, that array way `obj_res`, which is abbreviation of `object_response`, also, we've checked if player hit save button, a.k.a `EDIT_RESPONSE_FINAL` or cancel button with obviously `EDIT_RESPONSE_FINAL` and then we simply output a message. If, for some reason, messages didn't get output, then there's most likely a problem. 

The functions you're going to use are: 

```c
Task: AsyncObject_Edit(playerid, objectid)
```

The params are obvious, the function also has a wrapper. By defining `ASYNC_OBJECT_SYNTAX_EDIT` you allow yourself to use it:
```
Task: EditObjectAsync(playerid, objectid)
```

*Note: You've to put `OnPlayerEditObject` callback in your script.*

## Testing

To test, simply run the package, connect to a server and then execute /test:

```bash
sampctl package run
```
