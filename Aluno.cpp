//
// Created by Rafahel on 12/03/2017.
//
#include "Aluno.h"

Aluno::Aluno(int id, int chegada, int entrada,  int execucao) : id(id), chegada(chegada), entrada(entrada), execucao(execucao), execucaoOriginal(execucao) {}

void Aluno::setExecucao(int execucao) {
    Aluno::execucao = execucao;
}

void Aluno::setEntrada(int entrada){
    Aluno::entrada = entrada;
}

int Aluno::getId(){
    return id;
}

int Aluno::getChegada(){
    return chegada;
}

int Aluno::getExecucao(){
    return execucao;
}

void Aluno::executa(){
 Aluno:execucao--;
}

int Aluno::getEntrada() const {
    return entrada;
}

int Aluno::getTempoFila() const {
    return tempoFila;
}

void Aluno::setTempoFila(int tempoFila) {
    Aluno::tempoFila = tempoFila;
}

int Aluno::getExecucaoOriginal() const {
    return execucaoOriginal;
}

int Aluno::getSaida() const {
    return saida;
}

void Aluno::setSaida(int saida) {
    Aluno::saida = saida;
}

