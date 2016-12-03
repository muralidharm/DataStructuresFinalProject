# DataStructuresFinalProject

REPORT

Tool

Logistics of Scoring
The tool we created scores source code on a scale ranging from 0 to 100, with 0 representing perfectly formatted source code and 100 representing source code that performed incredibly poorly on all metrics. We have constructed five metrics, and each of the metrics counts for a total of 20 percent of the overall score. Thus, if a certain source code file performs very well on all metrics except for one, they would receive a score nearing 20 out of 100. On the other hand, a source code performing well on only one metric and scoring poorly on the other four would receive an overall score of around 80 out of 100.

Implementation of Grader
The tool is implemented with a “grader” class which has several member functions to perform the actions necessary to properly analyze the source code. Five of these functions represent the five different scoring metrics, each scoring the source code on a scale of 0-20. For each metric function, a score is first calculated for each file and then a total score for the project is given by taking an average of all scores for each file. Another bonus metric is represented in a sixth function, which subtracts points for code complexity to augment the score of more complex code bases compared to simpler ones. Another method parses through the source code of each file, saving each line as a ****. This also enables us access to the number of lines in each file as the size of each linked list object. The seventh method takes the scores from the various metrics, sums them to create an overall score for the code, and then provides an either a brief or verbose output detailing the analysis. The brief output merely reports the score for each metric, while the verbose output gives a thorough detailing of the metric’s scoring and analysis. Some metrics allow for mathematical analysis while others present a more conceptual idea.

Usage of New Data Structures
	Two separate hash tables were utilized in the project. The first was implemented to store each line read in from the file along with the file name. The file name served as the key for the hash node, and the line of code itself, saved as a string object, served as the value. Therefore, all lines of code for one particular file of source would be stored in the same row of the hash table. The second hash table was utilized to store instances of control statements, such as for loops and if statements. In this table the file name served as the key for the hash node, and the line of code containing the control statement was stored as a string as the value.
	In addition, an AvlTree was implemented in order to store user-defined and primitive type variable names. When reading in the files, these names were read into string objects and added to the tree. The number of instances these variables were used could then be found.***

Metrics

I. Metric to Assess the Length of Each Line of Code
	The first metric we developed measures the number of characters in a line and provides a score based on how many lines exceed eighty characters. Since eighty characters is the standard maximum number of characters that should be included on one line, we decided to add points for each line over this number, as these lines are improperly formatted. The score was calculated by taking the ratio of the lines over eighty characters to the total number of lines in the file and multiplying this fraction by the total possible 20 points. Thus, a code base having no lines over eighty characters will receive a zero on the metric.
  
II. Metric to Assess the Quality of Comments
	The second metric we developed measures the ratio of commented lines to uncommented lines of code and provides a score based on this ratio. Code bases with too many or too little comments relative to the number of source code lines will receive a high score on the metric, while code bases with a rational and informative amount of commented lines will receive a lower score on the metric. Good coding practice includes commented nearly every block of code so that users can interpret the code.*** Thus, not only the number of commented lines relative to uncommented lines is important, but also the fact that they occur at relatively balanced rates throughout the code, meaning that not all comments occur in one place in the code.
In order to ensure that the commented lines and uncommented lines occurred at appropriate rates throughout the code, we implemented a stack. This would make sure that code bases with all comments at the very beginning or very end of the file would not score well on this metric, as this is poor coding practice. Every time a line was encountered that began a comment, a dummy variable was pushed to the stack. Each time a line was encountered that was not commented, a dummy variable was popped off the stack. If the stack was empty, meaning that there is more uncommented lines than commented, the metric score for the file was incremented. Thus, a piece of source code containing many lines in a row without a corresponding comment would have a high metric score. In addition, if the stack becomes too large, meaning that there are 10 more commented lines than uncommented lines in a row in the file, the score is incremented by .05. Thus, a piece of source code containing many commented lines in a row without any corresponding uncommented lines would have a high metric score as well.
***too many or too few***

III. Metric to Assess the Length of Main File
	The fourth metric we developed pertains to the length of the main file in regards to the average function size of the project.
	As lines of code from the file are read in, two counter variables to represent the number of lines of code in main and in all other files are incremented accordingly.
  
IV. Metric to Assess Repetition Control Statements
	The fourth metric we developed tests the redundancy of control statements within function blocks. In good coding practice, specific control statements such as for loop and while loops are not repeated multiple times in the same block of code, so we added points every time this occurred. If no control statements are repeated within the same code block, then the source code will receive a 0 on the metric. However, code bases containing no control statements will also score a perfect 0, even though this may not be good coding practice, since their function blocks will also not exhibit any instances of repetition.
	As lines of code are read in from the code base, they are each sent to a findRepition member function which determines whether repetition of control statements has occurred within the same block of code. This is done with the use of a stack object, which holds all lines of code within a particular function block. If the line of code contains a “{“, the line of code is pushed to the stack. If the stack is already not empty, a line of code passed to the function will also be added to the stack. When a “}” character is reached, the stack is emptied. In the process of emptying the stack, each line of code is added to a string vector, which is checked with each subsequent addition to ensure that no repetition exists. If a line of code is popped off the stack and it already exists in the string vector, a counter variable will be incremented to represent an additional instance of repetition if the line is found to be a control statement.
  
