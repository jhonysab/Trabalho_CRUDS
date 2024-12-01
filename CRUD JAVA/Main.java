import java.util.List;
import java.util.Scanner;

public class Main {
    private static final Scanner scanner = new Scanner(System.in);
    private static final ContatoService contatoService = new ContatoService();

    public static void main(String[] args) {
        while (true) {
            exibirMenu();
            String opcao = scanner.nextLine();

            try {
                switch (opcao) {
                    case "1":
                        adicionarContato();
                        break;
                    case "2":
                        listarContatos();
                        break;
                    case "3":
                        removerContato();
                        break;
                    case "4":
                        modificarContato();
                        break;
                    case "5":
                        System.out.println("Saindo do programa...");
                        return;
                    default:
                        System.out.println("Opção inválida! Tente novamente.");
                }
            } catch (Exception e) {
                System.out.println("Erro: " + e.getMessage());
            }
        }
    }

    private static void exibirMenu() {
        System.out.println("\n--- Agenda de Contatos ---");
        System.out.println("1. Adicionar Contato");
        System.out.println("2. Listar Contatos");
        System.out.println("3. Remover Contato");
        System.out.println("4. Modificar Contato");
        System.out.println("5. Sair");
        System.out.print("Escolha uma opção: ");
    }

    private static void adicionarContato() {
        System.out.print("Digite o nome: ");
        String nome = scanner.nextLine();
        System.out.print("Digite o telefone: ");
        String telefone = scanner.nextLine();
        System.out.print("Digite a profissão: ");
        String profissao = scanner.nextLine();

        Contato contato = new Contato(nome, telefone, profissao);
        contatoService.adicionarContato(contato);
        System.out.println("Contato adicionado com sucesso!");
    }

    private static void listarContatos() {
        List<Contato> contatos = contatoService.listarContatos();
        if (contatos.isEmpty()) {
            System.out.println("Nenhum contato cadastrado.");
        } else {
            for (int i = 0; i < contatos.size(); i++) {
                System.out.println((i + 1) + ". " + contatos.get(i));
            }
        }
    }

    private static void removerContato() {
        listarContatos();
        System.out.print("Digite o número do contato a ser removido: ");
        int index = Integer.parseInt(scanner.nextLine()) - 1;
        contatoService.removerContato(index);
        System.out.println("Contato removido com sucesso!");
    }

    private static void modificarContato() {
        listarContatos();
        System.out.print("Digite o número do contato a ser modificado: ");
        int index = Integer.parseInt(scanner.nextLine()) - 1;

        System.out.print("Novo nome: ");
        String nome = scanner.nextLine();
        System.out.print("Novo telefone: ");
        String telefone = scanner.nextLine();
        System.out.print("Nova profissão: ");
        String profissao = scanner.nextLine();

        Contato novoContato = new Contato(nome, telefone, profissao);
        contatoService.atualizarContato(index, novoContato);
        System.out.println("Contato atualizado com sucesso!");
    }
}
