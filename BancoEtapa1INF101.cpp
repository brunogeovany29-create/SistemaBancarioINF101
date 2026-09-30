/*Trabalho – Implementação de um Sistema de
Bruno Geovany S. P. Marques 
Registro e Gestão de Contas Bancarias  */
#include <iostream>
#include <string>
#define TAM_MAX 5 /*Uma forma não tão elegante de declara uma constante global*/

void exibir() { /* Essa funcao concentra o que vai ser exibido na tela, a escolha do tipo void() e porque ela nao tem obrigacao de return*/
  std::cout << std::endl;
  std::cout << "********************************" << std::endl;
  std::cout << "**      BANCO SPICA INF10     **" << std::endl;
  std::cout << "********************************" << std::endl;

  std::cout << "(1) Cadastrar conta." << std::endl;
  std::cout << "(2) Consultar conta." << std::endl;
  std::cout << "(3) Verificar saldo." << std::endl;
  std::cout << "(4) Alterar tipo da conta." << std::endl;
  std::cout << "(5) Ativar/Desativar conta." << std::endl;
  std::cout << "(6) Sair." << std::endl;
  std::cout << "Escolha uma opcao: ";
}
enum Escolher {CADASTRAR = 1,CONSULTAR = 2,VERIFICAR = 3,ALTERAR = 4,ATIVAR = 5,SAIR = 6}; /*Utilizei o enum para facilitar na hora de econtrar as opcoes, ja que da para procura pelo nome e nao o valor*/
void menu() {
  
  /*As variaveis utilizadas, devem ser inicializadas antes de serem usadas, entao coloquei no inicio e com valores padronizados*/
  int numeroConta[TAM_MAX], tipoConta[TAM_MAX], limiteConta = 0;
  int opcao = 0;
  std::string nomeCliente[TAM_MAX], cpfConta[TAM_MAX];
  double saldoConta[TAM_MAX];
  bool contaAtiva[TAM_MAX];
    
  do { /*inicio do laço, a função exibir() abaixo é para fica exibindo novamente as opcoes*/
    exibir(); /*Chama a mensagem padronizada em exibir*/

    if (!(std::cin >> opcao)) { /* Se o usuario digitar algo que nao seja numero, limpa o erro */
      std::cin.ignore();
      std::cin.clear(); /*Uma observaçao se o usuario digita uma letra o programa entra em um loop infinito,*/
      opcao = 0; /*nao foi solicitado que esse problema fosse resolvido, mas  creio que a saida seria utilizar o Try-Catch ou #include<limits>.*/
    }

    switch (opcao) { /*Inicia-se o switch respeitando o que foi definido no Enum*/
      case CADASTRAR:
        
       if (limiteConta < 5) { /*Cria ate 5 contas*/
        int numero;
        std::cout << "Digite o numero da conta: ";
        std::cin >> numero;
        std::cin.ignore();

        if (numero <= 0) { /*Estabelece que o valor da conta sendo menor ou igual a zero da erro*/
          std::cerr << "O numero da conta tem que ser maior que 0" << std::endl; /*O uso do cerr ao invés do cout, para mensagens de erro é o padrão*/
          break;}
        std::string nome;
        std::cout << "Digite o nome do titular: ";
        std::getline(std::cin, nome); /*A funcao getline é utilizada para capitura a string e ignora os espaços em branco entre os nomes*/
        /*O interessante de usar cpf como string, é que no caso de int cpf por exemplo se eu colocasse 001 ele iria me retorna 1 desconsidera os 0 a esquerda*/
        std::string cpf;
        std::cout << "Digite o cpf do titular: "; 
        std::getline(std::cin, cpf);
        int tipo;
        std::cout << "Escolha o tipo de conta (1)Corrente (2)Poupanca: ";
        std::cin >> tipo;
        while (tipo != 1 && tipo != 2) { /*Laço enquanto o numero recebido não se enquadram 1 e 2*/
        std::cout << "Tipo invalido! Digite 1 ou 2: ";
        std::cin >> tipo;}
        double saldo;
        std::cout << "Digite o seu saldo: ";
        std::cin >> saldo;

        if (saldo >= 0) { /*Estabelece tem que ser maior ou igual a 0*/
          contaAtiva[limiteConta] = true;
          std::cout << "Conta criada com sucesso!" << std::endl;
          numeroConta[limiteConta] = numero;
          nomeCliente[limiteConta] = nome;
          cpfConta[limiteConta] = cpf;
          tipoConta[limiteConta] = tipo;
          saldoConta[limiteConta] = saldo;
          limiteConta = limiteConta + 1;
        } else {
          std::cerr << "O saldo nao pode ser negativo." << std::endl;}
        }
        else{std::cout << "Limite de criacao de contas foi atingido";
        break;}
        break;
      /*Obseracao no case CONSULTAR, VERIFICAR, ATIVAR e ALTERAR, utiluzou-se {},
      pois essa era a condição para adicionar novas variaves
      dentro do bloco, se retirar as chaves ele para de funcionar*/    
      case CONSULTAR:{ 
        int numBusca;
        std::cout << "\nDigite o numero da conta: ";
        std::cin >> numBusca;
        bool encontrada = false;
        for (int i = 0; i < limiteConta; i++) { /*Realiza a busca no vetor*/
          if (numeroConta[i] == numBusca) { 
            encontrada = true; /*Caso a conta exista, retorna os valores abaixo*/
          std::cout << "Numero da conta: " << numeroConta[i] << std::endl;
          std::cout << "Nome do cliente: " << nomeCliente[i] << std::endl;
          std::cout << "CPF do cliente: " << cpfConta[i] << std::endl;
          std::cout << "Tipo de conta: " << (tipoConta[i] == 1 ? "Corrente" : "Poupanca") << std::endl;
          std::cout << "Saldo conta: " << saldoConta[i] << std::endl;        
          std::cout << "Situacao: " << (contaAtiva[i] ? "Ativa" : "Desativada") << std::endl; /*Aqui eu tenho um operador ternário para verifica se esta ativa ou nao*/
          std::cin.get();
        break;}}
        if (!encontrada) {
         std::cerr << "Conta nao encontrada.\n"; /*Mensagem de erro*/
        }                                                                 /*a escolha foi feita para evitar fica poluindo o programa com mais if e else*/
        break;
      } 
      case VERIFICAR:{
        int numBusca;
        std::cout << "\nDigite o numero da conta: ";
        std::cin >> numBusca;
        bool encontrada = false;
        for (int i = 0; i < limiteConta; i++) {
          if (numeroConta[i] == numBusca) {
            encontrada = true;
            if (contaAtiva[i] == false) { /*Verifica se a conta esta desativa, se for verdade ela impede a exibição do saldo*/
              std::cerr << "Sua conta esta inativa, funcao desativada" << std::endl;
              break;
            }
            std::cout << "Saldo em conta: " << saldoConta[i] << std::endl;
            std::cin.ignore();
            std::cin.get();
            break;
          }
        }
        if (!encontrada) {
          std::cout << "Conta nao encontrada.\n";
        }
        break;}

      case ALTERAR:{
        int numBusca;
        std::cout << "\nDigite o numero da conta: ";
        std::cin >> numBusca;
        bool encontrada = false;
        for (int i = 0; i < limiteConta; i++) { /*Realiza a busca no vetor*/
          if (numeroConta[i] == numBusca) {
            encontrada = true;
            if (contaAtiva[i] == false) { /*Conta desativada nao pode ser alterada*/
              std::cerr << "Sua conta esta inativa, funcao desativada" << std::endl;
              break;
            }
            std::cout << "Alterar tipo de conta" << std::endl;
            std::cout << "Tipo de conta: " << (tipoConta[i] == 1 ? "Corrente" : "Poupanca") << std::endl;
            std::cout << "Novo tipo (1)Corrente ou (2)Poupanca: ";
            std::cin >> tipoConta[i];
            while (tipoConta[i] != 1 && tipoConta[i] != 2) { /*Repete ate receber 1 ou 2*/
              std::cerr << "Tipo invalido! Digite 1 ou 2: ";
              std::cin >> tipoConta[i];
            }
            std::cout << "Tipo de conta alterada com sucesso!" << std::endl;
            break;
          }
        }
        if (!encontrada) {
          std::cerr << "Conta nao encontrada.\n";
        }
        break;
      }

      case ATIVAR:{
        int numBusca;
        std::cout << "\nDigite o numero da conta: ";
        std::cin >> numBusca;
        bool encontrada = false;
        for (int i = 0; i < limiteConta; i++) { /*Realiza a busca no vetor*/
          if (numeroConta[i] == numBusca) {
            encontrada = true;
            std::cout << "Ativar/Desativar conta" << std::endl;
            if (contaAtiva[i]) { /*Se estava ativa, desativa; senao, ativa*/
              contaAtiva[i] = false;
              std::cout << "Sua conta foi desativada com sucesso!" << std::endl;
            } else {
              contaAtiva[i] = true;
              std::cout << "Sua conta foi ativada com sucesso!" << std::endl;
            }
            break;
          }
        }
        if (!encontrada) {
          std::cerr << "Conta nao encontrada.\n";
        }
        break;
      }

      case SAIR:
        std::cout << "Encerrando o programa..." << std::endl; /*Sai do programa*/
        break;
      
        default:
        std::cout << "Nenhuma das opcoes" << std::endl;}/*Caso o usuario digite algo fora do estabelecido o default é acionado*/
  } while (opcao != SAIR); /*Literalmente utilizando o Enum para decidir se sai ou nao do laço*/
}

int main() {
  menu();
  return 0;
}