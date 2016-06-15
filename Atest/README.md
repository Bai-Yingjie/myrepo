#Rules
Thank you for your time taking this test, the ground rules behind the test :
* Please state all assumptions you make.
* You may choose any language (C, Java, etc.) you feel most comfortable with
* Once I send the test, you’ll have up to 4 hours to send me back the results
* It is fine to use an editor, paper, etc.  If you take the test on paper, take pictures of the papers and send them back to me.  If you use an editor, zip up the file and send it back to ensure it doesn’t get stripped out by any email virus checking software
* You must only submit files that you have completely written yourself.
* No one will be available for questions or clarifications.  If you do have a question, state your assumptions on why you chose the implementation you provided in your answer. 
* The programming test is ARM's copyright and confidential to ARM - please do not publish or distribute it.

#Questions and answers

Quiz 1 – Provide algorithm about how to make a sandwich, no need to write code.
Quiz 2 – Point out all errors found from that code snippet. 
Quiz 3 – Not only provide source code files but also list compile/build environment.

##Question 1:
Write an algorithm for how to make a sandwich.

Answered by Bai Yingjie to Q1:
Pre-condition: We will make a jam sandwich.
We have a jar of jam with the lid removed, 
a knife able to fit in the jam jar,
a plate on the table,
and two slices of bread, removed from their packaging.

1. Place slices of bread on plate, side by side.
2. Pick up knife by handle
3. Use knife to remove jam from jar
4. Use Knife with jam to spread jam on one slice of bread.
5. Put down knife
6. Pick up the other slice of bread
7. Place slice being held on top of other slice so slices edges align

Post-condition: Sandwich is ready to eat.

##Question 2:
The following code written in C has a number of issues with it.  Please document all errors that you find.

```
struct sensor_struct
{
	int status;
	uint8 value;
};

read_sensor(struct sensor_struct sensor)
{
	while (!sensor->status);
	{
		if (sensor->value < 0)
	    	sensor->value += 1024;
	    return sensor->value;
	}
}
```

Answered by Bai Yingjie to Q2:
bugs:
* 1024 exceeds uint8, and could be < 0, so value in sensor_struct_t should be int
* read_sensor doesn't have return type
* input parameter should be a pointer, otherwise it is a dead loop
* while() checks a status change, so volatile is needed to avoid compiler optimization
* The read_sensor function should not alter the sensor value, let somewhere else do it

corrected version:
```
typedef volatile struct sensor_struct
{
	int status;
	int value;
} sensor_struct_t;

int read_sensor( (sensor_struct_t *) sensor_p )
{
	int temp_val;
	assert(sensor_p != NULL);

	/*wait for status*/
	while (!sensor_p->status);

	temp_val = sensor_p->value;

	if (temp_val < 0)
	{
		temp_val += 1024;
	}

	return temp_val;
}
```


##Question 3:
Write a program in the language of your choice that prompts the user for a number and calculates all prime numbers between 1 and that number.  The program must compile and generate accurate results.  Please comment the code as well to indicate the logic behind your code.  Also, please provide the compiler and OS details to help with program compilation for verification of your answer.  Your code should handle all error conditions that might occur. 

Answered by Bai Yingjie to Q3:
cd path/to/this/dir
python q3.py 

Run this program, it will print result and exit; If your input is not a positive number, it will print a message and exit.

Language: python 2.7.6
OS: linux mint 17 x86_64 GNU/Linux
Linux kernel: 3.16.2



