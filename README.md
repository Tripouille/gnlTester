# gnlTester (2019+)

Clone this tester in your gnl repository. (works on linux and mac, handles sigsegv on all tests, and timeout on mandatory part)
![alt text](https://i.imgur.com/uupv1UH.png)

# Commands
make m = launch mandatory tests  
make b = launch bonus tests  
make a = launch mandatory tests + bonus tests 

make vm = launch mandatory tests with valgrind  
make vb = launch bonus tests with valgrind  
make va = launch mandatory tests + bonus tests with valgrind  

You can change the timeout value in Makefile    
![alt text](https://i.imgur.com/jUimpaC.png)  

*FOR RIGOROUS TEST YOU SHOULD RUN ALL TESTS WITH VALGRIND*

# Outputs

![alt text](https://i.imgur.com/b9hjjWn.png)
![alt text](https://i.imgur.com/C0ul80f.png)

MOK / MKO = test about your malloc size (this shouldn't be tested by moulinette)  

# Report bugs / Improvement
Contact me on slack or discord : jgambard
