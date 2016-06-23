/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

/**
 *
 * FSMachine class definition:
 *  Esta classe define um autômato de estados finitos,
 *	o reconhecedor para uma expressão, gramática ou
 *	linguagem regular.
 *  Estão aqui implementadas as operações sobre autômatos,
 *	união, complemento, remoção de estados mortos e inalcansáveis,
 *	além do algoritmo de minimização e a operação de igualdade.
 **/

#ifndef FS_MACHINE_HPP
#define FS_MACHINE_HPP

#include <map>
#include <set>
#include <string>
#include <utility>

#include "State.hpp"

class FSMachine {
 public:
 	/* Construtor vazio da máquina de estados */
 	FSMachine(); 
    
 	/* Construtor passando alfabeto como parâmetro */
    FSMachine(const std::set<char>&);

    // Formal Definition
    // Transitions exist inside States
    // Finite State Set, Input Alphabet, Initial State, Final States Set 
    //FSMachine(const std::map<char,State>&, const std::set<char>&, char, const std::set<char>&);
    
    /* Método para inserção de estado na máquina: label, inicial, final */
    void insert(const std::string&, bool = false, bool = false);

    /* Método para criar uma transição de from por label para to: from, label, to */
    void make_transition(const std::string&, const char, const std::string&);

    /* Acesso ao estado identificado pela string passada como parâmetro */
    State& operator[](const std::string&);
    const State& operator[](const std::string&) const; 

 	/* Remove os estados que não levam ao estado final */
    void remove_dead_states(); 
    
    /* Remove os estados inalcansáveis a partir do estado inicial */
    void remove_unreachable_states();

    /* Troca os estados finais e não finais
     * Faz o complemento do autômato
     * NF -> F
     * F -> NF
     */
    FSMachine complement();

    /* Cria um novo estado inicial que tem as mesmas 
     * transições dos estados iniciais das duas máquinas
     * e devolve uma nova máquina com esta característica
     */
    FSMachine union_operation(const FSMachine&);

    /* Executa o algoritmo de minimização de autômato finito */
    FSMachine minimize();

    /* Transforma o autômato numa tabela, para impressão em terminal/console */
    operator std::string() const;

    std::vector<std::vector<std::string>> to_table();

 private:

 	/* Um mapa de nome para estado, contendo todos os estados do autômato */
    std::map<std::string, State> states;

    /* O alfabeto da máquina de estados (sigma) */
    std::set<char> alphabet;

    /* O nome do estado inicial */
    std::string initial_state;

    /* Um conjunto dos nomes dos estados finais */ 
    std::set<std::string> final_states;

    /*  Estado de rejeição */
    RState rejection_state;
};

#endif /* FS_MACHINE_HPP */
