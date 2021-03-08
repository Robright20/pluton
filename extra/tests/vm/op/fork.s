	.name "tester"
	.comment "test fork"


	ld %10, r3
	st r3, 57
	fork %64

	#this will created the same process at the same place
