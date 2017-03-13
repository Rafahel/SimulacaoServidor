//
// Created by Rafahel on 12/03/2017.
//

#ifndef SIMULACAOSERVIDOR_ALUNO_H
#define SIMULACAOSERVIDOR_ALUNO_H

class Aluno{
    private:
        int id;
        int chegada;
        int entrada;
        int tempoFila;
        int execucao;
        int execucaoOriginal;
        int saida;
public:
    Aluno(int id, int chegada, int entrada, int execucao);

    void setExecucao(int execucao);

    void setEntrada(int entrada);

    void executa();

    int getId();

    int getChegada();

    int getExecucao();

    int getExecucaoOriginal() const;

    int getSaida() const;

    void setSaida(int saida);

    int getTempoFila() const;

    void setTempoFila(int tempoFila);

    int getEntrada() const;

};

#endif //SIMULACAOSERVIDOR_ALUNO_H
