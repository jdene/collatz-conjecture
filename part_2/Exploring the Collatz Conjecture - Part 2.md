<h1>The Simplest Math Problem We Still Can't Solve - Part 2</h1>

<p>This is the second part of a two part article aimed at analyzing the Collatz Conjecture. If you haven't read the first part, you can do so <a href="https://medium.com/@denelsky/the-simplest-math-problem-we-still-cant-solve-part-1-61cd767d33dc">here</a>. Code used in this article can be found at <a href="https://github.com/jdene/collatz-conjecture">github.com/jdene/collatz-conjecture</a><em></em>.
<p>Plenty of information already exists on the Collatz Conjecture, but actually implementing the algorithm and observing how it works gave me a much better feel for how it works. I also undertook this project to gain a deeper understanding of programming in C and Python. Full code can be found on my GitHub.
<p>
Part one of this series provides a brief overview of the Collatz Conjecture. This article will investigate some of the patterns which are found within the Collatz sequences, visualized using Python. I undertook this investigation both to explore these intriguing aspects of the Collatz conjecture, and to refine my Python skills.
</p>

# Visualizing the Collatz Conjecture using Python

<p>The first thing I did to start modeling the Collatz Conjecture using Python was to write a simple recursive function to model the path a number takes down to 1, shown below.</p>

```python
collatz_arr = []
def collatz(n): # takes a value n, returns the collatz sequence for n
    collatz_arr.append(n)
    if n == 1:
        return 1
    if n > 1:
        if n % 2 == 0:
             return collatz(n // 2)
        else:
             return collatz(3 * n + 1)
    return collatz_arr
```

<p>Three and its multiples supposedly occur "infrequently." I wasn't sure what this really meant, so I decided to investigate further. In order to do this, I calculated a large number of Collatz sequences and counted the number of times each value shows up.</p>


```python
# collatz_arr is updated every time collatz() is called
# takes a value n, and calculates each collatz sequence from 1 to n
# returns a dictionary which contains the number of occurances of the key in all Collatz sequences
def collatz_helper(n):
    for i in range(1, n+1):
        collatz_arr.clear()
        collatz(i)
        for num in collatz_arr:
            if num not in freq_dict:
                freq_dict[num] = 1
            else:
                freq_dict[num] += 1
	return freq_dict
```

<p> The function above takes a number n, and calculates each Collatz sequence from 1 to n. For each Collatz sequence, the frequencies of all intermediate values are recorded. The plot below shows frequencies of all intermediate values in all Collatz sequences from 1 to 300</p>

![All Frequencies from 1 to 300](https://github.com/jdene/collatz-conjecture/blob/main/part_2/plots/initial-py-plot-labeled.png)

<p> The first thing that is important to notice is that the frequency of 1 is 300. This makes sense as each Collatz sequence from 1 to 300 will contain 1 exactly one time. The frequency of 2 is 299, 4 is 298. This makes sense, as every Collatz sequence terminates with 4,2,1. Except of course, 4 doesn't occur in the sequence of 2 and both 4 and 2 don't occur in the sequence for 1. 
<p>Another interesting feature of this graph is that three and multiples of three typically have very low frequencies, compared to other numbers. Why is this?</p>


<p>
Every odd number n is mapped to 3n+1, which is not a multiple of three. Intuitively, it seems reasonable that there are fewer multiples of three than other numbers. However, this is not a proof.
</p>
The plot below is similar to the frequency plot above, but just shows the first 80 values found in all Collatz sequences computed with starting numbers from 1 to 1000. This plot makes it easier to see just how infrequent multiples of three are compared to other values, as the total of 1000 Collatz sequences are represented in this data. Multiples of three are shown in red.

![Frequency Quantified](https://github.com/jdene/collatz-conjecture/blob/main/part_2/plots/freq_quantified.png)

<p> To further investigate, I decided to see which numbers actually had the value 3 in their Collatz sequence. The function below takes a number n, and plots the Collatz sequence for that number n. If 3 is a member of its Collatz sequence, 1 is plotted for that value on the x axis. Otherwise, -1 is plotted.</p>

![Frequency of Three](https://github.com/jdene/collatz-conjecture/blob/main/part_2/plots/freq-of-three-labeled.png)

The distribution of sequences with a 3 in them seems to be distributed in a familiar way - maybe exponentially? To confirm this, I created the plot below.

![Frequency of Three Log](https://github.com/jdene/collatz-conjecture/blob/main/part_2/plots/freq-of-three-log.png)

<p> The plot above confirms that all Collatz sequences which contain the value 3 were in fact distributed exponentially. If the starting number of all Collatz sequences that contain a three are plotted on a log scale, the plot is a straight line which shows that the gaps between occurances of three are distributed exponentially. It is difficult to discern why this is.</p>

If three shows up in the Collatz sequence in an exponential distribution, how about multiples of three? The plot below shows the distribution of multiples of 3, between 3 and 30 in the Collatz sequence. Values of 1 represent the starting numbers of Collatz sequences which contain the specific multiple. For example, 3 occurs in nine Collatz sequences between 1 and 1000, while 30 only occurs in four.

![Distribution of Multiples of 3](https://github.com/jdene/collatz-conjecture/blob/main/part_2/plots/distribution_of_multiples_of_3.png)

I also decided to create a plot which shows the number of multiples of three in all Collatz sequences. Each Collatz sequence is plotted on the x-axis, and the number of values which are multiples of 3 in the corresponding sequence is plotted on the y-axis. This plot is shown below. Interestingly, the only values on this plot are numbers in the range 0 to 9. This means that all Collatz sequences between 0 and 1000 have at most 9 multiples of 3.

While multiples of three in Collatz sequences do occur very infrequently, what about other multiples such as multiples of 5. The below graph shows that multiples of 5 occur much more commonly in Collatz sequences. They also don't occur in any recognizable distribution, as the multiples of three do.

![Distribution of Multiples of 5](https://github.com/jdene/collatz-conjecture/blob/main/part_2/plots/distribution_of_multiples_of_5.png)

This is a histogram of the number of multiples of three for each Collatz sequence. It is important to keep in mind the y-axis scale, has a maximum of 10. So even the Collatz sequences with the highest values on this plot actually have few multiples of three. In my research of the Collatz problem, this result is not one I have seen visualized in this way.

![Multiples of 3](https://github.com/jdene/collatz-conjecture/blob/main/part_2/plots/mult_of_3_freq.png)

Even a problem which appears to be extremely simple, yields a number of fascinating patterns. In this article I analyze the phenomena of 3 and its multiples being infrequent, both visually and analytically. Writing this article helped me understand the Collataz conjecture in even more depth. It also helped show me the importance of containerizing code, and making it reusable. Using a consistant naming scheme in my code also ended up being a big help. After completing this analysis, it really made me think: I don't know how mathematicians even began to analyze problems like these without computers!

