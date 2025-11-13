import numpy as np
import matplotlib.pyplot as plt

# Valores de x
x = np.linspace(-3, 5000, 500)

# 1. Função Gaussiana
sigma = 1
gaussian = np.exp(-x**2 / (2 * sigma**2))

# 2. Laplaciana de Gaussiana (LoG)
log = (1 - (x**2 / sigma**2)) * np.exp(-x**2 / (2 * sigma**2))

# 3. Cosseno ao quadrado (janela Hann-like)
L = 5000
cosine_squared = np.cos(np.pi * x / (2 * L))**2
cosine_squared[np.abs(x) > L] = 0  # fora do suporte

# 4. Exponencial (Laplace)
b = 1
laplace = np.exp(-np.abs(x) / b)

# 5. Epanechnikov kernel
epanechnikov = 0.75 * (1 - x**2)
epanechnikov[np.abs(x) > 1] = 0  # suporte limitado

# Plot
plt.figure(figsize=(12, 6))
#plt.plot(x, gaussian, label='Gaussiana', linewidth=2)
#plt.plot(x, log, label='Laplaciana de Gaussiana', linestyle='--')
plt.plot(x, cosine_squared, label='Cosseno² (Hann)', linestyle=':')
#plt.plot(x, laplace, label='Exponencial (Laplace)', linestyle='-.')
#plt.plot(x, epanechnikov, label='Epanechnikov', linestyle='dashdot')

plt.title("Comparação de Funções Semelhantes à Gaussiana")
plt.xlabel("x")
plt.ylabel("Valor da função")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()
