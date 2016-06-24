/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

/**
 *
 * State class definition:
 *  Essa classe define a estrutura de dados Estado
 *  contém informação necessária para a contrução da
 *  máquina de estados. Estados tem referência para os
 *  estados que podem ser atingidos através de transições.
 *
 **/

#ifndef STATE_HPP
#define STATE_HPP

#include <map>
#include <string>
#include <vector>

class RState;

class State {
 public:
    /*
     * Construtor de estado, padrão: 
     * (label epslon, sem rejeição, não inicial, não final)
     */
    State(const std::string& = "&", RState* const = nullptr,
          bool = false, bool = false);

    /* Getter para o label do estado. */
    std::string get_label() const;

    /* Verifica se estado é inicial */
    bool is_initial() const;

    /* Verifica se estado é final */
    bool is_final() const;

    bool is_dead() const;

    /* Verifica se estado é de rejeição */
    virtual bool is_rejector() const;

    /* Setter para o label do estado. */
    void set_label(const std::string&);

    /* Verifica se estado aceita a entrada fornecida.
     * i.e., se existe transição com dada entrada,
     * ignorando as transições para o estado de rejeição.
     */
    bool accepts(const char) const;

    /* Cria uma nova transição ou redefine uma já existente. */
    void add_transition(const char, const std::vector<State*>&);

    /* Acesso a uma transição existente. */
    std::vector<State*>& operator[](const char);

    /* Acesso const a uma transição existente. */
    const std::vector<State*>& operator[](const char) const;

    operator std::string() const;

 private:
    /* Label do estado */
    std::string label;

    /* Mapa de transições */
    std::map<char, std::vector<State*>> transitions;
    
    /* Estado de rejeição. */
    RState* rejection_state;

    /* Identifica se estado é inicial.
     * True se inicial, false caso contrário.
     */
    bool initial;
    
    /* Identifica se estado é final.
     * True se final, false caso contrário.
     */
    bool final;
};

std::ostream& operator<<(std::ostream&, const State&);

/*
 * TODO: documentação
 */
class RState : public State {
 public:
    /*
     * TODO: documentação
     */
    RState();

    /*
     * TODO: documentação
     */
    bool is_rejector() const;
};

#endif /* STATE_HPP */
