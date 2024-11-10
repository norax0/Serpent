# Serpent

**Note that Serpent is extremely unfinished. these docs will only teach you the proper syntax for using Serpent!**
- prior python knowledge is recommended.


# Docs!
- I am horrible at documenting, it is recommended that you know how to read terrible c++ if you want to understand how serpent works!!

- Now you get to know how to make scripts with Serpent!
- (check about.md for things both an end-user and a developer would use, like importing scripts.)

# Initializing an empty script
- In order to create an empty script, create a folder, this can be anywhere!
- inside this folder, there'll be two files.
- `script.json`: This is a json file which includes mod metadata, this is the required syntax for it:
```json
// (this is only in jsonc for explaining what each key does, note that your script.json must not have comments! (i think it should work fine though))
{
	"serpent": "1.0.0", // This is the version of Serpent that the script is made for.
	"name": "Simple Script", // This is the name for the script
	"id": "simplescript_yellowcat98", // This is the ID of the script to avoid collision between other scripts!
	"developer": "YellowCat98" // The developer of the script!
}
```
- `mod_id.py`: This is the main script! note that it is required for it to have the same name as the ID otherwise it won't execute!

- Now that you've set up the empty script, package it into a .zip file! please keep in mind that it is required for it to have the same filename as the ID otherwise your mod's script will not execute either (i think)

# Script syntax
- Your script is required to have a class (in which you guessed (probably not) must have the same name as the ID!!)
- Each class must have an instance of the built-in class `script`, which its constructor takes two arguments, which are:
> ID: the ID of your script!
> mainClass: your script's class.

- Syntax example:
```py
# Serpent binds all geode and cocos functions/classes into __main__, you do not need to import any modules.

class simplescript_yellowcat98:
    def init(self):
        self.script = script("simplescript_yellowcat98", self)

if __name__ == "__main__":
    simplescript_yellowcat98() # Initailze an instance of simplescript_yellowcat98, this will be executed on startup.
```
- Now we have an empty mod!

# Hello, World!
- Serpent has an automatic hooking mechanism, so if you define `ClassName_FunctionName` within your mod's class, Serpent will detect this function and then hook `ClassName::FunctionName`
- What is hooking? its basically a thing where a function gets replaced by the other without directly modifying the original.

- But first, in order to initialize hooks, your script's main class must call `script.initAllHooks` after initializing `self.script`.

- All hooks must have `this` as its second argument, `this` is just the class that ClassName::FunctionName is defined in, so `this` is of type `ClassName`.

- Here's an example of a Hello World script!

```py
class simplescript_yellowcat98:
    def init(self):
        self.script = script("simplescript_yellowcat98", self)
        self.script.initAllHooks()
    
    def MenuLayer_onMoreGames(self, this, sender): # `self` is of type simplescript_yellowcat98, `this` is of type MenuLayer, `sender` is of type CCObject
        Notification.create("Hello from my custom script!").show()

if __name__ == "__main__":
    simplescript_yellowcat98()
```
- This code modifies the more games button to show a notification!

# And this is all it for now! there are a lot of other things, 