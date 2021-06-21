# Walden-Internship

Includes code I have written for a SwatWorks micro-internship with Walden Local Meat Co. I tested and implemented a 5-step algorithm that the company uses to deliver meat to its customers at favorable, cost-efficient times.

### zipcodes.cpp

Contains the implementation of the methods of the ZipCode class, parser functions for storing delivery and zip code data in memory, and functions that evaluate delivery algorithms based on different efficiency metrics.

### main.cpp

Takes in two inputs from the command line: a zip code and a date of last delivery. Returns the next delivery date based on both the original algorithm and the new one. Note that code for the actual delivery algorithm has been redacted per an agreement with my mentor and the company.

### validate.cpp

Takes in one input from the command line: 0 or 1. Program will test the original and new delivery algorithms by looking at average convergence times (for 0 input) and success rates (for 1 input) for each, based on the user's preference.

### project.pdf

This is a write-up of the work I did throughout the duration of my internship. Similarly to the code, I have redacted some sensitive information that Walden has asked me not to share.
