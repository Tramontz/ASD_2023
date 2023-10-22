#!/bin/sh

script output.txt

.\\bin\\main_ex1.exe C:\\profili\\u381672\\Desktop\\unito\\records_1.csv C:\\profili\\u381672\\Desktop\\unito\\sorted_string.csv 0 1 

.\\bin\\main_ex1.exe C:\\profili\\u381672\\Desktop\\unito\\records_1.csv C:\\profili\\u381672\\Desktop\\unito\\sorted_int.csv 0 2
 
#.\\bin\\main_ex1.exe C:\\profili\\u381672\\Desktop\\unito\\records_1.csv C:\\profili\\u381672\\Desktop\\unito\\sorted_float.csv 0 3 >> result.txt

#echo "Order k=300000" 
#.\\bin\\main_ex1.exe C:\\profili\\u381672\\Desktop\\unito\\records_1.csv C:\\profili\\u381672\\Desktop\\unito\\sorted_string.csv 300000 1 
#.\\bin\\main_ex1.exe C:\\profili\\u381672\\Desktop\\unito\\records_1.csv C:\\profili\\u381672\\Desktop\\unito\\sorted_int.csv 300000 2 
#.\\bin\\main_ex1.exe C:\\profili\\u381672\\Desktop\\unito\\records_1.csv C:\\profili\\u381672\\Desktop\\unito\\sorted_float.csv 300000 3 

#echo "Order k=1000000" 
#.\\bin\\main_ex1.exe C:\\profili\\u381672\\Desktop\\unito\\records_1.csv C:\\profili\\u381672\\Desktop\\unito\\sorted_string.csv 1000000 1 
#.\\bin\\main_ex1.exe C:\\profili\\u381672\\Desktop\\unito\\records_1.csv C:\\profili\\u381672\\Desktop\\unito\\sorted_int.csv 1000000 2 
#.\\bin\\main_ex1.exe C:\\profili\\u381672\\Desktop\\unito\\records_1.csv C:\\profili\\u381672\\Desktop\\unito\\sorted_float.csv 1000000 3

read -p "Press enter to continue"

