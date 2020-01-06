# Milestone 1

Milestone 1 is a project that we created as a part of two milestones that we have to do for this semester's course Advanced Programming 1

## Description

In this project we create an interpreter that interprets a given file in order to control and fly an airplane in the virtual scope of 
the program Flightgear Simulator.
The flightgear simulator allows us to connect to its server as a client and vice versa, meaning in this project we will connect to the simulator as a client in order to send commands to control the flight's information and change them, and the simulator will connect to our code as a client as a means to send the constantly changing values of the flight (e.g the airplane's altittude).

How does our project exactly do these steps?
-
The program opens a server that will allow the simulator to connect to, the simulator will connect to our server and will begin to 
send us values (10 times in a second) of the flight's state, then we will connect to the simulator as a client and throughout the program as we read and interpret the file that was provided to us, we will begin to send commands that will change and control the
airplane's behaviour, eventually resulting in the airplane's takeoff and the flight will begin (A picture of an airplane in the midst of it's flight is provided in this file).

### Usage

To use this project, you have to first add a file called generic_small.xml to the Data/Protocol folder which can be found in the Flightgear simulator's files (wherever you downloaded the simulator), then you run the flightgear simulator and go to the settings, scroll down and under Additional settings
add these two lines:

**--generic=socket,out,10,127.0.0.1,5400,tcp,generic_small**

**--telnet=socket,in,10,127.0.0.1,5402,tcp**

now we need to the compile the code, we compile it with the following line : g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread

then you have to run it using the following command: ./a.out filename (filename is fly.txt for this project)

Once the code is running our server will be listening and waiting to accept a connection, now all you have to do is launch the simulator and click on Fly!
so you have to do the following: 

**_1._ you have to first add a file called generic_small.xml to the Data/Protocol folder**

**_2._ you have to open the Flightgear Simulator and add the two lines under Additional settings.**

**_3._ you will compile the code with the given line.**

**_4._ run the program (in terminal) using the command ./a.out filename. (fly.txt is the filename that contains the commands that we will interpret and parse).**

**_5._ launch the flightgear simulator and click on Fly!.**

**_Note_**: the fly.txt should be in the same directory as the project!

#### Visuals

Here is an example of an airplane that we controlled and made fly.

![Flight exmaple](https://github.com/mohamadzah/Milestone-1/blob/master/Flight%20Example.PNG)

##### Support

You can find a lot of help on stackoverflow.com, the stackoverflow community has helped me a great deal and i know that they can do the same for you!

More on server-client relationship: https://en.wikipedia.org/wiki/Client%E2%80%93server_model

###### Authors

***The author(s) of this code is Mohamad Zahalka***

