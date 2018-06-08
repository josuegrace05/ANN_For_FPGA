compileTrain:
	gcc -o perceptron_training perceptron_training.c -Wall -g

compileTest:
	gcc -o perceptron_testing perceptron_testing.c -Wall -g

Train:
	./perceptron_training > trainingResult.dat

Test:
	./perceptron_testing > testResult.dat
 
debugTest:
	valgrind --leak-check=full ./perceptron_testing
