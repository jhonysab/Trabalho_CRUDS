import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class ContatoDAO {
    private static final String FILE_PATH = "contatos.csv";
    private static final String SEPARATOR = ",";

    public List<Contato> listarTodos() {
        List<Contato> contatos = new ArrayList<>();
        try (BufferedReader br = new BufferedReader(new FileReader(FILE_PATH))) {
            String linha;
            while ((linha = br.readLine()) != null) {
                String[] dados = linha.split(SEPARATOR);
                if (dados.length == 3) { 
                    contatos.add(new Contato(dados[0], dados[1], dados[2]));
                }
            }
        } catch (FileNotFoundException e) {
            // Arquivo ainda não existe, retorna lista vazia
        } catch (IOException e) {
            e.printStackTrace();
        }
        return contatos;
    }

    public void salvarTodos(List<Contato> contatos) {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(FILE_PATH))) {
            for (Contato contato : contatos) {
                String linha = contato.getNome() + SEPARATOR + contato.getTelefone() + SEPARATOR + contato.getProfissao();
                bw.write(linha);
                bw.newLine();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
