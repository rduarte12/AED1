import os
import matplotlib.pyplot as plt

# Pasta onde estão os arquivos de tempo
tempo_dir = "tempo"

# Lista todos os arquivos .txt na pasta tempo
arquivos = [f for f in os.listdir(tempo_dir) if f.endswith('.txt')]

plt.figure(figsize=(10, 6))
for arquivo in arquivos:
    caminho = os.path.join(tempo_dir, arquivo)
    iteracoes = []
    tempos = []
    with open(caminho, 'r') as f:
        for linha in f:
            partes = linha.strip().split(',')
            if len(partes) == 2:
                tempo = float(partes[0])
                iteracao = int(partes[1])
                tempos.append(tempo)
                iteracoes.append(iteracao)
    plt.plot(iteracoes, tempos, marker='o', label=arquivo.replace('.txt', ''))

plt.xlabel('Número de Iterações')
plt.ylabel('Tempo de Execução (s)')
plt.title('Comparação dos Algoritmos - Tempo de Execução')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()
