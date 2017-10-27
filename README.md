# "Sort of monopoly"

## Collaborators
- Rasmus Isager Kruuse: rkruus16@student.aau.dk
- Marcus Alexander Skytt: mask16@student.aau.dk
- Daniel Glenn Kartin: dkarti16@student.aau.dk
- Simone Bell Danielsen: sdanie16@student.aau.dk
- Nicolai Lorits: nlorit16@student.aau.dk
- Jens Jákup Egholm Gaardbo: jgaard16@student.aau.dk

## Dependencies

This is a list of the requirements in order to be able to run this program

- Unix-based system (Mac OS or Linux)
- cmake
- sfml-dev

[This page](https://www.sfml-dev.org/tutorials/2.4/compile-with-cmake.php) describes how to compile sfml using cmake.


## How to run
1. Open a terminal

2. Change into the desired directory on your machine:

```$ cd /path/to/the/directory```

3. Clone repository:

```$ git clone https://github.com/totalfreak/PCSS2017.git```

4. Change into the repo folder:

```$ cd PCSS2017```

5. Build program using cmake:

```$ cmake .```

6. Make program

```$ make```

7. Run executable file:

```$ ./clientExe```

## How to play

1. First choose if you want to Host a server(a) or Join an existing server(b)

    a. When hosting a game you will be asked to set how many players should play

    b. * To be specified

2. The lobby is where you wait for the other players to join

3. When it's your turn, roll the dice and watch the magic happen

## Program description
The program uses TCP (Transmission Control Protocol) to send data to and from the server and clients.
[*] More info to come

# Assignment issues
The assignment says to make two repositories, one for the client and one for the server, but we have only made one repository.
This is due to the way the assignment was formulated, that you should be able to host a server, join one and 
see available servers. This seems sorely impossible using two different executables, not even to mention two different repositories.
