# Huffman
Assignment to implement Huffman compression in C

Group Members: Sterling Rohlinger, Nikolo Sperberg, Karin Knapp

To compile the code, use the command gcc -o huf.o *.c -std=c99 -Wall. To compress a file, use ./

For our encode method, our logic was to take in the name of the file we want to encode, and to create the output file. While we had not reached the end of the file, we created a new tnode, and set it to the location of our array list at our temp value. While our tnodes still had a parent, if the tnode is the right child, we added 1 to our array to output, and if not, we added a 0. Once the number of bits went over 8, we wrote out the byte to the output file.  

Our decode is similar, except that we worked from the top of the tree down. While we hadn’t reached the end of the file and found the leafNode, and neither the left or right children were null, if the number was a 1 then we would move to the right of the tree, and if it was a 0 then we would move to the left, and then scan in the next number. Once the leafNode was found, then we wrote to the output file the letter from that node. 
