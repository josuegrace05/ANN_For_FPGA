compiletrain:
	gcc -o perceptron_training perceptron_training.c -Wall -g

compiletest:
	gcc -o perceptron_testing perceptron_testing.c -Wall -g

train:
	./perceptron_training

test:
	./perceptron_testing
 
debugtest:
	valgrind --leak-check=full ./perceptron_testing
	
debugtrain:
	valgrind --leak-check=full ./perceptron_training
