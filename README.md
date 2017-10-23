# c4d-xpmodifier-numpy
An add-on for Cinema 4D Particles or X-Particles (a Cinema 4D plugin) that lets you modify particles with numpy.

# What is "xpmodifier"?
Cinema 4D has a basic Particles System build-in. X-Particles is a fully featured particle and VFX system for Cinema 4D, available as a commercial plugin. It let's you modify the particles in a variety of ways, mostly with Questions and Actions.
The Questions and Actions, however, can be daunting at first, and with them you cannot accomplish everything that you might wish. If you need more flexibility, there's also a python modifier, which let's you program what the particles should do. The BIG caveat is that it's pure Python, and therefore terribly slow. In fact, it's kind of an offense to the otherwise so blazingly fast X-Particles.

But Python can be made fast, with numpy, and that's what the xpmodifier does. Using numpy, it let’s you modify the particles in any way you wish, with a speed comparable to the rest of X-Particles. You can easily do 100k particles and keep decent frame rates!

For bonus, I have included a "particlemodifier", which does the same but acts on normal Cinema 4D particles (NOT Thinking Particles!).

# Installation
So how do you install xpmodifier? 

# Prerequisites:
Numpy: 
xpmodifier has been tested with numpy 1.10.1, but it’ll probably work with all numpy versions after 1.7, but you should test this. If xpmodifier can’t find numpy, it will give a warning and do nothing. If you happen to have a wrong version, it might make Cinema 4D crash, so beware!

X-Particles:
Of course, you need to have X-Particles installed in order to modify X-Particles! However, if you don't have X-Particles, there is also the particlemodifier-plugin, which acts on normal Cinema 4D particles. Normal c4d particles only have a position and a velocity (but there's nothing to stop you from adding more properties in your numpy script*1).

# Mac
If you’re lucky and on a Mac, you might just be able to copy the whole folder “xpmodifier/” into your plugin directory. On Mac, this is:

~/Library/Preferences/MAXON/CINEMA 4D R1x_xxxxxxx/plugins/

You need to have numpy installed in your packages directory, which is:

~Library/Preferences/MAXON/CINEMA 4D R1x_xxxxxxxx/library/python/packages/osx/



# Windows
I don’t have a Windows computer, so no precompiled plugin for Windows is available. If you know c++, and you are familiar with writing plugins for Cinema 4D, you can try and compile the plugin for yourself. A thing to be aware of is adding the right header paths:
- For "Python.h", add the path to Cinema 4D’s own Python version
- "numpy/arrayobject.h" can be found in: “…/packages/osx/numpy/core/include/”
- The file "numpy/arrayobject.h" #includes a number of other header files, amongst which <Python.h>. You might need to change this to “Python.h”, or compile with the appropriate FLAG.

# Getting Started
The plugin is pretty self-explanatory. At start-up, a little script is loaded to show you the way. By default, “Position” and “Velocity” are available as numpy arrays. More properties can be made available by checking the appropriate checkboxes. 

Of course, you should be familiar with numpy! If not, there are plenty of numpy-tutorials on the web to get you started.

*1) Adding extra properties can be done by a little trick: Since the script is loaded afresh every frame, it cannot store global variables. But you can import a module, and store the global variables there. 

