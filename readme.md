
# Problem definition
In this project, we are required to apply file compression using character-based LZ77 compression algorithm. C / C++ programming languages will be used for the project.

# Requirements
- The uncompressed file to be used as input will be in the form of a text file (text.txt).
- Each character in the file will be read.
- Output file (compressed text file) will be generated for each compression algorithm.

# LZ77 Compression Algorithm
Generally, there are repetitive parts in the prepared text documents. Especially;
- conjunctions and pronouns,
- suffixes at the beginning and end of other words,
are frequently repeated in texts.

The purpose of the LZ77 algorithm is to eliminate repeating sections in text documents and to compress the text document accordingly.

In the LZ77 approach, the dictionary is part of the previously encoded series. The size of the search buffer in the algorithm determines the size of the previously coded series to be searched. The larger the search buffer, the higher the compression ratio, but also the higher the compression time.

**Example**

Compressing the word “abracadabra” with the LZ77 algorithm.

- The first character of the forward buffer, a, is searched in the search buffer from beginning to end. 
- In the second comparison, similarity is found, but since this character is followed by the character d, not the character b, the similarity length is only 1. 
- The search continues. Two characters later, there is another a, followed by c, so its similarity length is 1. 
- The search continues. At the beginning of the search buffer, that is, in the forward buffer, there is another a at 7 distance (offset=7) from the searched character. This time the similarity length is 4 (abra).
- It is triple encoded as [7,4,C(a)] with the character a after the "abra" series in the forward buffer. The a character at the end of the forward buffer is encoded as [0,0,C(a)].

# Ease of Use 

- When you run the program, the project reads directly from the file named "text.txt" without asking you for an input or selection.
- If there is no file named "text.txt" it will give an error and go to the output.
- The read text is compressed using the LZ77 algorithm and the compressed text is written to the output file named "lz77_cikti.txt".
- The size of the original text and the size of the compressed text are printed on the screen.
- If the original size is larger than the compressed size, the compression percentage is calculated and printed to the screen along with advice to use it in compression.
- If the original size is smaller than the compressed size, the percent compression (in this case the percent expansion) is calculated and printed on the screen along with warning that it should not be used for this text.
- If the text size has not changed, this information is also printed on the screen.
- Then the program goes to the exit.
