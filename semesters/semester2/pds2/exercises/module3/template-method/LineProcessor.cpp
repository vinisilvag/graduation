#include <regex>
#include <math.h>
#include <string>
#include <vector>
#include <sstream>

#include "LineProcessor.hpp"
#include <list>

// int LineProcessor::_numLinhas = 0;

void LinePrinter::processaLinha(const std::string &str) {
  std::cout << str << std::endl;
}

bool ContadorPopRural::linhaValida(const std::string &str) const {
  // Neste exemplo usaremos expressoes regulares para verificar se uma linha
  // eh valida ou nao.
  //
  // Esta expressao regular eh formada por cinco partes. Cada uma dessas
  // partes eh um dos tres tipos de padrao regular abaixo:
  //
  // \\w+ eh qualquer palavra com um ou mais digitos, letras e sublinhas (_)
  // \\s* eh qualquer sequencia de zero ou mais espacos (inclui tab)
  // \\d+ eh qualquer sequencia de um ou mais digitos
  std::regex regularExpr("\\w+\\s*\\d+\\s*\\d+");

  // A funcao regex_match vai retornar verdadeiro se a string str casa-se com
  // a expressao regular que acabamos de criar:
  return std::regex_match(str, regularExpr);
}

void ContadorPopRural::processaLinha(const std::string &str) {
  //
  // Em geral eh mais facil ler dados de uma string se a string eh transformada
  // em um objeto do tipo stringstream:
  std::stringstream ss(str);
  //
  // Iremos ler os dados da string nestas tres variaveis abaixo:
  std::string nomePais;
  unsigned populacao, percUrbana;
  //
  // Como sabemos que a linha contem string int int, podemos fazer a leitura
  // facilmente usando o operador de streaming:
  ss >> nomePais >> populacao >> percUrbana;
  //
  // Note que precisamos arredondar o valor que serah impresso. O arredondamento
  // serah feito via a funcao floor. Ou seja, decimais serao sempre
  // arredondados para baixo:
  unsigned popRural = floor(populacao - (populacao * (percUrbana/100.0)));
  //
  // Uma vez encontrados os valores que precisam ser impressos, seguimos o
  // modelo do enunciado do exercicio:
  std::cout << popRural << " pessoas vivem no campo no " << nomePais <<
    std::endl;
}

bool ContadorNumNaturais::linhaValida(const std::string &str) const {
  std::regex regularExpr("([0-9])+(\\s*([0-9])+)+?");

  return std::regex_match(str, regularExpr);
}

void ContadorNumNaturais::processaLinha(const std::string &str) {
  std::stringstream ss(str);
  int sum = 0, temp;

  while(ss >> temp) {
    sum += temp;
  }

  std::cout << sum << std::endl;
}

bool LeitorDeFutebol::linhaValida(const std::string &str) const {
  std::regex regularExpr("\\s*\\w+\\s*\\d+\\s*\\w+\\s*\\d+");

  return std::regex_match(str, regularExpr);
}

void LeitorDeFutebol::processaLinha(const std::string &str) {
  std::stringstream ss(str);

  std::string team_one, team_two;
  int score_one, score_two;

  ss >> team_one >> score_one >> team_two >> score_two;

  if(score_one > score_two) {
    std::cout << "Vencedor: " << team_one << std::endl;
  } else if(score_one < score_two) {
    std::cout << "Vencedor: " << team_two << std::endl;
  } else {
    std::cout << "Empate" << std::endl;
  }
}

void ContadorDePalavras::processaLinha(const std::string &str) {
  std::stringstream ss(str);

  int count = 0;
  std::string temp;

  while(ss >> temp) {
    count++;
  }

  std::cout << count << std::endl;
}

bool InversorDeFrases::linhaValida(const std::string &str) const {
  std::regex regularExpr("([A-Za-z])+(\\s*([A-Za-z])+)+?");

  return std::regex_match(str, regularExpr);
}

void InversorDeFrases::processaLinha(const std::string &str) {
  std::stringstream ss(str);
  std::string temp;

  std::list<std::string> aux;

  while (ss >> temp) {
    aux.push_front(temp);
  }

  for(auto it : aux) {
    std::cout << it << " ";
  }

  std::cout << std::endl;
}

bool EscritorDeDatas::linhaValida(const std::string &str) const {
  std::regex regularExpr("\\s*\\d\\d?/\\d\\d?/\\d{4}");

  return std::regex_match(str, regularExpr);
}

void EscritorDeDatas::processaLinha(const std::string &str) {
  std::stringstream ss(str);
  std::string temp;

  std::map<int, std::string> months = {
    {1, "Jan"},
    {2, "Fev"},
    {3, "Mar"},
    {4, "Abr"},
    {5, "Mai"},
    {6, "Jun"},
    {7, "Jul"},
    {8, "Ago"},
    {9, "Set"},
    {10, "Out"},
    {11, "Nov"},
    {12, "Dez"}
  };

  std::vector<int> out;

  while (std::getline(ss, temp, '/')) {
    out.push_back(std::stoi(temp));
  }

  std::cout << months[out[1]] << std::endl;
}
