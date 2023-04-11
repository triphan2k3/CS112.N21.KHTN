Week1:
	rm -f ./Assignment/Week1/main
	g++ -Wl,-z,stack-size=1073741824 -o main ./Assignment/Week1/main.cpp
	./Assignment/Week1/main
Week4:
	cd Assignment/Week4/RELAX; \
	rm -f generate; \
	rm -f generate.exe; \
	rm -f RELAX; \
	rm -f RELAX.exe; \
	g++ -o RELAX RELAX.cpp; \
	g++ -o generate generate.cpp; \
	./generate; \
	cd ../MODULO; \
	rm -f generate; \
	rm -f generate.exe; \
	rm -f MODULO; \
	rm -f MODULO.exe; \
	g++ -o MODULO MODULO.cpp; \
	g++ -o generate generate.cpp; \
	./generate