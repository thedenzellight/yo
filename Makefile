CCC = g++

main:
	$(CCC) src/main.cpp -std=c++20 -lcpr -ljsoncpp -o yo

install:
	make
	sudo cp yo /usr/bin/yo

test:
	make
	./yo search visual-studio-code-bin
	./yo search whatdadogdoin
	./yo install air-bin
	@echo "Tests done!"
