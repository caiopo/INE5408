#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <set>

/**
 * @brief      Executa um comando shell e retorna o resultado
 *
 * @param[in]  cmd   Comando
 *
 * @return     Resultado
 */
std::string exec(const std::string cmd);

/**
 * @brief      Le um arquivo inteiro e retorna seu conteudo
 *
 * @param[in]  filename  Nome do arquivo
 *
 * @return     Conteudo do arquivo lido
 */
std::string readwhole(const std::string filename);

/**
 * @brief      Lista os arquivo em um diretorio
 *
 * @param[in]  path  Caminho do diretorio
 *
 * @return     Lista de arquivos no diretorio
 */
std::vector<std::string> ls(std::string path);

/**
 * @brief      Separa a string nos delimitadores
 *
 * @param[in]  str    String
 * @param[in]  delim  Delimitadores
 *
 * @return     Vetor de string separadas
 */
std::vector<std::string> split(const std::string& str, const std::string& delim);

/**
 * @brief      Substitui todos os caracteres em str iguais a algum caractere em
 *             to_replace por by
 *
 * @param      str         A string
 * @param[in]  to_replace  O que substituir
 * @param[in]  by          Substituto
 */
void replace_chars(std::string& str, const std::string& to_replace, const char by = ' ');

/**
 * @brief      Testa se str é uma palavra valida
 *
 * @param      str   String a ser testada
 *
 * @return     Se str é valida
 */
bool valid_word(std::string& str);

/**
 * @brief      Sanitiza a str de caracteres especiais e retorna todas as suas
 *             palavras
 *
 * @param[in]  str   String a ser sanitizada
 *
 * @return     Lista de palavras em str
 */
std::set<std::string> listOfWords(std::string str);

/**
 * @brief      Coloca todos os tokens da string str no container tokens
 *
 * @param[in]  str         The string
 * @param      tokens      The tokens
 * @param[in]  delimiters  The delimiters
 * @param[in]  trimEmpty   The trim empty
 *
 * @tparam     ContainerT  Tipo de container
 */
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