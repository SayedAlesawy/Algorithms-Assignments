import os

input_data_file = "input_p3.in"
output_data_file = "output_p3.out"
running_time_file = "p3.time"
student_output_file = "my_output_p3.out"

print("Compiling source code...")
os.system("rm " + student_output_file)
os.system("g++ -std=c++11 hw3_p3.cpp -o output")

print("Running binary file...")
os.system("./output " + str(input_data_file) + " " + str(student_output_file) + str(running_time_file))

print("Validating output...")

arr1, arr2 = [], []

with open(student_output_file, "r") as f:
    for i in range(15):
        arr1.append(f.readline().rstrip("\n").split(" ")[1])

with open(output_data_file, "r") as f:
    for i in range(15):
        arr2.append(f.readline().rstrip("\n").split(" ")[1])

if arr1 == arr2:
    print("Hurray Correct Submission :)")
    # print(arr1)
    # print(arr2)
else:
    print("Bad Luck Wrong Submission :(")
    print("our solution: ", arr2)
    print("your solution: ", arr1)
