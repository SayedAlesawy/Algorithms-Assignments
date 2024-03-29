import sys
import os
import random

def is_int(x):
    try:
        int(x)
        return True
    except ValueError:
        return False

data_count = 10000000  # large array to make time difference between reursive and non recursive
unsorted_data_file = "p3_data.in" #the file to generate data in.
output_data_file = "p3_dataa.out"  # the file where the output of code exists.
running_time_file = "p3.time" # the file to write the running time.
data = []

print("Generating data...")
with open(unsorted_data_file, "w") as file:
    for i in range(data_count):
        randint = random.randint(1, 50000)
        data.append(randint)
        file.write(str(randint)+"\n")

data.sort()

print("Compiling source code...")
os.system("g++ -o output hw2_p3.cpp")
#If the compilation raised an exception, try this command instead (comment the previous line and uncomment the next one)
# os.system("g++ -o output P3.cpp -std=c++11")

print("Running binary file...")
os.system("./output " + str(unsorted_data_file) + " " + str(output_data_file) + " " + str(running_time_file))

print("Validating output...")
with open(output_data_file, "r") as file:
    try:
        i = 0
        for line in file:
            if line == "\n":
                continue
            if not is_int(line):
                raise ValueError("Wrong Submission A")
            if int(line) != data[i]:
                raise ValueError("Wrong Submission B")
            i = i + 1
        if i != data_count:
            raise ValueError("Wrong Submission C")
        print("Correct Submission")
    except ValueError as err:
        print(err.args[0])
