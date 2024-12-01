public class Contato {
    private String nome;
    private String telefone;
    private String profissao;

    public Contato(String nome, String telefone, String profissao) {
        this.nome = nome;
        this.telefone = telefone;
        this.profissao = profissao;
    }

    public String getNome() { return nome; }
    public void setNome(String nome) { this.nome = nome; }

    public String getTelefone() { return telefone; }
    public void setTelefone(String telefone) { this.telefone = telefone; }

    public String getProfissao() { return profissao; }
    public void setProfissao(String profissao) { this.profissao = profissao; }

    @Override
    public String toString() {
        return "Nome: " + nome + ", Telefone: " + telefone + ", Profissão: " + profissao;
    }
}
