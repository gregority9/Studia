import numpy as np
import matplotlib.pyplot as plt

frequencies_1 = np.array([0.1, 0.2, 0.4, 0.7, 1, 2, 4, 7, 8, 9, 10, 12, 14, 17, 20, 40, 70, 100])
gain_1 = np.array([0.09, 0.09, 0.09, 0.09, 0.09, 0.09, 0.00, -0.82, -1.31, -2.05, -2.97, -4.88, -6.94, -9.9, -12.4, -26.02, -33.9, -40])
frequencies_2 = np.array([1, 2, 4, 7, 7.5, 8, 8.5, 9, 9.5, 10, 10.5, 11, 12, 14, 17, 20, 40, 70, 100])
gain_2 = np.array([0.17, 0.42, 1.66, 5.76, 7.04, 8.63, 10.66, 13.39, 17.06, 19.94, 17.09, 12.85, 7.08, 0.51, -5.35, -9.37, -24.44, -33.98, -40])



plt.figure(figsize=(10, 6))
plt.semilogx(
    frequencies_1, 
    gain_1, 
    'ro-',           # Czerwone kółka z linią ciągłą
    label='(Pomiar 1 (Q = 0.707))',
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
plt.title('Filtry dolnoprzepustowy', fontsize=14)
plt.grid(True, which="both", linestyle="--", alpha=0.6)
plt.legend(fontsize=10)

# Linia pomocnicza dla -3 dB
# plt.axhline(y=-3, color='gray', linestyle=':', linewidth=1)
# plt.text(10, -2.5, 'f₃dB', fontsize=10)


plt.show()