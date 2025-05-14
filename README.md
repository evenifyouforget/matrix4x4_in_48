# matrix4x4_in_48
Multiplication of two 4x4 matrices using 48 scalar multiplications using Winograd's algorithm.

Note: This algorithm does not work if the types are non-commutative (as it relies on some particular cancellations). 49 is the best known for the general case.

Demo code (not production ready) is provided.
Try `build_and_test.sh`.

## Algorithm description

Sources:

* https://math.stackexchange.com/a/662382/1298784
* https://era.ed.ac.uk/handle/1842/4734

Define the ausiliary quantities:

$$A^{(i)} = A_{i,1} A_{i,2} + A_{i,3} A_{i,4}$$

$$B^{(j)} = B_{1,j} B_{2,j} + B_{3,j} B_{4,j}$$

Then

$$(AB){i,j} = (A_{i,1} + B_{2,j}) (A_{i,2} + B_{1,j}) + (A_{i,3} + B_{4,j}) (A_{i,4} + B_{3,j}) - A^{(i)} - B^{(j)}$$

## Other previous results

Source:

* https://math.stackexchange.com/a/4546116/1298784
* https://www.nature.com/articles/s41586-022-05172-4/figures/6

Google DeepMind in 2022 apparently found a 47 multiplies algorithm, but only for mod 2.

## AlphaEvolve's claims in 2025

Source:

* https://storage.googleapis.com/deepmind-media/DeepMind.com/Blog/alphaevolve-a-gemini-powered-coding-agent-for-designing-advanced-algorithms/AlphaEvolve.pdf

Google DeepMind claims their AI found a method to multiply two 4x4 matrices in 48 scalar multiplications, beating the previous best of 49.

I was not able to verify their 48 algorithm. It uses complex numbers, so I am almost certain this is not a general algorithm.

Winograd's algorithm works for complex numbers, so the record was already 48 for complex numbers.

Google's claim of finding a new record of 48 seems to be misleading, if not outright bogus.