import numpy as np
import matplotlib.pyplot as plt

# Dane wejściowe (teraz o tej samej długości)
frequencies_1 = np.array([6.2, 7.58, 8.53, 10, 11.9, 13.42, 16.53])  # 6 elementów
gain_1 = np.array([0.32, 0.5070,0.7169,  1.0140, 0.7169, 0.5070, 0.32])  # 6 elementów

frequencies_2 = np.array([9.287, 9.588, 9.781, 10, 10.29, 10.48, 10.84])  # 7 elementów
gain_2 = np.array([0.3131, 0.4960, 0.7, 0.9910, 0.7, 0.4960, 0.3131])  # 7 elementów

# Tworzenie wykresu
plt.figure(figsize=(12, 6))

# Wykres liniowy dla pierwszej serii
plt.plot(frequencies_1, gain_1, 
         'ro-',           # Czerwone kółka z linią ciągłą
         linewidth=2, 
         markersize=8, 
         label='Pomiar 1 (Q = 3)')

# Wykres liniowy dla drugiej serii
plt.plot(frequencies_2, gain_2, 
         'bo-',           # Niebieska linia kreskowana
         linewidth=2,
         markersize=8, 
         label='Pomiar 2 (Q = 20)')

# Konfiguracja wykresu
plt.title('Filtr środkowoprzepustowy', fontsize=14)
plt.xlabel('Częstotliwość [kHz]', fontsize=12)
plt.ylabel('Wzmocnienie [20 * log|K_u|]', fontsize=12)
plt.legend(fontsize=10)
plt.grid(True, linestyle='--', alpha=0.6)

# Dopasowanie zakresu osi
plt.xlim(min(min(frequencies_1), min(frequencies_2)) - 1, 
         max(max(frequencies_1), max(frequencies_2)) + 1)

plt.tight_layout()

plt.xticks(np.arange(6, 18, 1))  # Od 6 do 14 Hz, co 1 Hz

plt.show()