import os
import matplotlib.pyplot as plt

# Pasta onde estão os arquivos de tempo
tempo_dir = "tempo"

# Lista todos os arquivos .txt na pasta tempo
arquivos = [f for f in os.listdir(tempo_dir) if f.endswith('.txt')]

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
    plt.figure(figsize=(8, 5))
    plt.plot(iteracoes, tempos, marker='o')
    plt.xlabel('Número de Iterações')
    plt.ylabel('Tempo de Execução (s)')
    plt.title(f'Tempo de Execução - {arquivo.replace(".txt", "")}')
    plt.grid(True)
    plt.tight_layout()
    plt.show()