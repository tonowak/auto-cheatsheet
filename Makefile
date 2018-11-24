CXX=clang++
CXXFLAGS=-std=c++11 -Wall -Wextra -Wshadow
LATEX=xelatex

all: output.pdf clean
	@echo "Finished"

convert-text: convert_text.cpp
	@echo "Compiling converter"
	@$(CXX) convert_text.cpp -o convert_text $(CXXFLAGS)

output.pdf: input.txt convert-text
	@./convert_text
	@echo "Creating pdf, it can take a while"
	@$(LATEX) converted.tex > log
	@mv converted.pdf output.pdf

clean:
	@$(RM) converted* log convert_text

install:
	sudo apt-get install -y texlive-xetex texlive-lang-polish

update: clean
	rm output.pdf
	git pull
