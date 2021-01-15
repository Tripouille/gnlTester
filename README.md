# gnlTester (2019+)

Tester for the get next line project of 42 school (now with personalized leaks checking on mac, using valgrind on linux)  
If all your tests are OK and the moulinette KO you, please contact me on slack/discord.  
Clone this tester in your get_next_line repository. (works on linux and mac, handles sigsegv on all tests, and timeout on mandatory part)  
![alt text](https://i.imgur.com/uupv1UH.png)

# Commands
make m = launch mandatory tests  
make b = launch bonus tests  
make a = launch mandatory tests + bonus tests 


You can change the timeout value in Makefile    
![alt text](https://i.imgur.com/jUimpaC.png)  

*FOR RIGOROUS TEST YOU SHOULD RUN ALL TESTS WITH VALGRIND*

# Outputs

![alt text](https://i.imgur.com/u4Li6AM.png)
![alt text](https://i.imgur.com/KL3mc4F.png)

MOK / MKO = test about your malloc size (this shouldn't be tested by moulinette)  

# Report bugs / Improvement
Contact me on slack or discord : jgambard
