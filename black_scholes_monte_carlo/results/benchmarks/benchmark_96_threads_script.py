import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Charger les deux fichiers CSV
df_v4 = pd.read_csv('resultats_v6.csv')
df_v5 = pd.read_csv('resultats_vf.csv')

# Convertir les colonnes nécessaires en valeurs numériques
df_v4['Time (seconds)'] = pd.to_numeric(df_v4['Time (seconds)'], errors='coerce')
df_v4['Threads'] = pd.to_numeric(df_v4['Threads'], errors='coerce')
df_v5['Time (seconds)'] = pd.to_numeric(df_v5['Time (seconds)'], errors='coerce')
df_v5['Threads'] = pd.to_numeric(df_v5['Threads'], errors='coerce')

# Filtrer les données pour ne conserver que les résultats avec 96 threads et les tailles de simulation spécifiées
simulation_values = [100, 1000, 10000, 100000, 1000000]

df_v4_96 = df_v4[(df_v4['Threads'] == 96) & (df_v4['Value (100s)'].isin(simulation_values))]
df_v5_96 = df_v5[(df_v5['Threads'] == 96) & (df_v5['Value (100s)'].isin(simulation_values))]

# Calculer les statistiques (moyenne et écart-type) pour chaque fichier avec 96 threads et les tailles de simulation spécifiées
summary_v4_96 = df_v4_96.groupby(['Value (100s)']).agg(
    avg_time_v4=('Time (seconds)', 'mean'),
    std_time_v4=('Time (seconds)', 'std')
).reset_index()

summary_v5_96 = df_v5_96.groupby(['Value (100s)']).agg(
    avg_time_v5=('Time (seconds)', 'mean'),
    std_time_v5=('Time (seconds)', 'std')
).reset_index()

# Fusionner les deux ensembles de données pour la comparaison avec 96 threads
comparison_df_96 = pd.merge(summary_v4_96, summary_v5_96, on=['Value (100s)'], how='outer')

# Sauvegarder le tableau de comparaison dans un fichier CSV
comparison_df_96.to_csv('benchmark_comparison_96_threads_selected.csv', index=False)

# Afficher les résultats dans la console
print(comparison_df_96)

# Visualisation des temps moyens pour les deux fichiers (v4 et v5) avec 96 threads
plt.figure(figsize=(14, 8))

sns.lineplot(data=comparison_df_96, x='Value (100s)', y='avg_time_v4', label='V4', palette='Blues', marker='o')
sns.lineplot(data=comparison_df_96, x='Value (100s)', y='avg_time_v5', label='V5', palette='Reds', marker='o')

plt.title('Comparaison des Temps Moyens d\'Exécution (V4 vs V5) avec 96 Threads')
plt.xlabel('Nombre de Simulations (Value 100s)')
plt.ylabel('Temps Moyen (secondes)')
plt.legend(title='Taille des Simulations', loc='upper left')
plt.grid(True)
plt.show()

