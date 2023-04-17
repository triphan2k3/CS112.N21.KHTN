def TowerOfHanoi(n , source, destination, auxiliary):
    if n == 1:
        print ("Move disk 1 from ", source, "to ", destination)
        return 
    TowerOfHanoi(n - 1, source, auxiliary, destination)
    print ("Move disk", n,"from ", source, "to ", destination)
    TowerOfHanoi(n - 1, auxiliary, destination, source)
         
n = int(input())
TowerOfHanoi(n,'A','B','C')