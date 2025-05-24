import numpy as np
import matplotlib.pyplot as plt

frequencies_1 = np.array([100, 70, 40, 20, 17, 14, 12, 10, 7, 4, 2, 1])
gain_1 = np.array([0.34, 0.34, 0.26, -0.09, -0.35, -0.92, -1.62, -2.85, -6.94, -15.39, -27.97, -40])
frequencies_2 = np.array([100, 70, 40, 20, 17, 14, 12, 11, 10.5, 10, 9.5, 9, 8.5, 8, 7, 4, 2, 1])
gain_2 = np.array([0.59, 0.67, 0.59, 2.67, 3.81, 6.32, 10.6, 14.58, 18.12, 20.55, 16.53, 11.73, 8.27, 5.15, -0.26, -14.42, -27.96, -40])



plt.figure(figsize=(10, 6))
plt.semilogx(
    frequencies_1, 
    gain_1, 
    'ro-',           # Czerwone kółka z linią ciągłą
    label='Pomiar 1 (Q = 0.707)',
    linewidth=2,
    markersize=8
)
plt.semilogx(
    frequencies_2, 
    gain_2, 
    'bo-',           # Niebieska linia kreskowana
    label='Pomiar 2 (Q = 10)',
    linewidth=2,
    markersize=8
)

# Opisy osi i legenda
plt.xlabel('Częstotliwość [kHz]', fontsize=12)
plt.ylabel('Wzmocnienie [20*log|K_u|]', fontsize=12)
plt.title('Filtry górnoprzepustowe', fontsize=14)
plt.grid(True, which="both", linestyle="--", alpha=0.6)
plt.legend(fontsize=10)

# Linia pomocnicza dla -3 dB
# plt.axhline(y=-3, color='gray', linestyle=':', linewidth=1)
# plt.text(10, -2.5, 'f₃dB', fontsize=10)

#plt.gca().invert_xaxis()  # Odwraca kierunek osi X


plt.show()