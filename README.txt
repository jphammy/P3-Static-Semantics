Static Semantics
Total 100 points.

/accounts/classes/janikowc/submitProject/submit_cs42801_P3 SubmitFileOrDirectory

Invocation: 
> statSem [file]
with file as before with implicit extension .input1
Wrong invocations will not be graded. 

Graded 90% execution 10% structure/standards.

Stat Semantics Definition

The only static semantics we impose that can be processed by the compiler (static) are proper use of variables.
Variables
Variables have to be defined before used first time (after satisfying syntax)
Variable name can only be defined once in a scope but can be reused in another scope. There are two options for scope
Two options for variable scope. You must include README.txt file listing on the first line either Global or Local to indicate your chosen scope option. If this info is missing projects will be tested and graded as global.

Global option for variables (100)
There is only one scope, the global scope, in the case, regardless of where variable is defined
Local option for variables (+20)
Variables outside of a block are global
Variables in a given block are scoped in this block
Rules as in C (smaller scope hides the outer/global scope variable)
Do not display the tree any more (points can be deducted).

P3 Suggestions
Modify the main function so that after calling parser and receiving the tree, the main will call the static semantic function on the tree.

If not sure if you can handle the local scope, implement global scope and then try to redo.

P3 Local Support
You may process all variables using local scope rules, or process variables in the outside <vars> as global and all other variables as local. This describes the latter.

Software support
Implement a stack adapter according to the following

Stack item type is String or whatever was your identifier token instance - the stack will process identifiers. You may also store line number or the entire token for more detailed error messaging
You can assume no more than 100 items in a program and generate stack overflow if more
Interface
void push(String);
just push the argument on the stack
void pop(void);
just remove
 int find(String);
the exact interface may change, see below
find the first occurrence of the argument on the stack, starting from the top and going down to the bottom of the stack
return the distance from the TOS (top of stack) where the item was found (0 if at TOS) or -1 if not found
Static semantics
Perform left to right traversal, and perform different actions depending on subtree and node visited
when working in <vars> outside of the first block, process the identifiers there as in the  global option (or process as local if desired)
when working in a <block>
set varCount=0 for this block
in <vars> of this <block> take the identifier v
when varCount>0 call find(v) and error/exit if it returns non-negative number < varCount (means that multiple definition in this block)
push(v)  and varCount++
otherwise when identifier token found (variable use)
find(v), if -1 try STV.verify(v) (if STV used for the global variables) and error if still not found
call pop() varCount times when leaving a block (note that varCount must be specific to each block)
