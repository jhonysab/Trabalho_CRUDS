import java.util.List;

public class ContatoService {
    private final ContatoDAO contatoDAO;

    public ContatoService() {
        this.contatoDAO = new ContatoDAO();
    }

    public List<Contato> listarContatos() {
        return contatoDAO.listarTodos();
    }

    public void adicionarContato(Contato contato) {
        List<Contato> contatos = contatoDAO.listarTodos();
        contatos.add(contato);
        contatoDAO.salvarTodos(contatos);
    }

    public void removerContato(int index) {
        List<Contato> contatos = contatoDAO.listarTodos();
        if (index >= 0 && index < contatos.size()) {
            contatos.remove(index);
            contatoDAO.salvarTodos(contatos);
        } else {
            throw new IllegalArgumentException("Índice inválido");
        }
    }

    public void atualizarContato(int index, Contato novoContato) {
        List<Contato> contatos = contatoDAO.listarTodos();
        if (index >= 0 && index < contatos.size()) {
            contatos.set(index, novoContato);
            contatoDAO.salvarTodos(contatos);
        } else {
            throw new IllegalArgumentException("Índice inválido");
        }
    }
}
