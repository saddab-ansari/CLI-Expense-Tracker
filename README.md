Personal Expense Tracker System ------------------------------------------------------------------------------

Project Overview
A comprehensive console-based application developed in C Language to help users track their daily spending. 
This project utilizes File Handling to ensure data persists even after the program is closed. 
It allows users to record expenses, set monthly budgets, and generate detailed reports.

Key Features -------------------------------------------------------------------------------------------------

Add Expenses: Record ID, Date, Amount, Category, and Notes.

View History: Display all records in a clean, tabular format.

Budget Management: Set a monthly limit and get warnings if you overspend.

Reports: Generate total spending calculations for specific Months or Years.

Data Persistence: Automatically saves data to text files (expenses.txt).

Technical Details-----------------------------------------------------------------------------------------

Language: C (Standard Library)

Concepts Used:

Structure (struct) for data grouping.

File I/O (fopen, fprintf, fscanf) for database management.

String Handling and Formatting.

Control Structures (Loops, Switch-Case).

How to Run ----------------------------------------------------------------------------------------------

Compile the program using a C compiler (like GCC):
Bash

Compile the program by  : gcc expense.c -o tracker 

Then run the program by : ./tracker

File Structure------------------------------------------------------------------------------------------

expense.c - The main source code.

expenses.txt - Automatically created; stores expense history.

Author --------------------------------------------------------------------------------------------------

Name: Saddab Sabir Ansari

Course: EEL Final Project : Semester 1

Date: December 2025
