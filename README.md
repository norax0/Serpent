# Serpent

- Documentation

**Note that Serpent is extremely unfinished. these docs will only teach you the proper syntax for using Serpent!**
- (prior python knowledge is recommended.)

# Creating a new Script

- first, we create an instance of `script`, which is a class that has basic mod metadata, enabling hooks, etc.
- It is recommended to only make a single instance of `script`.
- each script requires a Script ID.
- This is how you create an instance of `script`
```python
scriptid_author = script("scriptid_author") # It is recommended to make your ScriptID `scriptid_author`, aswell making the name of the `script` instance variable the same as your scriptID
```
- Now we have an instance of `script`!

# Hooks
- What is a hook?
- When you hook a specific funcion (example: `MenuLayer::onMoreGames`), you replace the original function with another function.

- here is an example, lets modify the `MenuLayer::onMoreGames` function.


```python
# assuming we have an instance of `script` named `scriptid_author`.

def scriptid_author_MenuLayer_onMoreGames(self, sender):
    notification = Notification.create("HellO!")
    notification.show()
```
- Let's explain the code above.

> `scriptid_author_MenuLayer_onMoreGames(self, sender)`
> Function name, in order to hook MenuLayer::onMoreGames, the name MUST BE `scriptid_author_MenuLayer_onMoreGames`, (this applies for any function)

> `(self, sender)`
> The arguments, normally, `MenuLayer::onMoreGames` requires only a single argument (which is `sender`)
> In this case, we pass `self` as the first argument and then the arguments requires.
> Why? this is in order to be able to interact more with the `MenuLayer`

(more will be added soon)