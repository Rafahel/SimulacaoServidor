#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Aluno.h"
#include <iomanip>

using namespace std;

/// MOSTRA A CRIAÇÃO DE ALUNOS EM TEMPO REAL
#define DEBUG 0 // 0 inativo 1 ativo

/// PERMITE CRIAÇÃO DE ALUNOS SEM UTILIZAR ALEATORIEDADE (APENAS PARA TESTES)
#define CONTROLE 0 // 0 inativo 1 ativo


/// FUNCAO QUE GERA OS VALORES ALETORIOS NECESSÁRIOS
int random(int min, int max){

    return min + (rand() % (max - min + 1));
}

/// FUNÇÃO QUE PERMITE CRIAÇÃO DE ALUNOS SEM UTILIZAR ALEATORIEDADE
vector<Aluno> inicializacaoControlada(){
    vector<Aluno> alunos;
    Aluno aluno1(1, 6, -1, 9);
    alunos.push_back(aluno1);
    Aluno aluno2(2, 24, -1, 7);
    alunos.push_back(aluno2);
    Aluno aluno3(3, 26, -1, 9);
    alunos.push_back(aluno3);
    Aluno aluno4(4, 35, -1, 7);
    alunos.push_back(aluno4);
    Aluno aluno5(5, 44, -1, 10);
    alunos.push_back(aluno5);
    Aluno aluno6(6, 52, -1, 6);
    alunos.push_back(aluno6);
    Aluno aluno7(7, 58, -1, 6);
    alunos.push_back(aluno7);
    Aluno aluno8(8, 70, -1, 5);
    alunos.push_back(aluno8);
    Aluno aluno9(9, 77, -1, 9);
    alunos.push_back(aluno9);
    Aluno aluno10(10, 89, -1, 7); //89
    alunos.push_back(aluno10);

    return alunos;

}



int main() {

    srand(time(NULL));
    vector<Aluno> alunos;

    bool livre = true;
    int tempoOcupacao = 0;
    int alunosNoSistema = 0;
    int chegada = 0;
    int numeroDeAlunos = random(10, 100);
    int execucao = 0;
    int atendimentoTotal = 0;
    /// Inicializa os alunos no sistema
    if (!CONTROLE){
        for (int i = 0; i < numeroDeAlunos; ++i){
            execucao = random(1, 15);
            atendimentoTotal += execucao;
            chegada += random(1, 10);
            Aluno aluno(i+1, chegada, -1, execucao);
            alunos.push_back(aluno);
            if(DEBUG)
                cout << "DEBUG --> Aluno: " << alunos[i].getId() << " Tempo de Chegada: " << alunos[i].getChegada() << " Tempo Execucao: " << alunos[i].getExecucao() << endl;
        }
    } else{
        alunos = inicializacaoControlada();
    }
    Aluno aluno(0,0,0,0);
    int contador = 1;
    int pos = 0;
    int posAtual = 0;
    int filaTotal = 0;
    string status = "Livre";

    /// PARTE RESPOSÁVEL POR MOSTRAR A VISÃO DO PROFESSOR
    cout << endl << endl << "     ---------------------------------------- PROFESSOR ----------------------------------------" << endl << endl;
    cout << "Tempo de evento   Aluno   Tipo de Evento   Estado do Professor      Tempo de Ocupacao   Alunos no sistema" << endl; // Retirando tempo de entrada, tempo na fila
    cout << "       0             0         Inicio             Livre                    0                    0" << endl;
    while(1){
        if(alunos[pos].getChegada() == contador){
            alunosNoSistema++;
            status = "Ocupado";
            cout << "       " << contador << "           " << alunos[pos].getId() << "         "  << "Chegada";
            cout << "            " << status << "                   "<< tempoOcupacao << "                   " <<  alunosNoSistema  << endl;
            livre = false;
            if(pos < alunos.size() - 1){
                pos++;
            }
        }
        if(pos >= alunos.size() - 1)
            livre = false;
        if(alunos[posAtual].getExecucao() > 0 && !livre){
            if(alunos[posAtual].getEntrada() == -1){
                alunos[posAtual].setEntrada(contador);
                alunos[posAtual].setTempoFila(alunos[posAtual].getEntrada() - alunos[posAtual].getChegada());
                if(alunos[posAtual].getTempoFila() < 0){
                    alunos[posAtual].setTempoFila(0);
                }
            }
            alunos[posAtual].executa();
            tempoOcupacao += 1;
            status = "Ocupado";
//            cout<< "ID: " << alunos[posAtual].getId()  << "  exec: " << alunos[pos].getExecucao() << endl;
        }
        if(alunos[posAtual].getExecucao() <= 0 && !livre){
            alunosNoSistema--;
            if(posAtual + 1 < alunos.size() - 1){
                if(alunos[posAtual + 1].getChegada() >= contador){
                    status = "Livre";
                }
            }
            if(posAtual == alunos.size() - 1)
                status = "Livre";
            cout << left << "       " << contador + 1 << "           " << alunos[posAtual].getId() << "         "  << " Saida ";
            cout << "            " << status <<"                      " << tempoOcupacao << "                   " <<  alunosNoSistema  << endl;
            filaTotal += alunos[posAtual].getTempoFila();
            alunos[posAtual].setSaida(contador + 1);
            posAtual++;
            livre = true;
        }
        contador++;
        if(posAtual >= alunos.size())
            break;
    }

    /// SOMA DE MÉDIAS.
    double tempoMedioFila = filaTotal / alunos.size();
    double tempoMedioExecucao = atendimentoTotal / alunos.size();

    /// PARTE RESPOSÁVEL POR MOSTRAR A VISÃO DO ALUNO
    cout << endl << endl << "     ---------------------------------------- ALUNO ----------------------------------------" << endl << endl;
    cout << "Aluno   Tempo de chegada   Tempo de entrada   Tempo de saida   Tempo de fila   Tempo de atendimento" << endl;
    for (int i = 0; i < alunos.size() ; ++i) {

        cout << "   " << alunos[i].getId() << "          " << alunos[i].getChegada() << "                  " << alunos[i].getEntrada() <<
             "                 " << alunos[i].getSaida() << "                " << alunos[i].getTempoFila()<< "                 " << alunos[i].getExecucaoOriginal() << endl;
    }

    /// FIM DE EXECUÇÃO E AMOSTRAGEM DE MÉDIAS.
    cout << fixed;
    cout << setprecision(2);
    cout << endl << "Tempo medio de fila: " << tempoMedioFila << endl;
    cout << "Tempo medio de atendimento: " << tempoMedioExecucao << endl << endl;
    cin.get();
    return 0;
}






