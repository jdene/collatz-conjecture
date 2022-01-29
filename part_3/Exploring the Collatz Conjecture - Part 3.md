# Exploring the Collatz Conjecture - Part 3

<p> I wanted to find out if it is possible to generalize the Collatz Conjecture for any base, and find out if I would get the same results as using the standard base of 3. In the standard Collatz Conjecture, 2 is the base, or the divisor, and 3 is the multiplier.

In this article I investigate two hypotheses:

- Do different bases exhibit the same Collatz like behavior - every sequence ends at 1?
- For bases that have Collatz like behavior, do the multipliers have the same infrequency property as 3 does in the original conjecture?

# Generalizing the Collatz Conjecture

<p> In the original Collatz conjecture, the base is 2 and the multiplier is 3. I have seen people look at different multipliers used in the Collatz Conjecture, but I was wondering what the results would look like if different bases were examined instead. For a base of 2, 3 and its multiples are infrequent. If the conjecture is generalized, are the multiples of all multipliers just as infrequent as in the original conjecture?


<p>The key insight is to remember that in the standard Collatz Conjecture, if a number is even, it is divided by two. If a number is odd, it is multiplied by 3, and 1 is added. The Collatz function guarantees that if the current number is odd, the next will be even. The Collatz Conjecture is really two operations "fighting" each other, one pushing the current number towards infinity, the other towards 1. However, all numbers do eventually seem to end at 1.
</p>
<p>
What if this thinking is extended, to a base of five, rather than a base of two as in the original conjecture? If the value is divisible by five, then divide by five. If it is not, then following the logic of the Collatz Conjecture would mean multiplying this number and adding an offset so that it then becomes divisible by five. Depending on the value of n%5, where n is the current value, the next operation would either be 5n+4, 5n+3, 5n+2, or 5n+1.
</p>
<p>
Similarly, what if a base of 7 is chosen? If the number is divisible by 7, divide by 7. Otherwise, depending on the value of n%7, calculate 7n+6, 7n+5, 7n+4, 7n+3, 7n+2, or 7n+1 so that the next number will be guaranteed to be divisible by 7.
</p>
<p>
    The first thing I wanted to verify was if the modified Collatz sequence will work for all bases. I used the try/catch block below to find all bases that work between 2 and 100 for this approach. I used a maximum iteration of 10,000, as after this many iterations an infinite recursion is almost guaranteed.
</p>
```python
working_bases = []
for base in range(2,100):
    try:
        for n in range(1,10000):
            custom_collatz_slim(n,base)
        working_bases.append(base)
    except Exception as e:
        continue
```


Once I had a list of all working bases, it was time to test this custom "Collatz" function. I found that using base of 3 for example, causes the sequences to spiral out of control and will never reach 1. The code below shows the way I first implemented this function. This worked, but this specific implementation would only work for a base of 3, and the three if statements would check whether n%3 equals 2, 1 or 0. The problem with this approach is that for a base of k, k-1 `if` statements would need to be added to modify the function for that base.


```python
def custom_collatz(n):
    custom_collatz_arr.append(n)
    if n == 1:
        return 1
    if n > 1:
        if n % 3 == 2:
            print(4*n+1)
            return custom_collatz(4*n + 1)
        if n % 3 == 1:
            print(4*n+2)
            return custom_collatz(4 * n + 2)
        if n % 3 == 0:
            print(n // 3)
            return custom_collatz(n // 3)
    return custom_collatz_arr
```

<p> The revised function below takes care of those shortcomings. The function recursively returns n // base in the case that n % base is 0. If n % base is not 0, the last line will guarantee that in the next iteration, n%base becomes 0, and n will be divided by base: the behavior exhibited by the Collatz function! </p>

```python
def custom_collatz_slim(n, base):
    if n == 1:
        return 1
    k = n % base
    if k == 0:
        return custom_collatz(n // base, base)
    return custom_collatz((base + 1) * n + (base-k), base)
```

I originally thought that maybe only bases that are prime numbers would work, but it turns out that the numbers which worked as bases were fairly uniformly distributed. Below are histograms for stopping times of various bases, with starting values from 1 to 2000. The first plot, base 2, shows stopping times for effectively what is the original Collatz Conjecture. The other bases show what happens for other bases using the generalized conjecture. I also generated a larger plot showing histograms for all working bases below 100, which can be viewed here.

![6_bases_histogram](https://github.com/jdene/collatz-conjecture/blob/main/part_3/plots/6_bases_histogram.png)

The histogram below shows Collatz sequences from 1 to 2000 and the stopping time for each Collatz sequence. The blue plot shows the standard Collatz sequence, with a base of 2, and the orange plot shows the generalized Collatz function using a base of 7. Similarly, the second histogram shows the same plot for base of 2, and base of 98. While the plots for base of 7 and base of 98 are both shifted, they both seem to have clear discrete bands. 

![histogram_2_7](https://github.com/jdene/collatz-conjecture/blob/main/part_3/plots/histogram_2_7.png)

![histogram_2_98](https://github.com/jdene/collatz-conjecture/blob/main/part_3/plots/histogram_2_98.png)

The next part of my investigation was focused on verifying if the infrequency of multiples of base+1 holds using the generalized Collatz function. I decided to choose a base of 7, meaning I would hypothesize that all numbers that are multiples of 8 would be infrequent. After plotting the data generated, it turns out that this is the case.

![freq_of_mult_8](https://github.com/jdene/collatz-conjecture/blob/main/part_3/plots/freq_of_mult_8.png)

In the above plot, all multiples of 8 are shown in red. Multiples of 8 have significantly lower frequencies in the first 1000 Collatz sequences using this modified function.

The plot below shows the distribution of multiples of the first ten multiples of 8. Values of 1 represent starting numbers of "Collatz" sequences which contain the specific multiple of 8. For example, 8 occurs in three of the first 1000 sequences of this "Collatz" function, and 80 occurs in two.

![distribution_of_mult_8](https://github.com/jdene/collatz-conjecture/blob/main/part_3/plots/distribution_of_mult_8.png)

What all of this data means, is that the infrequency of bases holds for other bases besides 2. Effectively, the Collatz Conjecture can be extended to many different bases, and the properties which appear in the original conjecture are also present in the generalized conjecture.

In the process of writing these three articles, while I of course learned a lot about the Collatz problem, it was also a great exercise in C, Python, and visualizing data using gnuplot and matplotlib. Visualizing infrequencies of multiples and other interesting properties gave me much more insight into this unsolved mathematical mystery. There are still many different paths that can be explored within this problem: for example, is there a pattern to bases which work with the generalized function, multipliers other than base+1, frequency patterns of numbers other than the multiplier and its multiples, and many more.