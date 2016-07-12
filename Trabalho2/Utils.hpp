#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>

std::string exec(const std::string cmd);

void cat(const std::string filename);

std::string readwhole(const std::string filename);

std::vector<std::string> ls(std::string path);

std::vector<std::string> split(const std::string& str, const std::string& delim);

void replace_chars(std::string& str, const std::string& to_replace, const char by = ' ');

bool valid_word(std::string& str);

std::vector<std::string> listOfWords(std::string str);

template < class ContainerT >
void tokenize(const std::string& str, ContainerT& tokens,
			  const std::string& delimiters = " ", bool trimEmpty = true) {
	std::string::size_type pos, lastPos = 0;

	using value_type = typename ContainerT::value_type;
	using size_type  = typename ContainerT::size_type;

	while (true) {
		pos = str.find_first_of(delimiters, lastPos);
		if(pos == std::string::npos) {
			pos = str.length();

			if(pos != lastPos || !trimEmpty)
				tokens.push_back(value_type(str.data()+lastPos,
								(size_type)pos-lastPos ));

			break;
		} else {
			if(pos != lastPos || !trimEmpty)
				tokens.push_back(value_type(str.data()+lastPos,
								(size_type)pos-lastPos ));
		}

		lastPos = pos + 1;
   }
}

#endif  // UTILS_HPP