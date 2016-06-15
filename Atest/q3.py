#!/usr/bin/env python

import os
import sys

def prime(limit=0):
	primes = [2, 3]
	for i in primes:
		if i > limit:
			return
		yield i

	def is_prime(test):
		sqrt = int(test ** 0.5)
		isprime = True
		for i in primes:
			#only the numbers less than sqrt(number) need to be checked 
			if i > sqrt:
				break
			if test % i == 0:
				isprime = False
				break
		return isprime

	t = 0
	while True:
		#fast way to check primes
		t += 6
		for x in [t-1, t+1]:
			if x > limit:
				return	
			if is_prime(x):
				primes.append(x)
				yield x

if __name__ == '__main__':
	number = raw_input("Please input a positive number: ")
	if number.isdigit() and int(number) > 0:
		print "All prime numbers between 1 and %d are:"%int(number)
		for i in prime(int(number)):
			print i
	else:
		print "Your input is not a Positive Number!"

