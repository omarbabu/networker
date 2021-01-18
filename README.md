**

## NETWORKER

Final Presentation: https://youtu.be/8sg10jTKIZM

**

Welcome to the Networker! Our program can help you map connections between individuals in any dataset. We have provided an ego-GPlus dataset from SNAP with the program so you can test out the algorithm, but you are welcome to run it on your own dataset.

**How to I download this?**

You can download this app directly from GitHub as a zip folder. It is ready to use as soon as you unzip the folder.

*For Windows users*

You will have to enable WSL (Windows subsystem for Linux)  [instructions to enable WSL] (https://docs.microsoft.com/en-us/windows/wsl/install-win10) and install the Ubuntu terminal in order to use this application.

**How do I run this?**

Hop onto your terminal (Ubuntu terminal for Windows Users) and navigate to the folder containing all the code files (src folder).
Windows users must add an additional command when typing the path to the desired folder:

> cd /mnt/c/Users/...

Once you have successfully navigated to the correct folder, type "make networker" into the terminal. It should output:

>Makefile:29: -e  Looks like you are not on EWS. Be sure to >test on EWS before the deadline. -e
>clang++  -std=c++1y -stdlib=libc++ -c -g -O0 -Wall ->Wextra -pedantic main.cpp graph.cpp driver.cpp
>clang++ graph.o main.o driver.o -std=c++1y -stdlib=libc++ >-lc++abi -lm -o networker

Then type in "./networker" into the terminal to start the application. The following should be outputted onto the terminal:

>Welcome to Networker! Enter the path to your dataset or >type 'default' to use a Google+ network

Enter "default" into the terminal if you want to use the packaged ego-GPlus dataset, but feel free to use your own! Simple enter the path to your dataset instead of "default" to do so. Then, you should be prompted to enter the first name.

>Creating your graph...
>Graph created!
>Please enter a name to start from

Enter the first name you want navigate from. Then, the following prompt will appear on your screen.

>Please enter a name to end at

Enter the name you want to navigate to. Finally, you will prompted to enter the maximum distance you want to traverse in order to find a path. If a path is found the screen will show:

>I'm finding the path between these people... please specify a max distance for me to search in.
9
Path exists within 9 nodes!
>_____________________________ PATH ___________________________________

>tom
> |__andrea
>     |__ryan
>         |__christina

If a path is not found, it will instead display:

>Path does not exist within 900 nodes...

Thank you for using the Networker. We hope you had a good experience!
