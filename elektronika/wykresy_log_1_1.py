import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import LogLocator, LogFormatter

# Dane wejściowe (przeliczone z dB na wartości liniowe)
frequencies = np.array([100, 70, 40, 20, 17, 14, 12, 10, 7, 4, 2, 1])
frequencies_2 = np.array([100, 70, 40, 20, 17, 14, 12, 11, 10.5, 10, 9.5, 9, 8.5, 8, 7, 4, 2, 1])
gain_linear_1 = 10**(np.array([0.34, 0.34, 0.26, -0.09, -0.35, -0.92, -1.62, -2.85, -6.94, -15.39, -27.97, -40])/20)
gain_linear_2 = 10**(np.array([0.59, 0.67, 0.59, 2.67, 3.81, 6.32, 10.6, 14.58, 18.12, 20.55, 16.53, 11.73, 8.27, 5.15, -0.26, -14.42, -27.96, -40])/20)

# Konfiguracja wykresu
fig, ax = plt.subplots(figsize=(12, 8))

# Wykres log-log
ax.loglog(frequencies[:len(gain_linear_1)], gain_linear_1, 'ro-', linewidth=2, markersize=8, label='Pomiar nr 1 (Q = 0.707)')
ax.loglog(frequencies_2[:len(gain_linear_2)], gain_linear_2, 'bo--', linewidth=2, markersize=6, label='Pomiar nr 2 (Q = 10)')

# Konfiguracja podziałki osi X
ax.xaxis.set_major_locator(LogLocator(base=10.0, numticks=15))
ax.xaxis.set_minor_locator(LogLocator(base=10.0, subs=np.arange(2, 10)*0.1, numticks=15))
ax.xaxis.set_major_formatter(LogFormatter(labelOnlyBase=False))
ax.set_xlabel('Częstotliwość [kHz]', fontsize=12)

# Konfiguracja podziałki osi Y
ax.yaxis.set_major_locator(LogLocator(base=10.0, numticks=15))
ax.yaxis.set_minor_locator(LogLocator(base=10.0, subs=np.arange(2, 10)*0.1, numticks=15))
ax.yaxis.set_major_formatter(LogFormatter(labelOnlyBase=False))
ax.set_ylabel('Wzmocnienie [20*log(Vout/Vin)]', fontsize=12)

# Dodatkowe elementy
ax.set_title('Filtr górnoprzepustowy', fontsize=14)
ax.grid(True, which='both', linestyle='--', alpha=0.6)
ax.legend(fontsize=10)

# Linie pomocnicze
ax.axhline(y=1, color='gray', linestyle=':', linewidth=1)  # 0 dB
ax.axhline(y=10**(-3/20), color='green', linestyle='--', linewidth=1)  # -3 dB

# Zakres osi
ax.set_xlim(0.9, 110)
ax.set_ylim(1e-4, 1e2)

plt.tight_layout()
#plt.gca().invert_xaxis()  # Odwraca kierunek osi X
plt.show()