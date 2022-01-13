<h1>The Simplest Math Problem We Still Can't Solve - Part 1</h1>

<p>The Collatz Conjecture, named after German mathematician Lothar Collatz, initially appears to be a simple proposition. Take any positive integer <em>n</em>. If the term is even, divide by two. If the term is odd, multiply it by three and add one. A sequence can then be formed by performing this operation 
    multiple times. The resulting sequence will always decay to 1. </p>
<p>Plenty of information already exists on the Collatz Conjecture, but implemenging the algorithm and observing how it works gave me a much better feel for how it actually works. I also undertook this project to gain a deeper understadning of programming in C. Full code can be found on my github, <a href="https://github.com/jdene/collatz-conjecture">github.com/jdene/collatz-conjecture</a> </p>


<p>The Collatz conjecture can be expressed simply in a piecewise function:</p>

<img src="https://github.com/jdene/collatz-conjecture/blob/main/part_1/collatz_function.png" alt="Collatz Function" width="400" class="center"/>

<p>The numbers that result from a Collatz sequence are known as "Hailstone Numbers", due to their rising and falling behavior similar to that of hail in a cloud. The Collatz conjecture states that the total stopping time of every positive integer is finite, and eventually ends in 4, 2, 1.</p>

<p>The piecewise function above can modeled using a simple function in C with only a single line of code. Alternatively, this can be achieved using a simple if-else statement, but this implementation greatly reduces the amount of code needed. The ternary operator can be used to construct an if-else statement using the following syntax:</p>

```c
condition ? value_if_true : value_if_false
```

<p>The following C function is used to model the above piecewise function. The first statement (n & 1) is designed to determine if the input n is odd or even. Any number ANDed with 1 will always be 0 if even, and 1 if odd. This works well with the ternary operator, as in the C language 0 is interpreted as false, and 1 as true. Thus, the second part of this equation will run when true, and the third when (n & 1) is false. In the third part, a shift right operator is used to increase efficency. When dividing in C, the compiler will attempt to divide by using a series of multiplication, shift and addition instructions (most CPUs dont have division instructions, but can easily shift bits). To make the calculation as efficent as possible, we work with the CPU, and use a bit shift operation to achieve the same result as n / 2.</p>

```c
// if-else statement using ternary operator
unsigned int collatz(unsigned int n){                                                                                                                                                                                        
    return (n & 1) ? (3*n + 1) : (n >> 1);                                                                                        
}                                                                                                                               
```

<p>When this function is called over and over again, a Collatz sequence for a given number can be modeled. What is especially interesting about the Collatz sequence is that a number's distance from another number has no affect on the number of steps it will take to reduce to 1. The graph below models the stopping time for 341. After it spikes to 1024, it quickly reduces to 4, 2 finally 1.</p>

![Stopping Time for 341](https://github.com/jdene/collatz-conjecture/blob/main/part_1/gnuplot/341.png)

<p>The next plot shows the path taken by 342. While this is just 1 away from 341, it's path looks vastly different. Collatz sequences don't seem to have any obvious relationship to numbers that are close sequentially. But can any pattern be found in Collatz stopping times?</p>

![Stopping Time for 342](https://github.com/jdene/collatz-conjecture/blob/main/part_1/gnuplot/342.png)

<p>Another possible way to visualize the Collatz function is by examining each input to the function, and the corresponding number of steps it takes to "stop", or to decay to the 4-2-1 loop. Below is a plot showing inputs to the Collatz function from 1 to 1000 and each value's corresponding stopping time.</p>

![1 to 1000 Stopping Time](https://github.com/jdene/collatz-conjecture/blob/main/part_1/gnuplot/stoppingtime.png)

<p>Observing the graph above, there appear to be clear discrete bands which seem to follow the same general trend as that of an exponential decay function.</p>

<p>The C language and gnuplot, used to generate the plots above are relatively limited, so I decided to switch to Python to analyze this data in further depth.</p> 

<p>Stay tuned for part 2 of this series, where this fascinating problem is visualized in even more depth!</p>