V. Metric to Assess the Number of Instances of Identifier Names
	The fifth metric we developed ***. As the code base is initially read into the hash table of files and lines of code, variable names are parsed out. This is done through a member function of grader called variableParse which receives a line of code and parses out the variable name, if the line contains one. During read-in, any line containing an equals sign will be sent to the variable parser, as it may be a variable declaration. In addition, any line containing only one space, not beginning with “#,” and not containing an equals sign will also be sent to the variable parser function. This will catch variable declarations such as “int x;” in the code base. Inside the variable parser function, the line of code is checked to ensure that it is not a control statement or a return statement, as these would not contain relevant variable declarations. The line is then checked to ensure it does not contain a period, as this would indicate an object calling a function rather than a variable declaration. If the line passes these conditions, it is sent to another member function which will return the second word of the string without any following punctuation, since this will be the name of the variable declared. For instance, the function would return “x” if given “int x;” and would return “name” if given “string name=”bee keeper;”, as this would be the second word and variable name in both circumstances.
**scoring and usage**

VI. Bonus Metric to Assess Existence of Control Statements
	The sixth metric we developed measures the number of existing control statements in a project. Since more complex code will contain more control statements, points are subtracted as more control statements are found in the source code. However, a simple file may be properly formatted and well-written without using any control statements, so points are not added to the score if few control statements are used. Instead, points are only subtracted if a large number of control statements are implemented in the project, as this is a sign of more complex code.

Analysis
I. Source Code
II. Source Code
III. Source Code


OUTPUT

Final Project Verbose Output

General
•	___ (name of code base)
•	Overall Score: /100, _________
•	The code base contained ___ files.

Metrics
I. Metric to Assess the Length of Each Line of Code
•	Metric I Score: ___/20
•	Good coding standards propose that no lines be longer than eighty characters. This code base contained ___ lines over eighty characters out of its total ___ lines. 
•	The score represents the ratio of the lines over eighty characters to the total number of lines in the file and multiplying this fraction by the total possible 20 points. 
•	Below a detailed report of the number of lines over eighty characters in each file is displayed.
o	File ___ received a ___/20.
o	The file contained ___ lines over eighty characters out of its total ___ lines.
II. Metric to Assess the Quality of Comments
•	Metric II Score: ___/20
o	___ commented with ___ comments (too many/few).
o	The project contained ___ lines of commented code and ___ lines of uncommented code.
•	Properly formatted source code contains an informative number of comments to help other programmers better understand the code. A score of ___ represents a ___ well commented source code. 
•	Below a detailed report of the scores for each file is displayed.
o	File ___ received a ___/20.
o	The source code is ___ commented, with ___ comments (too many/few).
o	The file contained ___ lines of commented code and ___ lines of uncommented code.
•	***NOT DISPLAYED***
o	Well: 0-6
♣	This source code exhibited an informative number of comments for useful interpretation of the code.
o	Too Many -- Poorly: 13-20
♣	This source code either exhibited much too many comments for useful interpretation of the code.
o	Too Many -- Moderately-well: 7-12
♣	This source code either exhibited slightly too many comment for useful interpretation of the code.
o	Too Few -- Poorly: 13-20
♣	This source code either exhibited much too few comments for useful interpretation of the code.
o	Too Few -- Moderately-well: 7-12
♣	This source code either exhibited slightly too few comments for useful interpretation of the code.
 III. Metric to Assess the Length of Main File Relative to Average Function Size
•	Metric III Score: ___/20
•	In good coding practice, the main.cpp file should be a relatively concise file which utilizes additional classes to perform most of the logic of the program.
IV. Metric to Assess Repetition Control Statements within Code Blocks
•	Metric IV Score: ___/20
•	In good coding practice, specific control statements such as for loop and while loops are not repeated multiple times in the same block of code. This code base exhibited ___ instances of control statement repetition within code blocks.
•	Below a detailed report of the scores for each file is displayed.
o	File ___ received a ___/20.
o	This file exhibited ___ instances of control statement repetition within code blocks.
•	The following lines of code were repeated within the same function block:
o	___ in the ___ file
V. Metric to Assess the Number of Instances of Identifier Names
•	Metric V Score: ___/20
•	In good coding practice, declared variables are used at least once and preferably several times in the project. There were ___ variables declared and not utilized in the code base, and ___ variables declared and utilized fewer than three times in the code base.
•	Below a detailed report of the scores for each file is displayed.
o	File ___ received a ___/20.
o	___ variables that were declared and not utilized in the code base.
o	___ variables that were declared and utilized fewer than three times in the code base.
VI. Bonus Metric to Assess Existence of Control Statements	
•	Metric VI Score: ___/-5
o	This code base exhibited ___ instances of control statements.
o	This code base exhibits ___ complexity.
•	Since more complex code will contain more control statements, this metric subtracts points as more control statements are found in the source code as a means of giving especially complex code bases lower scores than equally well-formatted code bases of simpler complexity.
•	Below a detailed report of the scores for each file is displayed.
o	File ___ received a ___/-5.
•	***NOT DISPLAYED***
o	Very High: -5
♣	This source code exhibited a very high level of complexity with a large number of control statements for the ***.
o	High: -4
♣	This source code exhibited a high level of complexity with a large number of control statements for the ***.
o	Moderately High: -3
♣	This source code exhibited a moderately high level of complexity with a large number of control statements for the ***.
o	Moderate: -2
♣	This source code exhibited a moderate level of complexity with a large number of control statements for the ***.
o	: -1
♣	This source code exhibited a *** level of complexity with a large number of control statements for the ***.


