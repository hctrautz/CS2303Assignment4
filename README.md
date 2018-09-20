README for PA4 -- Hunter Trautz and Gabriel Aponte, Event Based Simulation
------------------------------------------------------------------
Instructions for compiling:
Type 'make' from the command line in the project directory.
------------------------------------------------------------------
To Run:
Type “./qSim #customers #tellers simulationTime averageServiceTime <seed> (optional)”
------------------------------------------------------------------	
Description: 
This program simulates customers arriving at a bank and standing in line in front of one of the tellers. People arrive at random intervals. Each person waits in his/her selected line until reaching the head of that line. When a person reaches the head of his line, the teller provides service for a random amount of time. After the service is completed, the person leaves the bank. The entire purpose of this simulation is to compare the performance of a single line serving all tellers versus separate lines for each teller. 
------------------------------------------------------------------
Customers:
Customers are represented as a linked list of Customer

Tellers:
Tellers are represented as a linked list of Teller

Events:
There are two types of events, a CustomerEvent and a Teller Event. Both extend the class their parents class Event. 

------------------------------------------------------------------
Sample Output Code: 

Example #1 with more customers than tellers:
Command used: "./qSim 100 4 60 2.3"

Statistics 
Total Customers Served: 100
Total Time Taken to Serve: 249.119
Total Tellers: 4
Queue Type: Per-Teller 

Average Customer Time Used: 111.047
Standard Deviation: 42.9586
Maximum Customer Wait Time: 191.985
Total Teller Service Time: 240.046
Total Teller Idle Time: 605

Statistics 
Total Customers Served: 100
Total Time Taken to Serve: 194.331
Total Tellers: 4
Queue Type: Common 

Average Customer Time Used: 89.0636
Standard Deviation: 38.0789
Maximum Customer Wait Time: 138.473
Total Teller Service Time: 241.578
Total Teller Idle Time: 519
------------------------------------------------------------------
Example #2 with the same amount of customers and tellers:
Command Used: "./qSim 100 4 60 2.3"

Statistics 
Total Customers Served: 10
Total Time Taken to Serve: 164.201
Total Tellers: 10
Queue Type: Per-Teller 

Average Customer Time Used: 40.6228
Standard Deviation: 48.654
Maximum Customer Wait Time: 140.538
Total Teller Service Time: 24.9266
Total Teller Idle Time: 916

Statistics 
Total Customers Served: 10
Total Time Taken to Serve: 60.7739
Total Tellers: 10
Queue Type: Common 

Average Customer Time Used: 2.66609
Standard Deviation: 1.3546
Maximum Customer Wait Time: 4.46492
Total Teller Service Time: 26.6609
Total Teller Idle Time: 760
------------------------------------------------------------------
Example #3 with more tellers than customers:
Command Used: "./qSim 5 10 60 2.3"

Statistics 
Total Customers Served: 5
Total Time Taken to Serve: 111.413
Total Tellers: 10
Queue Type: Per-Teller 

Average Customer Time Used: 17.4416
Standard Deviation: 24.3064
Maximum Customer Wait Time: 64.4274
Total Teller Service Time: 12.7591
Total Teller Idle Time: 315

Statistics 
Total Customers Served: 5
Total Time Taken to Serve: 51.7922
Total Tellers: 10
Queue Type: Common 

Average Customer Time Used: 3.28671
Standard Deviation: 1.31291
Maximum Customer Wait Time: 4.59505
Total Teller Service Time: 16.4335
Total Teller Idle Time: 365
-------------------------------------------------------------------
Analysis: 
All of these examples show that the common queue type is superior in all cases over the per-teller type. 

