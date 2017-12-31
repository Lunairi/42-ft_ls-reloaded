# 42-ft_ls-reloaded
Re-writing my ft_ls to have better data structure and improved functionality. First time I did ft_ls was for learning system, this time the goal is to improve optimization.

My original ft_ls can be seen here: https://github.com/Lunairi/42-ft_ls

The main problem with that ls is:
1) Poor data structuring lead to poor functionality
2) Sorting was very slow due to accessing too many sorting algo
3) Accessed stats multiple time to track and create behaviors

With this reloaded version where I re-write my ls I wanted to focus on:
1) Using a link list to improve and optimize data structuring
2) Reduce the amount of times I need to sort
3) Simplify the data so there is less redundancy in the code
4) Fix all the prior bugs in my previous ls