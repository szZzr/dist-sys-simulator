# Distibuted System Simulator

The system that simulated at this work concerns a simple distributed system M/M/2, consisting of two Servers and two queues, figure 1. In this system, a `mm2.in` file is given as input and the `mm2.out` file as output. At the input file given at the following order mean arrival time,  mean service time of first server followed by the time (seconds) that required for the second one, and finally the probabilities $P_1 = 0.65$ and $P_2=0.35$, that related with the possibility to choose the first or the second server respectively to serve a job, figure 2. The system estimates the mean response time of system (mean response time), average number of jobs in the system, mean waiting time in the queues ), and average number of jobs in the queues when the simulation of running 40,000 jobs is complete.

<figure>
  <p style="text-align:center">
  <img  style="height:10vh" src="https://github.com/szZzr/dist-sys-simulator/blob/master/icon/1.png">
  </p>
  <figcaption align="center">Figure 1: Distributed system</figcaption>
</figure>

By mean service time ($μ_i$) it follows that the mean service time  ($\bar{μ_i}$):

* $\bar{μ_1} = 2 \Rightarrow s_1 = \frac{1}{μ_1} = \frac{1}{2} =0.5 $ 
* $\bar{μ_2} = 1 \Rightarrow s_2 = \frac{1}{μ_2} = \frac{1}{1} =1 $ 

by mean arrival rate ($λ$) it follows that the mean arrival rates of each queue ($λ_i$) and mean arrival time ($\bar{\lambda_i}$):

* $λ_1 = λ\cdot p_1 = 1 \cdot 0.65 \Rightarrow \bar{λ_1} = \frac{1}{λ_1}=1.53\dots$
* $λ_2 = λ\cdot p_2 = 1 \cdot 0.35 \Rightarrow \bar{λ_2} = \frac{1}{λ_2}=2.85\dots$

the $s_1, s_2$ correspond to mean service time of each server.

<figure>
  <p style="text-align:center">
  <img style="height:5vh" src="https://github.com/szZzr/dist-sys-simulator/blob/master/icon/2.png">
  </p>
  <figcaption align="center">Figure 2: Input Arguments <br/> [interarrival time, service time 1, service time 2, service probability 1, service probability 2]</figcaption>
</figure>

Additionally this repository also contains a simple example of a linear system with one queue and one processor.
