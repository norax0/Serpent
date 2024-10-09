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
scriptname_author = script("scriptname_author") # It is recommended to make your ScriptID `scriptname_author`, aswell making the name of the `script` instance variable the same as your scriptID
```
- Now we have an instance of `script`!

# Hooks
- What is a hook?
- When you hook a specific funcion (example: `MenuLayer::onMoreGames`), you replace the original function with another function.

- here is an example, lets modify the `MenuLayer::onMoreGames` function.


```python
# assuming we have an instance of `script` named `scriptname_author`.

def scriptname_author_MenuLayer_onMoreGames(self, sender):
    notification = Notification.create("HellO!")
    notification.show()
```
- Let's explain the code above.

- `scriptname_author_MenuLayer_onMoreGames(self, sender)`
- Function name, in order to hook MenuLayer::onMoreGames, the name MUST BE `scriptname_author_MenuLayer_onMoreGames`, (this applies for any function)

- `(self, sender)`
- The arguments, normally, `MenuLayer::onMoreGames` requires only a single argument (which is `sender`)
- In this case, we pass `self` as the first argument and then the arguments requires.
- (note that `self` is the current instance of `MenuLayer`)
- Why? this is in order to be able to interact more with `MenuLayer`

- Once we're done defining our hook, we have to enable it

```python
scriptname_author.initAllHooks() # it is recommended to put this line at the end of your script.
```
`script.initAllHooks()` that just initializes all hooks for your specific script, you can call it twice (which enables the hook twice) but just please don't do it

# Extending on a Function
- Sometimes you might want to extend on a function instead of replacing it entirely, thanks to the first `self` argument, you can do that!

```python
# Assuming the script ID is testscript_yellowcat98

# the `init` most times initializes the layer. in this case the main menu (MenuLayer)
def testscript_yellowcat98_MenuLayer_init(self) -> bool:
    info("Before original!") # This will be called before MenuLayer::init is called.
    if not self.init(): return False # we just called original!
    # note that you should never pass `self` as an argument1

    info("After original!") # this will be called after MenuLayer::init is called (assuming the function returns true. which it most likely will)
    return True
```

- Here's a more easy to understand example:

```python
# Assuming the script ID is testscript_yellowcat98

# MenuLayer::onMoreGames hook
def testscript_yellowcat98_MenuLayer_onMoreGames(self, sender):
    info("before original!")
    self.onMoreGames(sender) # we have just called the original!
    info("after original is called!")
```

# Logging
- While you already know the `print` function in python, in Serpent, it is recommended to NOT use `print`
- This is because `print` sends direct calls to `stdout`, While you can use `print`, it is better to use `info`, `debug`, `warn`, or `error` depending on which context. here is an example!

```python
# Assuming the script ID is testscript_yellowcat98

def testscript_yellowcat98_MenuLayer_init(self):
    if not self.init():
        error("`MenuLayer::init returned false!") # (this is just for demo purposes, this line of code won't be reached because GD automatically destroys the instance of `MenuLayer` IF MenuLayer::init returns false.)
        return False
    
    return True