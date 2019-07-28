## cd to the below directory before running the program

cd ~/gojek_assignment/parking-lot-1.4.2/parking_lot



##To run the program on mac OSX, you can compile using clang++ as compiler

clang++ -std=c++17 src/main.cpp -Iinclude/ -Wc++11-extensions -Wall -Werror -o bin/parking_lot 



##To run the program on unix machine, you can compile using g++ as compiler

g++ -std=c++17 src/main.cpp -Iinclude/ -Wc++11-extensions -Wall -Werror -o bin/parking_lot


## To run the program for command line mode/ interactive mode

bin/parking_lot



##To run the program for file as input

bin/parking_lot  <filename with path>
E.g.  bin/parking_lot functional_spec/fixtures/file_input_test1.txt





