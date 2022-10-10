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

## `Suffix Trie`

Preprocessing for calculating **SuffixTrie(text)** using all the suffixes of the text

$$
O(n^2)
$$

Pattern Matching

$$
O(\sum_{i=1}^{p}m_i)
$$

Finally, the total time complexity is

$$
O(n^2 + \sum_{i=1}^{p}m_i)
$$


## `Suffix Array`

Preprocessing for calculating **SuffixArray(text)**

$$
O(n * log(n))
$$

Pattern Matching

$$
O(p * log(n))
$$

Finally, the total time complexity is

$$
O(n * log(n) + p * log(n)) \\
= O( (n+p) * log(n)) \\
$$

> greatly reduced memory complexity