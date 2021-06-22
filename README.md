# Walden-Internship

Includes code I have written for a SwatWorks micro-internship with Walden Local Meat Co. I tested and implemented a 5-step algorithm that the company uses to deliver meat to its customers at favorable, cost-efficient times.

### zipcodes.cpp

Contains the implementation of the methods of the ZipCode class, parser functions for storing delivery and zip code data in memory, and functions that evaluate delivery algorithms based on different efficiency metrics. Note that code for the actual delivery algorithm has been redacted per an agreement with my mentor and the company.

### main.cpp

Takes in two inputs from the command line: a zip code and a date of last delivery. Returns the next delivery date based on both the original algorithm and the new one. This code will not run because the methods it uses have been deleted from the zipcodes.cpp file.

### validate.cpp

Program will test the original and new delivery algorithms by looking at average convergence times and success rates for each.

### .txt files

These were originally proprietary input which included delivery data with information about shares and regions. The proprietary information within them has been redacted, and each file is replaced with a short version

### project.pdf

This is a write-up of the work I did throughout the duration of my internship. Similarly to the code, I have redacted some sensitive information that Walden has asked me not to share. It goes extensively into explaining the data analysis techniques I used and the different functions I implemented.
