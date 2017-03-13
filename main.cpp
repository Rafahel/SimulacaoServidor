#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Aluno.h"
#include <iomanip>

using namespace std;

#define DEBUG 0 // 0 inativo 1 ativo
#define SHOWLOG 1 // 0 inativo 1 ativo

int random(int min, int max){

    return min + (rand() % (max - min + 1));
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
    for (int i = 0; i < numeroDeAlunos; ++i){
        execucao = random(1, 15);
        atendimentoTotal += execucao;
        chegada += random(1, 10);
        Aluno aluno(i+1, chegada, -1, execucao);
        alunos.push_back(aluno);
        if(DEBUG)
            cout << "DEBUG --> Aluno: " << alunos[i].getId() << " Tempo de Chegada: " << alunos[i].getChegada() << " Tempo Execucao: " << alunos[i].getExecucao() << endl;
    }
    Aluno aluno(0,0,0,0);

//    Aluno aluno1(1, 6, -1, 9);
//    alunos.push_back(aluno1);
//    Aluno aluno2(2, 24, -1, 7);
//    alunos.push_back(aluno2);
//    Aluno aluno3(3, 26, -1, 9);
//    alunos.push_back(aluno3);
//    Aluno aluno4(4, 35, -1, 7);
//    alunos.push_back(aluno4);
//    Aluno aluno5(5, 44, -1, 10);
//    alunos.push_back(aluno5);
//    Aluno aluno6(6, 52, -1, 6);
//    alunos.push_back(aluno6);
//    Aluno aluno7(7, 58, -1, 6);
//    alunos.push_back(aluno7);
//    Aluno aluno8(8, 70, -1, 5);
//    alunos.push_back(aluno8);
//    Aluno aluno9(9, 77, -1, 9);
//    alunos.push_back(aluno9);
//    Aluno aluno10(10, 89, -1, 7); //89
//    alunos.push_back(aluno10);

    int contador = 1;
    int pos = 0;
    int posAtual = 0;
    int filaTotal = 0;
    string status = "Livre";
    cout << "Tempo de evento   Aluno   Tipo de Evento   Estado do Professor   Tempo de entrada   Tempo na fila   Tempo de Ocupacao   Alunos no sistema" << endl;
    cout << "       0           0         Inicio             Livre                  -                  -               0                    0" << endl;
    while(1){
        if(alunos[pos].getChegada() == contador){
            alunosNoSistema++;
            status = "Ocupado";
            cout << "       " << contador << "           " << alunos[pos].getId() << "         "  << "Chegada";
            cout << "            " << status << "                " << "--" << "                  " << "--" << "                   "<< tempoOcupacao << "                   " <<  alunosNoSistema  << endl;
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
            cout << "       " << contador + 1 << "           " << alunos[posAtual].getId() << "         "  << "Saida";
            cout << "            " << status << "                 " << alunos[posAtual].getEntrada() << "                  "  << alunos[posAtual].getTempoFila() << "                  " << tempoOcupacao << "                   " <<  alunosNoSistema  << endl;
            filaTotal += alunos[posAtual].getTempoFila();
            alunos[posAtual].setSaida(contador + 1);
            posAtual++;
            livre = true;
        }
        contador++;
        if(posAtual >= alunos.size())
            break;
    }
    double tempoMedioFila = filaTotal / alunos.size();
    double tempoMedioExecucao = atendimentoTotal / alunos.size();
    cout << fixed;
    cout << setprecision(2);
    cout << "Tempo medio de fila: " << tempoMedioFila << endl;
    cout << "Tempo medio de atendimento: " << tempoMedioExecucao << endl << endl;
    if(SHOWLOG){
        cout << "---------------------------------------- LOG ----------------------------------------" << endl << endl;
        for (int i = 0; i < alunos.size() ; ++i) {
            cout << "ID: " <<alunos[i].getId() << endl;
            cout << "Tempo de chegada: " <<alunos[i].getChegada() << endl;
            cout << "Tempo de execucao: " <<alunos[i].getExecucaoOriginal() << endl;
            cout << "Tempo de saida: " <<alunos[i].getSaida() << endl;
            cout << "Tempo de fila: " <<alunos[i].getTempoFila() << endl;
            cout << "________________________________"<< endl << endl;
        }
    }
    system("pause");
    return 0;
}






