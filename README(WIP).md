#Get_next_line	

##
create line: read, malloc, assign
	Counts the length of a line for malloc and returns the line.
	A) file is buffered until next->line on the STACK as a STATIC VAR: it's life spans outside the func 
	buffer size needs to fit entire file, all on stack if cycled until the end.
	struct saves line and next on heap, prints line.
##Buffer management:
The static buffer is scaled to either A) a size flag at compilation or B) a hardcoded default size if no size is defined at compilation. In a whle loop, characters are read() from the FD into the static buffer until the buffer fills up, then the buffer is "flushed" to the utility functions. This process is rinsed and repeated until \n is encountered.

The buffer could also be read at once totalling BUFFER_SIZE number of characters. Then a function call inside the loop to strchr() will check whether \n was inside that part. If so, the loop exits. The last part would have garbage beyond the \n. 

Each piece from buffer needs to be saved for later combining, or combined on the fly as the pieces come. Combination on the fly would require some dynamic memory structure that can expand. It seems more straightforward to combine the pieces once they all exist, but here a custom structure akin to a dynamic list structure could be useful. Another would be a custom realloc() type function that reallocates the space to accommodate each new piece as they come.

The main function checks that there is no node yet, or that there is a node but it's not the end of line. If there is no node, or the node has no line end, it calls ft_readtostring(heads_arrayfd) to create more nodes in the array at the FD's position, after which it moves on to ft_strjoin. Whenever the main function is called, there's never more than one node left in the array slot at position fd.

Otherwise, if the linked list head at position fd in the heads_array already is a node with a line end, ft_strjoin will be called directly with said head as argument and processed directly for returning without creating any new nodes.

	the function has to know the last time it's called for the next line, to free it.
	if we don't know what will be the last call, where do we free next
	the caller knows, but doesn't tell, we must free() next when it's no longer needed


	read(1) char by char, loop until \n, add to buffer, get len
	buffer: BUFFER_SIZE macro may be defined at compile or may not. Must work either case.
