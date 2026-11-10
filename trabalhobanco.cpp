#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main() {
    // ---------- Dados das contas ----------
    const int MAX_CONTAS = 100;
    int numeroConta[MAX_CONTAS];
    string nomeCliente[MAX_CONTAS];
    string cpf[MAX_CONTAS];
    int tipoConta[MAX_CONTAS];
    double saldo[MAX_CONTAS];
    bool contaAtiva[MAX_CONTAS];
    int quantidadeContas = 0;

    // ---------- Histórico de movimentações ----------
    const int MAX_MOVIMENTACOES = 500;
    int contaMovimentacao[MAX_MOVIMENTACOES];
    char tipoMovimentacao[MAX_MOVIMENTACOES];
    double valorMovimentacao[MAX_MOVIMENTACOES];
    int quantidadeMovimentacoes = 0;

    int opcao;
    cout << fixed << setprecision(2);

    do {
        cout << "\n********************************\n";
        cout << "**        BANCO INF101        **\n";
        cout << "********************************\n";
        cout << "1 - Cadastrar conta\n";
        cout << "2 - Listar contas\n";
        cout << "3 - Consultar conta\n";
        cout << "4 - Depositar\n";
        cout << "5 - Sacar\n";
        cout << "6 - Transferir\n";
        cout << "7 - Extrato\n";
        cout << "0 - Sair\n";
        cout << "Escolha: ";
        cin >> opcao;

        switch (opcao) {

        // ---------------- 1 - CADASTRAR ----------------
        case 1: {
            if (quantidadeContas >= MAX_CONTAS) {
                cout << "Limite de contas atingido!\n";
                break;
            }
            int num, tipo;
            string nome, cpfLido;
            double saldoInicial;

            cout << "Numero da conta: ";
            cin >> num;
            if (num <= 0) {
                cout << "Numero deve ser maior que zero!\n";
                break;
            }
            // Não permite número de conta repetido
            bool repetido = false;
            for (int i = 0; i < quantidadeContas; i++) {
                if (numeroConta[i] == num) repetido = true;
            }
            if (repetido) {
                cout << "Ja existe uma conta com esse numero!\n";
                break;
            }
            cout << "Nome do titular: ";
            cin.ignore();
            getline(cin, nome);
            cout << "CPF: ";
            getline(cin, cpfLido);
            cout << "Tipo da conta (1 = Corrente, 2 = Poupanca): ";
            cin >> tipo;
            if (tipo != 1 && tipo != 2) {
                cout << "Tipo invalido!\n";
                break;
            }
            cout << "Saldo inicial: R$ ";
            cin >> saldoInicial;
            if (saldoInicial < 0) {
                cout << "Saldo inicial nao pode ser negativo!\n";
                break;
            }

            numeroConta[quantidadeContas] = num;
            nomeCliente[quantidadeContas] = nome;
            cpf[quantidadeContas] = cpfLido;
            tipoConta[quantidadeContas] = tipo;
            saldo[quantidadeContas] = saldoInicial;
            contaAtiva[quantidadeContas] = true;
            quantidadeContas++;
            cout << "Conta cadastrada com sucesso!\n";
            break;
        }

        // ---------------- 2 - LISTAR ----------------
        case 2: {
            if (quantidadeContas == 0) {
                cout << "Nenhuma conta cadastrada.\n";
                break;
            }
            cout << "\n--- Contas cadastradas ---\n";
            for (int i = 0; i < quantidadeContas; i++) {
                cout << "Conta " << numeroConta[i]
                     << " | " << nomeCliente[i]
                     << " | " << (tipoConta[i] == 1 ? "Corrente" : "Poupanca")
                     << " | Saldo: R$ " << saldo[i]
                     << " | " << (contaAtiva[i] ? "Ativa" : "Inativa") << endl;
            }
            break;
        }

        // ---------------- 3 - CONSULTAR ----------------
        case 3: {
            int num, indice = -1;
            cout << "Numero da conta: ";
            cin >> num;
            for (int i = 0; i < quantidadeContas; i++) {
                if (numeroConta[i] == num) indice = i;
            }
            if (indice == -1) {
                cout << "Conta nao encontrada!\n";
                break;
            }
            cout << "\nConta: " << numeroConta[indice] << endl;
            cout << "Titular: " << nomeCliente[indice] << endl;
            cout << "CPF: " << cpf[indice] << endl;
            cout << "Tipo: " << (tipoConta[indice] == 1 ? "Corrente" : "Poupanca") << endl;
            cout << "Saldo: R$ " << saldo[indice] << endl;
            cout << "Situacao: " << (contaAtiva[indice] ? "Ativa" : "Inativa") << endl;
            break;
        }

        // ---------------- 4 - DEPOSITAR ----------------
        case 4: {
            int num, indice = -1;
            double valor;
            cout << "Numero da conta: ";
            cin >> num;
            for (int i = 0; i < quantidadeContas; i++) {
                if (numeroConta[i] == num) indice = i;
            }
            if (indice == -1) {
                cout << "Conta nao encontrada!\n";
                break;
            }
            if (!contaAtiva[indice]) {
                cout << "Conta inativa!\n";
                break;
            }
            if (quantidadeMovimentacoes >= MAX_MOVIMENTACOES) {
                cout << "Historico de movimentacoes cheio!\n";
                break;
            }
            cout << "Valor do deposito: R$ ";
            cin >> valor;
            if (valor <= 0) {
                cout << "Valor deve ser positivo!\n";
                break;
            }
            saldo[indice] = saldo[indice] + valor;
            contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indice];
            tipoMovimentacao[quantidadeMovimentacoes] = 'D';
            valorMovimentacao[quantidadeMovimentacoes] = valor;
            quantidadeMovimentacoes++;
            cout << "Deposito realizado! Novo saldo: R$ " << saldo[indice] << endl;
            break;
        }

        // ---------------- 5 - SACAR ----------------
        case 5: {
            int num, indice = -1;
            double valor;
            cout << "Numero da conta: ";
            cin >> num;
            for (int i = 0; i < quantidadeContas; i++) {
                if (numeroConta[i] == num) indice = i;
            }
            if (indice == -1) {
                cout << "Conta nao encontrada!\n";
                break;
            }
            if (!contaAtiva[indice]) {
                cout << "Conta inativa!\n";
                break;
            }
            if (quantidadeMovimentacoes >= MAX_MOVIMENTACOES) {
                cout << "Historico de movimentacoes cheio!\n";
                break;
            }
            cout << "Valor do saque: R$ ";
            cin >> valor;
            if (valor <= 0) {
                cout << "Valor deve ser positivo!\n";
                break;
            }
            if (valor > saldo[indice]) {
                cout << "Saldo insuficiente!\n";
                break;
            }
            saldo[indice] = saldo[indice] - valor;
            contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indice];
            tipoMovimentacao[quantidadeMovimentacoes] = 'S';
            valorMovimentacao[quantidadeMovimentacoes] = valor;
            quantidadeMovimentacoes++;
            cout << "Saque realizado! Novo saldo: R$ " << saldo[indice] << endl;
            break;
        }

        // ---------------- 6 - TRANSFERIR ----------------
        case 6: {
            int numOrigem, numDestino, indiceOrigem = -1, indiceDestino = -1;
            double valor;
            cout << "Conta de origem: ";
            cin >> numOrigem;
            cout << "Conta de destino: ";
            cin >> numDestino;
            for (int i = 0; i < quantidadeContas; i++) {
                if (numeroConta[i] == numOrigem) indiceOrigem = i;
                if (numeroConta[i] == numDestino) indiceDestino = i;
            }
            if (indiceOrigem == -1 || indiceDestino == -1) {
                cout << "Uma das contas nao foi encontrada!\n";
                break;
            }
            if (indiceOrigem == indiceDestino) {
                cout << "Origem e destino devem ser contas diferentes!\n";
                break;
            }
            if (!contaAtiva[indiceOrigem] || !contaAtiva[indiceDestino]) {
                cout << "Ambas as contas precisam estar ativas!\n";
                break;
            }
            // Garante espaço para os DOIS registros
            if (quantidadeMovimentacoes + 2 > MAX_MOVIMENTACOES) {
                cout << "Historico sem espaco para a transferencia!\n";
                break;
            }
            cout << "Valor da transferencia: R$ ";
            cin >> valor;
            if (valor <= 0) {
                cout << "Valor deve ser positivo!\n";
                break;
            }
            if (valor > saldo[indiceOrigem]) {
                cout << "Saldo insuficiente na conta de origem!\n";
                break;
            }
            saldo[indiceOrigem] = saldo[indiceOrigem] - valor;
            saldo[indiceDestino] = saldo[indiceDestino] + valor;

            // Registro 1: saída da origem
            contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indiceOrigem];
            tipoMovimentacao[quantidadeMovimentacoes] = 'S';
            valorMovimentacao[quantidadeMovimentacoes] = valor;
            quantidadeMovimentacoes++;
            // Registro 2: entrada no destino
            contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indiceDestino];
            tipoMovimentacao[quantidadeMovimentacoes] = 'D';
            valorMovimentacao[quantidadeMovimentacoes] = valor;
            quantidadeMovimentacoes++;

            cout << "Transferencia realizada com sucesso!\n";
            break;
        }

        // ---------------- 7 - EXTRATO ----------------
        case 7: {
            int num, indice = -1;
            cout << "Numero da conta: ";
            cin >> num;
            for (int i = 0; i < quantidadeContas; i++) {
                if (numeroConta[i] == num) indice = i;
            }
            if (indice == -1) {
                cout << "Conta nao encontrada!\n";
                break;
            }
            cout << "\n--- Extrato da conta " << num << " (" << nomeCliente[indice] << ") ---\n";
            bool temMov = false;
            for (int i = 0; i < quantidadeMovimentacoes; i++) {
                if (contaMovimentacao[i] == num) {
                    temMov = true;
                    if (tipoMovimentacao[i] == 'D') {
                        cout << "Deposito: R$ " << valorMovimentacao[i] << endl;
                    } else if (tipoMovimentacao[i] == 'S') {
                        cout << "Saque: R$ " << valorMovimentacao[i] << endl;
                    }
                }
            }
            if (!temMov) cout << "Sem movimentacoes.\n";
            cout << "Saldo atual: R$ " << saldo[indice] << endl;
            break;
        }

        case 0:
            cout << "Encerrando o sistema...\n";
            break;

        default:
            cout << "Opcao invalida!\n";
        }

    } while (opcao != 0);

    return 0;
}
