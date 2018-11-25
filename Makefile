CXX=clang++
CXXFLAGS=-std=c++11 -Wall -Wextra -Wshadow
LATEX=xelatex

all: output.pdf clean
	@echo "Finished!"

convert-text: convert_text.cpp
	@echo "Compiling converter..."
	@$(CXX) convert_text.cpp -o convert_text $(CXXFLAGS)

output.pdf: input.txt convert-text
	@echo "Creating tex file..."
	@./convert_text
	@echo "Creating pdf, it can take up to 2 minutes..."
	@$(LATEX) -halt-on-error converted.tex > log
	@mv converted.pdf output.pdf

clean:
	@echo "Cleaning up..."
	@$(RM) converted* log convert_text

update: clean
	rm output.pdf
	git pull
