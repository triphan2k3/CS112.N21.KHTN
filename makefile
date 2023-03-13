MergeSort:
	rm -f ./Merge\ Sort\ parallel/main
	g++ -Wl,-z,stack-size=1073741824 -o ./Merge\ Sort\ parallel/main ./Merge\ Sort\ parallel/main.cpp
	./Merge\ Sort\ parallel/main