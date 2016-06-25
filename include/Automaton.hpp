/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

/**
 *
 * Automaton class definition:
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
#include <vector>
#include <algorithm>

class Automaton {
 public:
 	/* Construtor vazio da máquina de estados */
 	Automaton(); 
    
 	/* Construtor passando alfabeto como parâmetro */
    Automaton(const std::set<char>&);
    
    /* Método para inserção de estado na máquina: label, inicial, final */
    void insert(const std::string&, bool = false, bool = false);

    /* Método para criar uma transição de from por label para to: from, label, to */
    void make_transition(const std::string&, const char, const std::string&);

 	/* Remove os estados que não levam ao estado final */
    void remove_dead_states();
    
    /* Remove os estados inalcansáveis a partir do estado inicial */
    void remove_unreachable_states();

    /* Troca os estados finais e não finais
     * Faz o complemento do autômato
     * NF -> F
     * F -> NF
     */
    Automaton complement();

    /* Cria um novo estado inicial que tem as mesmas 
     * transições dos estados iniciais das duas máquinas
     * e devolve uma nova máquina com esta característica
     */
    Automaton union_operation(const Automaton&);

    Automaton automaton_intersection(const Automaton&);

    /* Executa o algoritmo de minimização de autômato finito */
    Automaton minimize();

    /* Transforma o autômato numa tabela, para impressão em terminal/console */
    operator std::string() const;

    std::vector<std::string>& operator()(const std::string&, const char);

    const std::vector<std::string>& operator()(const std::string&, const char) const;

    std::vector<std::vector<std::string>> to_table();

 private:
    class State;

 	/* Um mapa de nome para estado, contendo todos os estados do autômato */
    std::map<std::string, State> states;

    /* O alfabeto da máquina de estados (sigma) */
    std::set<char> alphabet;

    /* O nome do estado inicial */
    std::string initial_state;

    /* Um conjunto dos nomes dos estados finais */ 
    std::set<std::string> final_states;

    std::set<std::string> labels;

    std::string rejection_state;

    bool is_dead(const State&) const;
};

class Automaton::State {
 public:
    /*
     * Construtor de estado, padrão: 
     * (label epslon, sem rejeição, não inicial, não final)
     */
    State(bool = false, bool = false);

    /* Verifica se estado é inicial */
    bool is_initial() const;

    /* Verifica se estado é final */
    bool is_final() const;

    /* Verifica se estado aceita a entrada fornecida.
     * i.e., se existe transição com dada entrada,
     * ignorando as transições para o estado de rejeição.
     */
    bool accepts(const char) const;

    void append_transition(const char, const std::string&);

    std::map<char,std::vector<std::string>>::iterator begin();

    std::map<char,std::vector<std::string>>::iterator end();

    std::map<char,std::vector<std::string>>::const_iterator begin() const;

    std::map<char,std::vector<std::string>>::const_iterator end() const;

    /* Acesso a uma transição existente. */
    std::vector<std::string>& operator[](const char);

    /* Acesso const a uma transição existente. */
    const std::vector<std::string>& operator[](const char) const;

    operator std::string() const;

 private:
    /* Label do estado */
    std::string label;

    /* Mapa de transições */
    std::map<char, std::vector<std::string>> transitions;

    /* Identifica se estado é inicial.
     * True se inicial, false caso contrário.
     */
    bool initial;
    
    /* Identifica se estado é final.
     * True se final, false caso contrário.
     */
    bool final;
};

#endif /* FS_MACHINE_HPP */
