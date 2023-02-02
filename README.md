# NIM

## 1. Files
 This repo contains the readme that you're reading, a Makefile, and and five .c and .h files:
fonctions.c and fonctions.h are the files containing all the code for the game to take place between two humans; AI.c and AI.h contain the code required to run the different menus, and to play a game against the computer, and main.c simply starts the program.

## 2. How to use
 If you are using ubuntu, just use the "make" command, and it will recompile and run automatically.
 If you're using another OS, you'll have to recompile the source code for yourself.
 Once you rune the program, a menu will open and ask you if you want to play player v. player, or against an AI. If you choose AI, you'll get to choose how smart you want the computer to be, then which turn you play, or let the computer decide randomly the turn for you.
 For now, there are two difficulties: either the AI plays randomly (basic AI) or it can play perfectly (hard AI, it still can be defeated if you play perfectly, depending on who starts).

## 3. Future improvements
- I'll code an AI that plays using a minimax algorithm (to make intermediate level difficulties)
- In the long term, I'll make a simple GUI