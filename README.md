# **`Bioinformatics Algorithms`**

# **Multiple Pattern Matching Problem**

$n$ = length of text \
$m_i$ = length of each pattern \
$p$ = number of patterns

## `Bruteforce Algorithm`

$$
O(n*m_1+ n*m_2 + ... + n*m_p) \\
= O(n*\sum_{i=1}^{p}m_i) 
$$

## `KMP Algorithm`

$$
O( (n+m_1) + (n+m_2) + ... + (n+m_p) ) \\
= O(n*p + \sum_{i=1}^{p}m_i) 
$$

## `Trie`

Preprocessing for calculating **Trie(patterns)**
$$
O(\sum_{i=1}^{p}m_i)
$$

Pattern Matching
$$
O(n * max(m_i))
$$

Finally, the total time complexity is
$$
O(\sum_{i=1}^{p}m_i + n * max(m_i))
$$