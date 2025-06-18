install:
	clang++ bfortune.cpp -o bf -std=c++17
	cp bf ~/.local/bin/bfortune
	chmod +x ~/.local/bin/bfortune
