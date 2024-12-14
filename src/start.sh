#!/bin/bash

# Get the current terminal emulator
TERMINAL=$(basename "$SHELL")

# Define the path to your compiled program
PROGRAM_PATH=$(realpath MyProject)

# Open two terminal windows and run the program with specific terminals
gnome-terminal -- bash
#gnome-terminal -- bash -c "$PROGRAM_PATH; exec bash"

