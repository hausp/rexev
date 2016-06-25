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

#include "types.hpp"

class Automaton {
 public:
 	/* Construtor vazio da máquina de estados */
 	Automaton(); 
    
 	/* Construtor passando alfabeto como parâmetro */
    Automaton(const Alphabet&);

    void set_name(const std::string&);

    std::string get_name() const;

    bool is_minimum() const;
    
    /* Método para inserção de estado na máquina: label, inicial, final */
    void insert(const Key&, bool = false, bool = false);

    /* Método para criar uma transição de from por label para to: from, label, to */
    void make_transition(const Key&, const Entry, const Key&);

 	/* Remove os estados que não levam ao estado final */
    void remove_dead_states();
    
    /* Remove os estados inalcansáveis a partir do estado inicial */
    void remove_unreachable_states();

    /* Remove os estados equivalentes */
    void remove_equivalent_states();

    /* Troca os estados finais e não finais
     * Faz o complemento do autômato
     * NF -> F
     * F -> NF
     */
    Automaton complement() const;

    Automaton automaton_intersection(const Automaton&) const;

    /* Cria um novo estado inicial que tem as mesmas 
     * transições dos estados iniciais das duas máquinas
     * e devolve uma nova máquina com esta característica
     */
    Automaton union_operation(const Automaton&) const;

    /* Executa o algoritmo de minimização de autômato finito */
    Automaton minimize() const;

    /* Mostra as transições de erro */
    void set_error_transitions();

    /* Esconde as transições de erro */
    void hide_error_transitions();

    TransitionVector& operator()(const Key&, const Entry);

    const TransitionVector& operator()(const Key&, const Entry) const;

    std::vector<std::vector<std::string>> to_table() const;

 private:
    class State;

 	// Um mapa de nome para estado, contendo todos os estados do autômato
    std::map<Key, State> states;

    // O alfabeto da máquina de estados (sigma)
    Alphabet alphabet;

    // O nome do estado inicial
    Key k_initial;

    // Um conjunto dos nomes dos estados finais
    KeySet k_acceptors;

    // Conjunto de nomes dos estados
    KeySet keys;

    // O nome do estado de rejeição
    Key k_error;

    // O nome do autômato
    std::string name;

    // Identifica se autômato já é mínimo
    bool minimum;

    KeySet difference(const KeySet&, const KeySet&) const;

    KeySet intersection(const KeySet&, const KeySet&) const;

    KeySet predecessors_of(const KeySet&, const Entry) const;

    KeySet predecessors_of(const Key&, const Entry) const;

    void update_states(const PartitionSet&);
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

    void set_initial(bool);

    /* Verifica se estado aceita a entrada fornecida.
     * i.e., se existe transição com dada entrada,
     * ignorando as transições para o estado de rejeição.
     */
    bool accepts(const Entry) const;

    bool accepts_to(const Entry, const Key&) const;

    void append_transition(const Entry, const Key&);

    std::map<Entry,TransitionVector>::iterator begin();

    std::map<Entry,TransitionVector>::iterator end();

    std::map<Entry,TransitionVector>::const_iterator begin() const;

    std::map<Entry,TransitionVector>::const_iterator end() const;

    /* Acesso a uma transição existente. */
    TransitionVector& operator[](const Entry);

    /* Acesso const a uma transição existente. */
    const TransitionVector& operator[](const Entry) const;

 private:
    /* Mapa de transições */
    std::map<char, TransitionVector> transitions;

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
