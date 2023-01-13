#Compile:
g++ Q1.cpp -o Q1 -pthread -std=c++11

#Compile for a.), one more fork is put between no.0 and 1 philosophy
g++ Q1.cpp -o Q1 -Deven_forks -pthread -std=c++11

#Compile for b.), the philosophy with high number have lower priority and need to wait longer before taking forks
g++ Q1.cpp -o Q1 -Dhigh_priority -pthread -std=c++11

#Compile for c.), every one eat for 1 second.
g++ Q1.cpp -o Q1 -Drandom_eating_time -pthread -std=c++11

#Run the code:
./Q1.out